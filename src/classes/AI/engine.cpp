#include "engine.h"

Engine::Engine() {
    this->name = "Chess AI Engine 1.0";
    this->board.init();
    cout << this->name << endl;

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

#include <time.h>
clock_t startChrono() { 
    return clock();
}

double stopChrono(clock_t start) {
    return (double)(clock() - start) / CLOCKS_PER_SEC;
}


void Engine::parse_expr(string expr) {
    vector<string> res = split(expr, ' ');

    // parse expression of type : position fen [fen] moves [moves]
    if (res.size() > 1 && res[0] == "position") {
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

            this->board.init(fen);

            this->startpos = false;
        } else if (res[1] == "startpos") {
            this->board.init();
            moves_idx = 2;

            this->startpos = true;
        }

        this->moves.clear();


        if (res.size() > moves_idx+1 && res[moves_idx] == "moves") {
            for (int i = moves_idx+1; i<res.size(); i++) {
                this->board.computeLegalMoves();
                this->board.play_move(res[i]);
                this->moves.push_back(Board::StringToPly(res[i]));
            }
            this->startpos = false;
        }
    }

    else if (res.size() == 2 && res[0] == "play") {
        this->board.computeLegalMoves();
        this->board.play_move(res[1]);
        this->board.printPieces();

        this->moves.push_back(Board::StringToPly(res[1]));

        this->board.computeLegalMoves();
        if (this->board.isCheckmate()) {
            cout << (this->board.isWhite() ? "black" : "white") << " wins." << endl;
        }

        if (this->board.isStalemate()) {
            cout << "Stalemate." << endl;
        }

        this->startpos = false;
    }
    
    else if (res[0] == "go") {
        int depth = 3;

        // We check that there are less than 8 pieces on the chessboard.
        if (this->board.nb_pieces != 0 && this->board.nb_pieces < 8) depth = 4; 
        
        bool direct_analysis = false;

        if (res.size() > 2 && res[1] == "depth") {
            depth = stoi(res[2]);
            direct_analysis = true;
        }

        clock_t start = startChrono();
        if (this->moves.size() < 14 && this->startpos && !direct_analysis)
            this->best_move = searchOpeningBook(3);
        else
            this->best_move = inDepthAnalysis(depth);

        double dur = stopChrono(start);
        this->best_move.print_info(depth, this->board.isWhite());
        best_move.print();
        printf("%.3f seconds\n", dur);
    }
    

    else if (expr == "fen") {
        cout << this->board.getFen() << endl;
    }

    else if (expr == "undo") {
        this->board.undo_move();
        this->board.printPieces();
    }

    else if (expr == "legal") {
        this->board.printLegalMoves();
    }

    else if (expr == "eval") {
        clock_t start = startChrono();
        Score s = evalPosition();
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

// We evaluate position with value of each piece taken and number of legal moves
Score Engine::evalPosition() {
    this->board.computeLegalMoves();
    vector<ply> legal_moves = this->board.getLegalMoves();
    bool isOver = this->board.isOver();

    if (isOver) {
        if (this->board.isCheckmate())
            return Score(0, true, !this->board.isWhite(), 0);
        else
            return Score(0, false, false, 0);
    } else {

        // Value in centipawn
        const int kingV = 20000;
        const int queenV = 900;
        const int rookV = 500;
        const int BNV = 300;
        const int pawnV = 100;
        
        int wK = 0, bK = 0, wQ = 0, bQ = 0, wR = 0, bR = 0,
            wN = 0, bN = 0, wB = 0, bB =0, wP = 0, bP = 0;

        for (int i = 0; i<64; i++) {
            Piece* p = this->board.squares[i];
            string name = p->getName();

            if (name == "king") {
                p->isWhite() ? wK++ : bK++;
            }

            if (name == "queen") {
                p->isWhite() ? wQ++ : bQ++;
            }

            if (name == "rook") {
                p->isWhite() ? wR++ : bR++;
            }

            if (name == "knight") {
                p->isWhite() ? wN++ : bN++;
            }

            if (name == "bishop") {
                p->isWhite() ? wB++ : bB++;
            }

            if (name == "pawn") {
                p->isWhite() ? wP++ : bP++;
            }
        }
        //cout << wK << " " << bK << " " << wQ << " " << bQ << " " << wR << " " << bR << " " << wN << " " << bN << " " << wB << " " << bB << " " << wP << " " << bP << endl;
            
        int material_score =  kingV * (wK - bK)
                            + queenV * (wQ - bQ)
                            + rookV * (wR - bR)
                            + BNV * (wN - bN)
                            + BNV * (wB - bB)
                            + pawnV * (wP - bP)
        ;

        const float mobilityV = 3;

        int mobility_white, mobility_black;
        int *other_mobility;

        if (this->board.isWhite()) {
            mobility_white = legal_moves.size();
            other_mobility = &mobility_black;
        }
        else {
            mobility_black = legal_moves.size();
            other_mobility = &mobility_white;
        }
            
        // Compute mobility for the other side
        this->board.changeSide();
        this->board.computeLegalMoves();
        *other_mobility = this->board.getLegalMoves().size();
        this->board.changeSide();

        int mobility_score = mobilityV * (mobility_white - mobility_black);
        int score = (material_score + mobility_score);

        //cout << material_score << " " << mobility_white << " " << mobility_black << endl;

        return Score(score, false, false, 0);

    }

}

/*
    We go through the tree of possible cuts in stages.
    Thus, if we encounter checkmate, we can stop the search because
    no combination of moves can be better (at best it will be equivalent).
*/
Score Engine::inDepthAnalysis (int depth) {

    if (depth == 0) return evalPosition();

    this->board.computeLegalMoves();
    vector<ply> legal_moves = this->board.getLegalMoves();

    if (legal_moves.size() == 0) return evalPosition();


    // First we evaluate the position for each legal moves

    vector<Score> scores;

    for (ply p : legal_moves) {
        this->board.play_move(p, true);
        Score s = evalPosition();
        this->board.undo_move();

        s.plies.push_back(p);
        s.n_mate = s.plies.size();

        //If mate in 1
        if (s.mate && s.white_mate == this->board.isWhite()) {
            //s.print_info(1);
            return s;
        }

        scores.push_back(s);
    }

    // Then we store all variants starting with depth 1, 2, 3 etc...

    vector<Score> res;
    for (Score s : scores)
        res.push_back(s);

    for (int i = 1; i<depth; i++) {
        for (int j = 0; j<scores.size(); j++) {
            
            //We store the initial position
            string initPos = this->board.getFen();

            for (ply p : scores[j].plies)
                this->board.play_move(p, true);
            

            Score temp = inDepthAnalysis(i);
            temp.plies.insert(temp.plies.begin(), scores[j].plies.begin(), scores[j].plies.end());
            temp.n_mate = temp.plies.size();

            res[j] = temp;

            // We restore the initial position
            this->board.init(initPos);
            
            // If one of the variants is checkmate, we return it.
            if (temp.mate && temp.white_mate == this->board.isWhite())
                return temp;
        }
    }

    // Finally we return the best variant

    return Score::max (res, this->board.isWhite());
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
    opening_book.open ("/home/gaetan/Documents/Projets/IA-Chess/libs/opening_book-2.5M.pgn");

    if (opening_book.is_open()) {
        string line;
        while (getline(opening_book, line)) {

            // We check if the line corresponds to a game
            if (isGame (line)) {
                
                // If no move has been played, we return the first opening that fits the color
                if (this->moves.size() == 0 && isWin(line, this->board.isWhite())) {
                    cout<<line<<endl;
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
                if (found && isWin(line, this->board.isWhite())) {
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

