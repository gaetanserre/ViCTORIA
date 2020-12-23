#include "queen.h"

Queen::Queen (square position, bool white) : Piece(position, white) {
    this->name = "queen";
}