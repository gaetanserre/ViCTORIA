#include "king.h"

King::King (Square position, bool white) : Piece(position, white) {
    this->name = "king";
    this->is_check = false;
}

bool King::check_move(Square goal, Piece* squares[]) {
    // Test if there is a not takeable piece at the goal
    if (checkIfPiece(squares[squareToIdx(goal)])) {
        if (!checkIfPieceIsTakeable(squares[squareToIdx(goal)])) {
            return false;
        }
    }

    if (this->PlusOrMinus(this->position.line, goal.line, 1)) {
        return this->position.row == goal.row ||
               this->PlusOrMinus(this->position.row, goal.row, 1);
    }

    if (this->position.line == goal.line) {
        return this->PlusOrMinus(this->position.row, goal.row, 1);
    }

    return false;
};