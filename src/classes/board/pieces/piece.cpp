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
              this->position.rank << this->position.file <<
              " value : " << this->getPieceValue(false) << std::endl;
}

bool Piece::checkIfPieceIsTakeable(Piece* p) {
    if (checkIfPiece(p)) {
        bool A = this->white;
        bool B = p->isWhite();
        return A != B; // XOR
    } else return false;
}


bool PlusOrMinus(int value1, int value2, int n) {
    return value1 + n == value2 || value1 - n == value2;
}

int squareToIdx(Square c) {
    int rank = c.rank - 97;
    int file = 7 - (c.file - 1);
    return file * 8 + rank;
}

Square IdxToSquare(int idx) {
    char rank = 'a' + idx % 8;
    int file = 9 - (1 + idx / 8);
    return Square(rank, file);
}

bool checkIfPiece(Piece *p) {
    return p->getName() != 'z';
}

float Piece::getPieceValue (bool end_game) {
    Square pos = this->white ? this->position : Square (this->position.rank, 8 - this->position.file + 1);

    float score = this->pieceValue;

    if (end_game)
        score += this->table_end_game[squareToIdx(pos)];
    else 
        score += this->table[squareToIdx(pos)];

    return this->white ? score : -score;
}
