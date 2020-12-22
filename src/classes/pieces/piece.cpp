#include "piece.h"

Piece::Piece(square position, bool white, bool black) {
    this->position = position;
    this->white = white;
    this->black = black;
}

void Piece::print_piece() {
    std::string color = "black";
    if (this->white)
        color = "white";

    std::cout << color << " " << this->name << " " <<
              this->position.row << this->position.line << std::endl;
}

int Piece::squareToIdx(square c) {
    int row = c.row - 97;
    int line = c.line - 1;
    return line * 8 + row;
}