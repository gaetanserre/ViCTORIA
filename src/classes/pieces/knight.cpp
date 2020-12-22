#include "knight.h"

Knight::Knight (square position, bool white, bool black) : Piece(position, white, black) {
    this->name = "knight";
}