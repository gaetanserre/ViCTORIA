#include "rook.h"

Rook::Rook(square position, bool white) : Piece(position, white) {
    this->name = "rook";
}

bool Rook::check_move(square goal, Piece* squares[]) {
    // Test if there is a not takeable piece at the goal
    if (checkIfPiece(squares[squareToIdx(goal)])) {
        if (!checkIfPieceIsTakeable(squares[squareToIdx(goal)])) {
            return false;
        }
    }

    if (this->position.row == goal.row) {
        for (int i = position.line+1; i<goal.line; i++) {
            if (checkIfPiece(squares[squareToIdx({goal.row, i})]))
                return false;
        }
        return true;

    } else if (this->position.line == goal.line) {
        for (int i = position.row+1; i < goal.row ; i++) {
            if (checkIfPiece(squares[squareToIdx({char(i), goal.line})]))
                return false;
        }
        return true;
    } else return false;
}