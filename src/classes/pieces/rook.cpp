#include "rook.h"

Rook::Rook(square position, bool white, bool black) : Piece(position, white, black) {
    this->name = "rook";
}