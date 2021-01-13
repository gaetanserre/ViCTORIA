#include "pawn.h"

Pawn::Pawn(Square position, bool white,
           bool* en_passant, Square* en_passant_square) : Piece(position, white) {
    this->name = 'p';
    this->en_passant = en_passant;
    this->en_passant_square = en_passant_square;

    this->pieceValue = 100;

    this->table = &pawn_table[0];
    this->table_end_game = &pawn_table_end_game[0];
}

int Pawn::forward (int n) {
    return (this->white ? n : -n);
}

bool Pawn::check_move(Square goal, Piece* squares[], U64 occupancy) {

    bool piece = false;
    bool start_pos = this->white ? (this->position.line == 2) : (this->position.line == 7);

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
        
        else if ((this->position.line + forward(2) == goal.line) && start_pos) {
            // Check if there is a piece between the pawn and the goal
            return !piece &&
                   ! checkIfPiece(squares[squareToIdx(Square(goal.row, goal.line - forward(1)))]);
        }
        
        else return false;

    } else if (PlusOrMinus(this->position.row, goal.row, 1)) {
        if (this->position.line + forward(1) == goal.line) {
            return piece || (*(this->en_passant) && (*this->en_passant_square) == goal);
        }
            
        else return false;

    } else return false;
}

bool Pawn::en_prise(Square goal, Piece* squares[], U64 occupancy) {
    if (PlusOrMinus(this->position.row, goal.row, 1)) {
        return this->position.line + forward(1) == goal.line;
        
    } else return false;
}