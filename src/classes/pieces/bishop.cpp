#include "bishop.h"

Bishop::Bishop(square position, bool white, bool black) : Piece(position, white, black) {
    this->name = "bishop";
}