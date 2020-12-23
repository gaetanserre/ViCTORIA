#include "knight.h"

Knight::Knight (square position, bool white) : Piece(position, white) {
    this->name = "knight";
}