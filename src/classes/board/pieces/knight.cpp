#include "knight.h"

Knight::Knight (Square position, bool white) : Piece(position, white) {
    this->name = 'n';
    this->name_str = "Knight";

    this->pieceValue = 320;

    this->table = &knight_table[0];
    this->table_end_game = &knight_table[0];
}

bool Knight::check_move(Square goal, Piece* squares[], U64 occupancy) {

    if (PlusOrMinus(this->position.file, goal.file, 1)) {
        return PlusOrMinus(this->position.rank, goal.rank, 2);
    }

    if (PlusOrMinus(this->position.file, goal.file, 2)) {
        return PlusOrMinus(this->position.rank, goal.rank, 1);
    }

    return false;
}