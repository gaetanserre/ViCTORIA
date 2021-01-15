#include "engine.h"
/*************** End parse expression functions ***************/

vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

void Engine::parse_expr(string expr) {

    vector<string> res = split(expr, ' ');

    // parse expression of type : position fen [fen] moves [moves]
    if (res.size() > 1 && res[0] == "position") {

        delete this->board;
        this->board = new Board ();

        this->positions.clear();
        this->moves.clear();

        int moves_idx = 8;

        if (res[1] == "fen") {
            string fen = "";
            for (int i = 2; i<8; i++) {
                fen += res[i] + " ";
            }
            replace(fen.begin(), fen.end(), 'A', 'K');
            replace(fen.begin(), fen.end(), 'H', 'Q');
            replace(fen.begin(), fen.end(), 'a', 'k');
            replace(fen.begin(), fen.end(), 'h', 'q');

            this->board->init(fen);

            this->startpos = fen == "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 ";


        } else if (res[1] == "startpos") {
            this->board->init();
            moves_idx = 2;

            this->startpos = true;
        }

        this->positions.push_back(this->board->getFen(false));

        if (res.size() > moves_idx+1 && res[moves_idx] == "moves") {
            for (int i = moves_idx+1; i<res.size(); i++) {
                this->board->computeLegalMoves();
                this->board->play_move(res[i]);
                this->moves.push_back(Board::StringToPly(res[i]));
                this->positions.push_back(this->board->getFen(false));
            }
        }
    }
    
    else if (res.size() == 2 && res[0] == "play") {
        
        this->board->computeLegalMoves();
        this->board->play_move(res[1]);

        this->positions.push_back(this->board->getFen(false));

        this->board->printPieces();

        print_bitboard(this->board->occupancy);

        this->moves.push_back(Board::StringToPly(res[1]));

        this->board->computeLegalMoves();
        int size = this->board->getLegalMoves().size();
        if (this->board->isCheckmate(size)) {
            cout << (this->board->isWhite() ? "black" : "white") << " wins." << endl;
        }

        if (this->board->isStalemate(size)) {
            cout << "Stalemate." << endl;
        }

    }
    
    else if (res.size() > 0 && res[0] == "go") {
        parse_go_command(res);
    }
    

    else if (expr == "fen") {

        cout << this->board->getFen() << endl;
    }

    else if (expr == "undo") {
        this->board->undo_move();
        this->board->printPieces();
        this->moves.pop_back();
    }

    else if (expr == "legal") {
        clock_t start = startChrono();
        this->board->computeLegalMoves();
        double dur = stopChrono(start);
        this->board->printLegalMoves();
        printf("%lf millisecond(s)\n", dur);
    }

    else if (expr == "eval") {
        this->end_game = this->board->nb_piece != 0 && this->board->nb_piece <= 8;

        this->board->computeLegalMoves();
        clock_t start = startChrono();
        Score s = evalPosition(this->board);
        int dur = stopChrono(start);
        s.print_info(1, 1, dur, this->board->isWhite());
    }

    else if (expr == "sort") {
        vector<Move> res = this->sortMoves();
        for (Move m : res) {
            cout << m.ply.toString() << " : " << m.score << endl;
        }
    }

    else if (expr == "uci") {
        cout << "id name " << this->name << endl;
        cout << "id author Gaetan Serre" << endl;
        cout << "uciok" << endl;
    }

    else if (expr == "isready") {
        cout << "readyok" << endl;
    }

    else if (expr == "stop") {
        this->best_move.print();
    }

    else if (expr != "quit") {
        cout << "Unknown command: " << expr << endl;
    }
}

void *worker_thread(void *arg)
{
        printf("This is worker_thread()\n");
        pthread_exit(NULL);
}


void Engine::parse_go_command (vector<string> args) {
    /*
        We reset the old best move
    */
    this->best_move = Score();

    /*
        We define what end game is 
    */
    this->end_game = this->board->nb_piece != 0 && this->board->nb_piece <= 8;

    /*
        command: go infinite
    */
    if (args.size() == 2 && args[1] == "infinite") {
        this->terminate_thread = false;
        thread t(&Engine::MultiDepthAnalysis, this, this->maxDepth);
        string input = "";
        while (input != "stop") {
            getline(cin, input);
        }
        this->terminate_thread = true;
        t.join();
        this->best_move.print();
    }

    else if (args.size() == 3 && args[1] == "movetime") {
        cout << "ok" << endl;
        this->terminate_thread = false;
        int dur = stoi(args[2]);
        double stop = (double)(clock() / 1000) + dur;
        thread t(&Engine::MultiDepthAnalysis, this, this->maxDepth);
        double actual = (double) clock() / 1000;
        while (actual < stop) {
            actual = (double) clock() / 1000;
        }
        this->terminate_thread = true;
        t.join();
        this->best_move.print();
    }

    /*
        command: go depth n
    */
   else if (args.size() == 3 && args[1] == "depth") {
        int depth = stoi(args[2]);
        MultiDepthAnalysis(depth);
        this->best_move.print();
   }

    /*
        command: go and all others
    */
    else {
        int depth = end_game ? 7 : 5;
        if (this->moves.size() < 14 && this->startpos && !not_in_opening_table)
            searchOpeningBook(depth);
        else
            MultiDepthAnalysis(depth);
        this->best_move.print();
    }
}


/*************** End parse expression functions ***************/