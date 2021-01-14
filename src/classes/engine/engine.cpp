#include "engine.h"
#include <stdio.h>
#include <time.h>

clock_t startChrono() { 
    return clock();
}

double stopChrono(clock_t start) {
    return (double)(clock() - start) / 1000; //µs to ms
}


Engine::Engine() {
    this->name = "AlphaBeta Chess 1.0";
    this->board = new Board();
    this->board->init();

    cout << this->name << endl;
}


Engine::~Engine() {
    delete this->board;
}


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
        /*
            We reset the old best move
        */
        this->best_move = Score();

        /*
            We define what end game is 
        */
        this->end_game = this->board->nb_piece != 0 && this->board->nb_piece <= 8;

       /*
            We check if we are in end game
       */
        int depth = end_game ? 7 : 5;
        
        bool direct_analysis = false;

        if (res.size() > 2 && res[1] == "depth") {
            depth = stoi(res[2]);
            direct_analysis = true;
        }

        if (this->moves.size() < 14 && this->startpos && !direct_analysis)
            searchOpeningBook(depth);
        else
            MultiDepthAnalysis(depth);

        best_move.print();
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
            Score::print_ply(m.ply);
            cout << " : " << m.score << endl;
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
/*************** End parse expression functions ***************/



/*************** Begin search in opening book functions ***************/

// Checks if the line corresponds to a game
bool isGame (string line) {
    return line[0] != '[' && line.size() > 1;
}

bool isPly (string line, Ply p) {
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
Ply lineToPly (string line) {
    string move = "";
    for (int i = 0; i<4; i++)
        move += line[i];

    return Board::StringToPly(move);
}




// We search for the next move in a opening book
void Engine::searchOpeningBook (int depth) {
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
                    s.print_info(1, 1, 0, this->board->isWhite());
                    this->best_move = s;
                    return;
                }

                // We check if the game contains the moves already played.
                bool found = true;
                for (Ply p : this->moves) {
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
                        s.print_info(1, 1, 0, this->board->isWhite());
                        this->best_move = s;
                        return;
                    } else {
                        opening_book.close();
                        MultiDepthAnalysis(depth);
                        return;
                    }
                }
            }
        }
        opening_book.close();
        MultiDepthAnalysis(depth);
        return;
    }

    MultiDepthAnalysis(depth);
}

/*************** End search in opening book functions ***************/



/*************** Begin evaluation funcion ***************/

Score Engine::evalPosition(Board* board) {
    vector<Ply> legal_moves = board->getLegalMoves();
    int size = legal_moves.size();
    
    if (size == 0) {
        if (board->isCheck())
            return Score(-mate_value);
        else return Score();

    } else {
        
        int wK = 0, bK = 0, wQ = 0, bQ = 0, wR = 0, bR = 0,
            wN = 0, bN = 0, wB = 0, bB =0, wP = 0, bP = 0;
        
        int material_score = 0;

        for (int i = 0; i<64; i++) {

            if (checkIfPiece(board->squares[i])) {
                char name = board->squares[i]->getName();
                material_score += board->squares[i]->getPieceValue(this->end_game);

                if (name == 'k') {
                    board->squares[i]->isWhite() ? wK++ : bK++;
                }

                if (name == 'q') {
                    board->squares[i]->isWhite() ? wQ++ : bQ++;
                }

                if (name == 'r') {
                    board->squares[i]->isWhite() ? wR++ : bR++;
                }

                if (name == 'n') {
                    board->squares[i]->isWhite() ? wN++ : bN++;
                }

                if (name == 'b') {
                    board->squares[i]->isWhite() ? wB++ : bB++;
                }

                if (name == 'p') {
                    board->squares[i]->isWhite() ? wP++ : bP++;
                }
            }
        }

        if (this->end_game) {

            // Pair of bishop
            if (wB >= 2)
                material_score += 10;

            if (bB >= 2)
                material_score -= 10;
            
            // Increase pawn value
            material_score += wP*200;
            material_score -= bP*200;

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
        board->setEnPassant(false);
        board->computeLegalMoves();
        
        *other_mobility = board->getLegalMoves().size();
        board->changeSide();

        int mobility_score = mobilityV * (mobility_white - mobility_black);
        int score = (material_score + mobility_score) * (board->isWhite() ? 1 : -1);

        return Score(score);

    }
}

/*************** End evaluation funcion ***************/


/*************** Begin Heuristics funcs ***************/

bool Engine::NullPruning (Score beta, int depth, Score &res) {
    this->board->changeSide();
    Score score = AlphaBetaNegamax (depth - 1 - 2, Score (-beta.score), Score (-beta.score+1));
    this->board->changeSide();
    score.score = -score.score;

    if (score.score >= beta.score) {
        res = beta;
        return true;
    }
    return false;
}

/*************** End Heuristics funcs ***************/



/*************** Begin useful funcs for deep search ***************/

bool Engine::checkRepetitions (string position) {
    int count = 1;
    for (int i = 0; i<this->positions.size() - 1; i++) {
        if (positions[i] == position)
            count ++;
    }
    return count == 3;
}

bool isCapture (int idx_p1, int idx_p2, Piece** board) {
    return checkIfPiece (board[idx_p1]) && checkIfPiece (board[idx_p2]);
}

int getPieceIdx (char name) {
    switch (name) {
        case 'k':
            return 0;
        case 'p':
            return 1;
        case 'n':
            return 2;
        case 'b':
            return 3;
        case 'r':
            return 4;
        case 'q':
            return 5;
        default:
            return -1;
    }
}

vector<Move> Engine::PlyToMove (vector<Ply> move_list) {
    vector<Move> res;
    int size = this->best_move.plies.size();

    for (int i = 0; i < move_list.size(); i++) {
        int idx1 = squareToIdx(move_list[i].dep);
        int idx2 = squareToIdx(move_list[i].stop);

        Move m = {
            move_list[i],
            0
        };

        if (
            size > 0
            && move_list[i].dep == this->best_move.plies[0].dep
            && move_list[i].stop == this->best_move.plies[0].stop
        ) 
        {
            m.score = 1000;
        }

        else if (isCapture (idx1, idx2, this->board->squares)) {
            m.score = capture_table
                      [getPieceIdx (this->board->squares[idx1]->getName())]
                      [getPieceIdx (this->board->squares[idx2]->getName())];
        }
        res.push_back (m);
    }
    return res;
}

vector<Move> Engine::sortMoves () {
    this->board->computeLegalMoves();
    vector<Ply> legal_moves = this->board->getLegalMoves();
    vector <Move> res = PlyToMove(legal_moves);

    sort (res.begin(), res.end(), [](Move m1, Move m2) { return m1.score > m2.score; });

    return res;
}

/*************** End useful funcs for deep search ***************/



/*************** Begin negamax alpha beta deep search ***************/
int nodes = 0;
Score Engine::AlphaBetaNegamax (int depth, Score alpha, Score beta) {
    nodes++;

    //this->board->computeLegalMoves();
    vector<Move> move_list = sortMoves ();
    
    int size = move_list.size();

    // We don't check for repetitions at the root
    if (nodes > 1) {
        string pos = this->board->getFen(false);

        this->positions.push_back (pos);
    

        if (checkRepetitions (pos)) return Score (0);
    }

    if (depth == 0 || size == 0) return evalPosition(this->board);

    for (int i = 0; i<size; i++) {
        this->board->play_move(move_list[i].ply, true);
        
        Score score = AlphaBetaNegamax (depth - 1, Score(-beta.score), Score(-alpha.score));

        this->board->undo_move();
        this->positions.pop_back();


        score.score = -score.score;
        score.plies.push_back(move_list[i].ply);
        
        if (alpha.score >= beta.score) {
            bool check_mate = alpha.score == mate_value && alpha.plies.size() >= 1;
            return (check_mate ? alpha : beta);
        }
        
        alpha = Score::max (score, alpha);
    }
    return alpha;
}

/*************** End negamax alpha beta deep search ***************/


/*************** Begin in depth analysis functions ***************/

void Engine::inDepthAnalysis (int depth) {

    Score alpha (-mate_value); // Black checkmate
    Score beta (mate_value); // White Checkmate

    Score bestMove = AlphaBetaNegamax (depth, alpha, beta);

    reverse(bestMove.plies.begin(), bestMove.plies.end());

    if (!this->board->isWhite()) bestMove.score *= -1;
    
    this->best_move = bestMove;
}


void Engine::MultiDepthAnalysis (int depth) {
    for (int i = 1; i<= depth; i++) {
        nodes = 0;

        clock_t start = startChrono();
        inDepthAnalysis(i);
        int dur = stopChrono(start);

        this->best_move.print_info(i, nodes, dur, this->board->isWhite());

        /* 
            We check if there is a inevitable checkmate.
            If a checkmate in n moves has been found, it's useless to go deeper than depth n
        */
        if (this->best_move.score == mate_value)
            return;
    }
}

/*************** End in depth analysis functions ***************/
