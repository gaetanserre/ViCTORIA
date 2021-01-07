#include "pawn.h"

Pawn::Pawn(Square position, bool white, bool start_pos,
           bool* en_passant, Square* en_passant_square) : Piece(position, white) {
    this->name = "pawn";
    this->start_pos = start_pos;
    this->en_passant = en_passant;
    this->en_passant_square = en_passant_square;

    this->pieceValue = 100;

    this->table = &pawn_table[0];
    this->table_end_game = &pawn_table_end_game[0];
}

int Pawn::forward (int n) {
    return (this->white ? n : -n);
}

bool Pawn::check_move(Square goal, Piece* squares[]) {

    bool piece = false;

    // Test if there is a not takeable piece at the goal
    if (checkIfPiece(squares[squareToIdx(goal)])) {
        piece = true;
        if (!checkIfPieceIsTakeable(squares[squareToIdx(goal)])) {
            return false;
        }
    }

    if (this->position.row == goal.row) {
        if (this->position.line + forward(1) == goal.line)
            return !piece;
        
        else if ((this->position.line + forward(2) == goal.line) && this->start_pos) {
            // Check if there is a piece between the pawn and the goal
            return !piece &&
                   ! checkIfPiece(squares[squareToIdx(Square(goal.row, goal.line - forward(1)))]);
        }
        
        else return false;

    } else if (this->PlusOrMinus(this->position.row, goal.row, 1)) {
        if (this->position.line + forward(1) == goal.line) {
            return piece || (*(this->en_passant) && (*this->en_passant_square) == goal);
        }
            
        else return false;

    } else return false;
}

bool Pawn::en_prise(Square goal, Piece* squares[]) {
    if (this->PlusOrMinus(this->position.row, goal.row, 1)) {
        if (this->position.line + forward(1) == goal.line)
        
            return 
                this->checkIfPieceIsTakeable(squares[squareToIdx(goal)]) ||
                (*(this->en_passant) && (*this->en_passant_square) == goal);
            
        else return false;

    } else return false;
}