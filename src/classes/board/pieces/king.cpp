#include "king.h"

King::King (Square position, bool white) : Piece(position, white) {
    this->name = 'k';
    this->name_str = "King";

    this->pieceValue = 2000;

    this->table = &king_table[0];
    this->table_end_game = &king_table_end_game[0];
}

bool King::check_move(Square goal, Piece* squares[], U64 occupancy) {

    if (PlusOrMinus(this->position.file, goal.file, 1)) {
        return this->position.rank == goal.rank ||
                PlusOrMinus(this->position.rank, goal.rank, 1);
    }

    if (this->position.file == goal.file) {
        return PlusOrMinus(this->position.rank, goal.rank, 1);
    }

    return false;
};

