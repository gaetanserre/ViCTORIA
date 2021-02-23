#include "engine.h"

/*************** Begin evaluation functions ***************/


int getNbCastlings (vector<Ply> legal_moves, Piece** squares, bool white) {

    int file = white ? 1 : 8;
    Ply c_short = Ply(Square('e', file), Square('g', file));
    Ply c_long = Ply(Square('e', file), Square('c', file));

    if (squares[squareToIdx(Square('e', file))]->getName() == 'k') {
        int res = 0;

        for (Ply p : legal_moves) {
            if (p == c_short || p == c_long) res ++;
            if (res == 2) break;
        }
        return res;

    } else {
        return 0;
    }
}


/*
* We check if the opponent can check the kin
* If yes, we consider that the king is not safe (attaque à la découverte)
*/
bool isKingSafe (Board* board) {

    for (Ply p : board->getLegalMoves()) {
        board->play_move(p, true);
        bool check = board->isCheck();
        board->undo_move();

        if (check) return false;
    }

    return true;
} 


Score Engine::evalPosition(Board* board) {
    vector<Ply> legal_moves = board->getLegalMoves();
    int size = legal_moves.size();
    bool white = board->isWhite();
    
    if (size == 0) {
        if (board->isCheck())
            return Score( (white ? -mate_value : mate_value) );
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
            material_score += wP * 150;
            material_score -= bP * 150;

        }

        //cout << wK << " " << bK << " " << wQ << " " << bQ << " " << wR << " " << bR << " " << wN << " " << bN << " " << wB << " " << bB << " " << wP << " " << bP << endl;
            

        /*const float mobilityV = 3;

        int mobility_white, mobility_black;
        int *other_mobility;

        if (white) {
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
        board->computeLegalMoves();*/

        /* 
        * We check if the king is safe
        * To be working, we need to change side so this function needs to be between these 2 changeSide() calls
        */
        //int safety_score = isKingSafe(board) ? 200 : 0;
        
        /**other_mobility = board->getLegalMoves().size();
        board->changeSide();

        int mobility_score = mobilityV * (mobility_white - mobility_black);*/

        /*
        * We check if we have castling
        * If yes, we add/remove 100 cp
        * If no, we add/remove 25 cp per castling we can do in this position
        */
        int castlings_score = 0;
        if (white) {
            if (board->has_castling_w) castlings_score += 100;
            else castlings_score += 25 * getNbCastlings (legal_moves, board->squares, white);
        } else {
            if (board->has_castling_b) castlings_score -= 100;
            else castlings_score -= 25 * getNbCastlings (legal_moves, board->squares, white);
        }

        int score = (material_score + castlings_score);

        return Score(score);

    }
}


/*************** End evaluation functions ***************/