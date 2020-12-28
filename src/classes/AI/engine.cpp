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
    } else if (expr == "go") {
        inDepthAnalysis(10);
    }
    
    else if (expr != "quit") {
        cout << "Unknown command: " << expr << endl;
    }
}

Score Engine::evalPosition() {
    vector<ply> legal_moves;
    bool isOver = this->board.isOver();
    legal_moves = this->board.getLegalMoves();
    if (isOver) {
        if (this->board.isStalemate(legal_moves))
            return Score(0, true, 0);

        else
            return Score(0, false, 0);
    } else {
        const int rookV = 5;
        const int BNV = 3;
        const int queenV = 9;
        const int pawnV = 1;
        const int kingV = 200;
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
        cout << wK << " " << bK << " " << wQ << " " << bQ << " " << wR << " " << bR << " " << wN << " " << bN << " " << wB << " " << bB << " " << wP << " " << bP << endl;
            
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
        this->board.isOver();
        *other_mobility = this->board.getLegalMoves().size();
        this->board.changeSide();

        int mobility_score = mobilityV * (mobility_white - mobility_black);
        int score = (material_score + mobility_score) * (this->board.isWhite() ? 1 : -1);

        cout << score << endl;
        return Score(score, false, 0);

    }

}

Score Engine::inDepthAnalysis(int depth) {
    bool isOver = this->board.isOver();
    Score max_score (0, false, 0);
    if (! isOver && depth > 0) {
        vector<ply> legal_moves = this->board.getLegalMoves();

        for (ply p : legal_moves) {
            this->board.play_move(p);
            Score temp = inDepthAnalysis(depth-1);

            if (temp > max_score) max_score = temp;

            if (max_score.mate) depth = max_score.n_mate;

            //Implémenter undo move
        }
        return Score (max_score.score, max_score.mate, max_score.n_mate+1);

    } else {
        return evalPosition();
    }
}