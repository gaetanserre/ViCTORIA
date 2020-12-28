#include "piece.h"

Piece::Piece(Square position, bool white) {
    this->position = position;
    this->white = white;
}

void Piece::print_piece() {
    std::string color = "black";
    if (this->white)
        color = "white";

    std::cout << color << " " << this->name << " " <<
              this->position.row << this->position.line << std::endl;
}

bool Piece::checkIfPieceIsTakeable(Piece* p) {
    if (checkIfPiece(p)) {
        bool A = this->white;
        bool B = p->isWhite();
        return A != B; // XOR
    } else return false;
}


bool Piece::PlusOrMinus(int value1, int value2, int n) {
    return value1 + n == value2 || value1 - n == value2;
}

bool Piece::itermove(
    int init, Piece* squares[],
    std::function<bool(int)> test,
    std::function<void(int*)> incr,
    std::function<Square(int)> pos
) {
    int i = init;
    while (test(i)) {
        Square c = pos(i);
        //std::cout << c.row << c.line << std::endl;
        if (checkIfPiece(squares[squareToIdx(c)])) {
            //squares[squareToIdx(c)]->print_piece();
            return false;
        }
        incr(&i);
    }
    return true;
}




int squareToIdx(Square c) {
    int row = c.row - 97;
    int line = 7 - (c.line - 1);
    return line * 8 + row;
}

Square IdxToSquare(int idx) {
    char row = 'a' + idx % 8;
    int line = 1 + idx / 8;
    return Square(row, line);
}

bool checkIfPiece(Piece *p) {
    return p->getName() != "Null";
}
