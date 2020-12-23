#include "pawn.h"

Pawn::Pawn(square position, bool white, bool start_pos) : Piece(position, white) {
    this->name = "pawn";
    this->start_pos = start_pos;
}

int Pawn::forward (int n) {
    return (this->white ? n : -n);
}

bool Pawn::check_move(square goal, Piece* squares[]) {
    if (this->position.row == goal.row) {
        if (this->position.line + forward(1) == goal.line)
            return ! checkIfPiece(squares[squareToIdx(goal)]);
        
        else if ((this->position.line + forward(2) == goal.line) && this->start_pos)
            return ! checkIfPiece(squares[squareToIdx(goal)]);
        
        else return false;

    } else if (this->position.row + 1 == goal.row || this->position.row - 1 == goal.row) {
        if (this->position.line + forward(1) == goal.line)
            return this->checkIfPieceIsTakeable(squares[squareToIdx(goal)]);
            
        else return false;

    } else return false;
}