#include "evaluator.h"

/*************** Begin evaluation functions ***************/

int Evaluator::getNbCastlings (vector<Ply> legal_moves, Piece** squares, bool white) {

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

bool Evaluator::isKingSafe (Board* board) {

    for (Ply p : board->getLegalMoves()) {
        board->play_move(p, true);
        bool check = board->isCheck();
        board->undo_move();

        if (check) return false;
    }

    return true;
}

void Evaluator::getPawnsInfos(unordered_map<int, int> pawn_columns, int &nb_isolated, int &nb_doubled) {
    nb_doubled = 0;
    nb_isolated = 0;

    int prev = -1;
    int nb_empty = 1;
    bool pawn = false;

    for (int i = 0; i<9; i++) {
        if (pawn_columns.find(i) != pawn_columns.end()) {
            if (pawn_columns[i] >= 2)
                nb_doubled += pawn_columns[i] - 1;

            pawn = true;
            if (prev != -1 && prev == i - 1) {
                nb_empty = max(nb_empty - 1, 0);
            }
            prev = i;
        } else if (pawn) {
            nb_empty++;
            if (nb_empty == 2) {
                nb_isolated++;
                nb_empty = 1;
                pawn = false;
            }
        }
    }
}

Score Evaluator::evalPosition(Board* board, bool early_game, bool end_game) {
    vector<Ply> legal_moves = board->getLegalMoves();
    int size = legal_moves.size();
    bool white = board->isWhite();

    if (size == 0 || board->nb_plies_50_rule == 100) {
        if (board->isCheck())
            return Score( (white ? -mate_value : mate_value) );
        else return Score();

    } else {

        int wK = 0, bK = 0, wQ = 0, bQ = 0, wR = 0, bR = 0,
                wN = 0, bN = 0, wB = 0, bB =0, wP = 0, bP = 0;

        unordered_map<int, int> Wpawn_columns;
        unordered_map<int, int> Bpawn_columns;

        int material_score = 0;

        for (int i = 0; i<64; i++) {

            if (checkIfPiece(board->squares[i])) {
                char name = board->squares[i]->getName();
                material_score += board->squares[i]->getPieceValue(early_game, end_game);

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
                    if (board->squares[i]->isWhite()){
                        wP++;
                        if (Wpawn_columns.find(i%8) != Wpawn_columns.end())
                            Wpawn_columns[i%8] += 1;
                        else
                            Wpawn_columns[i%8] = 1;
                    } else {
                        bP++;
                        if (Bpawn_columns.find(i%8) != Bpawn_columns.end())
                            Bpawn_columns[i%8] += 1;
                        else
                            Bpawn_columns[i%8] = 1;
                    }
                }
            }
        }

        // We check for doubled pawns and isolated pawns
        int Wdoubled_pawn = 0;
        int Bdoubled_pawn = 0;
        int Wisolated_pawn = 0;
        int Bisolated_pawn = 0;

        getPawnsInfos(Wpawn_columns, Wisolated_pawn, Wdoubled_pawn);
        getPawnsInfos(Bpawn_columns, Bisolated_pawn, Bdoubled_pawn);

        if (end_game) {

            // Pair of bishop
            if (wB >= 2)
                material_score += 30;

            if (bB >= 2)
                material_score -= 30;

            // Increase pawn value
            material_score += wP * 150;
            material_score -= bP * 150;

        }

        int castlings_score = 0;
        if (white) {
            if (board->has_castling_w) castlings_score += 100;
            else castlings_score += 25 * getNbCastlings (legal_moves, board->squares, white);
            material_score -= 10 * (Wdoubled_pawn + Wisolated_pawn) + 10 * (Bdoubled_pawn + Bisolated_pawn);
        } else {
            if (board->has_castling_b) castlings_score -= 100;
            else castlings_score -= 25 * getNbCastlings (legal_moves, board->squares, white);
            material_score += 10 * (Bdoubled_pawn + Bisolated_pawn) - 10 * (Wdoubled_pawn + Wisolated_pawn);
        }

        int score = (material_score + castlings_score);

        return Score(score);
    }
}
