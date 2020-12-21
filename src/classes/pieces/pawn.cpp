#include "pawn.h"

Pawn::Pawn(square position, bool white, bool black) : Piece(position, white, black) {
    this->name = "Pawn";
    this->start_pos = true;
}