#include "queen.h"
#include "bishop.h"
#include "rook.h"

Queen::Queen (Square position, bool white) : Piece(position, white) {
    this->name = "queen";
}

bool Queen::check_move(Square goal, Piece* squares[]) {
    // Test if there is a not takeable piece at the goal
    if (checkIfPiece(squares[squareToIdx(goal)])) {
        if (!checkIfPieceIsTakeable(squares[squareToIdx(goal)])) {
            return false;
        }
    }

    Bishop bishop(this->position, this->white);
    Rook rook (this->position, this->white);

    return bishop.check_move(goal, squares) || rook.check_move(goal, squares);

};