#include "king.h"

King::King (square position, bool white, bool black) : Piece(position, white, black) {
    this->name = "king";
    this->is_check = false;
}