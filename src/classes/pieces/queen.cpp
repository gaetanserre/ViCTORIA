#include "queen.h"

Queen::Queen (square position, bool white, bool black) : Piece(position, white, black) {
    this->name = "queen";
}