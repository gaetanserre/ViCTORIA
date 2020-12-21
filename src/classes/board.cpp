#include "board.h"

int lines [] = {1, 2, 3, 4, 5, 6, 7, 8};
char rows [] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};

Board::Board(string fen) {
    for (char c : rows) {
        square s {c, 2};
        Pawn p(s, true, false); //white pawns
        pieces.push_back(p);
    }
}

void Board::print_pieces () {
    for (Piece p : this->pieces) {
        p.print_piece();
    }
}