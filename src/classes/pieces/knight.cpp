#include "knight.h"

Knight::Knight (square position, bool white) : Piece(position, white) {
    this->name = "knight";
}

bool Knight::check_move(square goal, Piece* squares[]) {
    // Test if there is a not takeable piece at the goal
    if (checkIfPiece(squares[squareToIdx(goal)])) {
        if (!checkIfPieceIsTakeable(squares[squareToIdx(goal)])) {
            return false;
        }
    }

    if (this->PlusOrMinus(this->position.line, goal.line, 1)) {
        return this->PlusOrMinus(this->position.row, goal.row, 2);
    }

    if (this->PlusOrMinus(this->position.line, goal.line, 2)) {
        return this->PlusOrMinus(this->position.row, goal.row, 1);
    }

    return false;
}