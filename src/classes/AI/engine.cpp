#include "engine.h"

Engine::Engine() {
    cout << "Chess AI Engine version alpha" << endl;
    this->board.init();
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
void Engine::parse_expr(string expr) {
    vector<string> res = split(expr, ' ');

    // parse expression of type : position fen [fen] moves [moves]
    if (res.size() > 1) {
        int moves_idx = 8;

        if (res[0] == "position") {
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
            } else if (res[1] == "startpos") {
                this->board.init();
                moves_idx = 2;
            }
        }

        if (res.size() > moves_idx+1 && res[moves_idx] == "moves") {
            for (int i = moves_idx+1; i<res.size(); i++) {
                this->board.computeLegalMoves();
                this->board.play_move(res[i].c_str());
            }
        }

    } 

    else if (res.size() == 2 && res[0] == "play") {
        this->board.computeLegalMoves();
        this->board.play_move(res[1].c_str());
        this->board.printPieces();

        this->board.computeLegalMoves();
        if (this->board.isCheckmate()) {
            cout << (this->board.isWhite() ? "black" : "white") << " wins." << endl;
        }

        if (this->board.isStalemate()) {
            cout << "Stalemate." << endl;
        }
    }
    
    else if (res[0] == "go") {
        int depth = 3;
        
        if (res.size() > 2 && res[1] == "depth") {
            depth = stoi(res[2]);
        }

        this->best_move = inDepthAnalysis(depth);
        this->best_move.print_info(depth);
        //if (res.size() > 2 && res[1] == "depth") best_move.print();
        best_move.print();
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
        Score s = evalPosition();
        s.print();
    }

    else if (expr == "uci") {
        cout << "id name Chess AI Engine 1.0" << endl;
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
        const int kingV = 20000;
        const int queenV = 900;
        const int rookV = 500;
        const int BNV = 300;
        const int pawnV = 100;
        
        const float mobilityV = 30;

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

    Score max_score = res[0];
    for (int i = 1; i<res.size(); i++) {
        max_score = Score::max(max_score, res[i], this->board.isWhite());
    }

    return max_score;
}
