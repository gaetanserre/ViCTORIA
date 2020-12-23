#include "bishop.h"

Bishop::Bishop(square position, bool white) : Piece(position, white) {
    this->name = "bishop";
}