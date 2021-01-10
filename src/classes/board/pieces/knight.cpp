#include "knight.h"

Knight::Knight (Square position, bool white) : Piece(position, white) {
    this->name = 'n';

    this->pieceValue = 320;

    this->table = &knight_table[0];
    this->table_end_game = &knight_table[0];
}

bool Knight::check_move(Square goal, Piece* squares[]) {

    if (this->PlusOrMinus(this->position.line, goal.line, 1)) {
        return this->PlusOrMinus(this->position.row, goal.row, 2);
    }

    if (this->PlusOrMinus(this->position.line, goal.line, 2)) {
        return this->PlusOrMinus(this->position.row, goal.row, 1);
    }

    return false;
}