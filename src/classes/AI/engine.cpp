#include "engine.h"
#include <stdio.h>
#include <time.h>


Engine::Engine() {
    this->name = "Chess AI Engine 1.0";
    this->board = new Board();
    this->board->init();
    cout << this->name << endl;

}


Engine::~Engine() {
    delete this->board;
}


vector<string> split (const string &s, char delim) {
    vector<string> result;
    stringstream ss (s);
    string item;

    while (getline (ss, item, delim)) {
        result.push_back (item);
    }

    return result;
}

clock_t startChrono() { 
    return clock();
}

double stopChrono(clock_t start) {
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}


Score evalPosition(Board* board) {
    vector<ply> legal_moves = board->getLegalMoves();
    int size = legal_moves.size();
    
    if (size == 0) {
        if (board->isCheck())
            return Score(0, true, !board->isWhite(), 0);
        else return Score(0, false, false, 0);

    } else {

        bool end_game = board->nb_pieces <= 8;
        
        int wK = 0, bK = 0, wQ = 0, bQ = 0, wR = 0, bR = 0,
            wN = 0, bN = 0, wB = 0, bB =0, wP = 0, bP = 0;
        
        int material_score = 0;

        for (int i = 0; i<64; i++) {

            if (checkIfPiece(board->squares[i])) {
                string name = board->squares[i]->getName();
                material_score += board->squares[i]->getPieceValue(end_game);

                if (name == "king") {
                    board->squares[i]->isWhite() ? wK++ : bK++;
                }

                if (name == "queen") {
                    board->squares[i]->isWhite() ? wQ++ : bQ++;
                }

                if (name == "rook") {
                    board->squares[i]->isWhite() ? wR++ : bR++;
                }

                if (name == "knight") {
                    board->squares[i]->isWhite() ? wN++ : bN++;
                }

                if (name == "bishop") {
                    board->squares[i]->isWhite() ? wB++ : bB++;
                }

                if (name == "pawn") {
                    board->squares[i]->isWhite() ? wP++ : bP++;
                }
            }
        }

        if (end_game) {

            // Pair of bishop
            if (wB >= 2)
                material_score += 10;

            if (bB >= 2)
                material_score -= 10;

            // Increase pawn value
            for (int i = 0; i<wP; i++)
                material_score += 100;

            for (int i = 0; i<bP; i++)
                material_score -= 100;
        }

        //cout << wK << " " << bK << " " << wQ << " " << bQ << " " << wR << " " << bR << " " << wN << " " << bN << " " << wB << " " << bB << " " << wP << " " << bP << endl;
            

        const float mobilityV = 3;

        int mobility_white, mobility_black;
        int *other_mobility;

        if (board->isWhite()) {
            mobility_white = legal_moves.size();
            other_mobility = &mobility_black;
        }
        else {
            mobility_black = legal_moves.size();
            other_mobility = &mobility_white;
        }
            
        // Compute mobility for the other side
        board->changeSide();
        board->computeLegalMoves();
        *other_mobility = board->getLegalMoves().size();
        board->changeSide();

        int mobility_score = mobilityV * (mobility_white - mobility_black);
        int score = (material_score + mobility_score);

        //cout << material_score << " " << mobility_white << " " << mobility_black << endl;

        return Score(score, false, false, 0);

    }
}



void Engine::parse_expr(string expr) {


    vector<string> res = split(expr, ' ');

    // parse expression of type : position fen [fen] moves [moves]
    if (res.size() > 1 && res[0] == "position") {

        delete this->board;
        this->board = new Board ();

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

        this->moves.clear();


        if (res.size() > moves_idx+1 && res[moves_idx] == "moves") {
            for (int i = moves_idx+1; i<res.size(); i++) {
                this->board->computeLegalMoves();
                this->board->play_move(res[i]);
                this->moves.push_back(Board::StringToPly(res[i]));
            }
        }
    }
    

    else if (res.size() == 2 && res[0] == "play") {
        
        this->board->computeLegalMoves();
        this->board->play_move(res[1]);
        this->board->printPieces();

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

        int depth = 4;

        // We check that there are less than 8 pieces on the chessboard.
        if (this->board->nb_pieces != 0 && this->board->nb_pieces <= 8) depth = 5; 
        
        bool direct_analysis = false;

        if (res.size() > 2 && res[1] == "depth") {
            depth = stoi(res[2]);
            direct_analysis = true;
        }

        clock_t start = startChrono();
        if (this->moves.size() < 14 && this->startpos && !direct_analysis)
            this->best_move = searchOpeningBook(depth);
        else
            this->best_move = inDepthAnalysis(depth);

        double dur = stopChrono(start);
        this->best_move.print_info(depth, this->board->isWhite());
        best_move.print();
        printf("%.3f seconds\n", dur);
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
        printf("%f seconds\n", dur);
    }

    else if (expr == "eval") {
        clock_t start = startChrono();
        Score s = evalPosition(this->board);
        double dur = stopChrono(start);
        s.print();
        printf("\n%lf seconds.\n", dur);
    }

    else if (expr == "uci") {
        cout << "id name " << this->name << endl;
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



// Checks if the line corresponds to a game
bool isGame (string line) {
    return line[0] != '[' && line.size() > 1;
}

bool isPly (string line, ply p) {
    if (line[0] == p.dep.row && line[1] == char(p.dep.line + '0')) {
        return line [2] == p.stop.row && line[3] == char(p.stop.line + '0');
    }
    return false;
}

// Checks if the game contained in line is a win
bool isWin (string line, bool white) {
    int end = line.size() - 1;

    if (line[end] == '2') return false;
    if (line[end] == '1') return ! white;
    else return white;
}

// Erase the n firsts char in line
void eraseNchars (string &line, int n) {
    for (int i = 0; i<n; i++)
        line.erase(line.begin());
}

// Convert the first ply in line into a ply
ply lineToPly (string line) {
    string move = "";
    for (int i = 0; i<4; i++)
        move += line[i];

    return Board::StringToPly(move);
}


// We search for the next move in a opening book
Score Engine::searchOpeningBook (int depth) {
    ifstream opening_book;
    opening_book.open ("/home/gaetan/Documents/Projets/Chess/chess_books/opening_book-2.5M.pgn");

    if (opening_book.is_open()) {
        string line;
        while (getline(opening_book, line)) {

            // We check if the line corresponds to a game
            if (isGame (line)) {
                
                // If no move has been played, we return the first opening that fits the color
                if (this->moves.size() == 0 && isWin(line, this->board->isWhite())) {
                    Score s;
                    s.plies.push_back(lineToPly(line));
                    opening_book.close();
                    return s;
                }

                // We check if the game contains the moves already played.
                bool found = true;
                for (ply p : this->moves) {
                    if (isPly (line, p)) {
                        eraseNchars(line, 5);
                    } else {
                        found = false;
                        break;
                    }
                }

                // If yes, we return it
                if (found && isWin(line, this->board->isWhite())) {
                    if (line.size() > 4) {
                        Score s;
                        s.plies.push_back(lineToPly(line));
                        opening_book.close();
                        return s;
                    } else {
                        opening_book.close();
                        return inDepthAnalysis(depth);
                    }
                }
            }
        }
        opening_book.close();
        return inDepthAnalysis(depth);
    }

    return inDepthAnalysis(depth);
}

Score Engine::inDepthAnalysisAux (int depth, Score alpha, Score beta) {

    this->board->computeLegalMoves();

    vector<ply> legal_moves = this->board->getLegalMoves();
    int size = legal_moves.size();

    if (depth == 0 || size == 0) return evalPosition(this->board);


    Score bestMove (0, true, !this->board->isWhite(), 0);

    for (int i = 0; i<size; i++) {
        bool white = this->board->isWhite();
        this->board->play_move(legal_moves[i], true);
        Score temp = inDepthAnalysisAux(depth - 1, alpha, beta);
        temp.plies.push_back(legal_moves[i]);
        temp.n_mate++;
        this->board->undo_move();

        bestMove = Score::max(bestMove, temp, this->board->isWhite());

        if (this->board->isWhite())
            alpha = Score::max (alpha, bestMove, true);
        else 
            beta = Score::max (beta, bestMove, false);

        if (beta <= alpha) return bestMove;
    }
    return bestMove;
}

Score Engine::inDepthAnalysis (int depth) {
    this->board->computeLegalMoves();
    vector<ply> legal_moves = this->board->getLegalMoves();
    Score bestMove (0, true, !board->isWhite(), 0);

    Score alpha (0, true, false, 0); // Black checkmate
    Score beta (0, true, true, 0); // White Checkmate


    for (ply p : legal_moves) {

        this->board->play_move(p, true);
        Score temp = inDepthAnalysisAux(depth - 1, alpha, beta);
        this->board->undo_move();
        temp.plies.push_back(p);
        temp.n_mate++;

        bestMove = Score::max(bestMove, temp, this->board->isWhite());
    }

    reverse(bestMove.plies.begin(), bestMove.plies.end());
    
    return bestMove;
}
