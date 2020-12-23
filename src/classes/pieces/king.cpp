#include "king.h"

King::King (square position, bool white) : Piece(position, white) {
    this->name = "king";
    this->is_check = false;
}