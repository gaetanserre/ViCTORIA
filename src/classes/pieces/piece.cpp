#include "piece.h"

Piece::Piece(square position, bool white, bool black) {
    this->position = position;
    this->white = white;
    this->black = black;
}

Piece::Piece() {
    this->name = "Null";
}

void Piece::print_piece() {
    std::string color = "black";
    if (this->white)
        color = "white";

    std::cout << color << " " << this->name << " " <<
              this->position.letter << this->position.number << std::endl;
}