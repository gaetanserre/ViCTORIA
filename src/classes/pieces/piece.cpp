#include "piece.h"

Piece::Piece(square position, bool white, bool black) {
    this->position = position;
    this->white = white;
    this->black = black;
}

void Piece::print_piece() {
    std::cout << this->name << " " << this->position.letter << this->position.number << std::endl;
}