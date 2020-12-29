#include "engine.h"

Engine::Engine() {
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

    if (res.size() > 7) {
        if (res[0] == "position" && res[1] == "fen") {
            string fen = "";
            for (int i = 2; i<res.size(); i++) {
                fen += res[i] + " ";
            }
            this->board.init(fen);
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
        Score s = inDepthAnalysis(depth);
        s.print();
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
        this->board.computeLegalMoves();
        Score s = evalPosition();
        s.print();
    }
    
    else if (expr != "quit") {
        cout << "Unknown command: " << expr << endl;
    }
}

Score Engine::evalPosition() {
    vector<ply> legal_moves = this->board.getLegalMoves();
    bool isOver = this->board.isOver();

    if (isOver) {
        if (this->board.isCheckmate())
            return Score(0, true, !this->board.isWhite(), 0);
        else
            return Score(0, false, false, 0);
    } else {
        const int kingV = 200;
        const int queenV = 9;
        const int rookV = 5;
        const int BNV = 3;
        const int pawnV = 1;
        
        const float mobilityV = 0.2;

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

Score Engine::inDepthAnalysis(int depth) {

    this->board.computeLegalMoves();
    bool isOver = this->board.isOver();
    bool first =  true;
    Score max_score (0, false, false, 0);

    if (! isOver && depth > 0) {
        vector<ply> legal_moves = this->board.getLegalMoves();

        for (ply p : legal_moves) {
            
            this->board.play_move(p);

            Score temp = inDepthAnalysis(depth-1);
        
            this->board.undo_move();
            this->board.setLegalMoves(legal_moves);

            temp.plies.push_back(p);
            
            if (first) {
                max_score = temp;
                first = false;
            } else 
                max_score = Score::max(max_score, temp, this->board.isWhite());

            if (max_score.mate) {
                if (max_score.n_mate < 2) {
                    max_score.n_mate++;
                    return max_score;
                } else 
                    depth = max_score.n_mate - 1;
            }
        }
        max_score.n_mate++;
        return max_score;

    } else {
        return evalPosition();
    }
}