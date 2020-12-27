#include "board.h"
#include <stdio.h>

Board::~Board() {
    for (int i = 0; i<64; i++)
        free(this->squares[i]);
}

void Board::init(string fen) {
    int row = 97; // ASCII for a
    int line = 8;
    int idx = 0;
    int nbspace = 0;

    for (int i = 0; i<fen.length(); i++) {
        square position = {char(row), line};

        if (fen[i] == ' ') {nbspace++; i++;}

        if (nbspace != 0) {

            if (nbspace == 1) {
                if (fen[i] == 'b') this->white = false;
            }
            if (nbspace == 2) {
                switch (fen[i])
                {
                case 'K':
                    this->castling_short_w = true;
                    break;
                case 'k':
                    this->castling_short_b = true;
                    break;
                case 'Q':
                    this->castling_long_w = true;
                    break;
                case 'q':
                    this->castling_long_b = true;
                    break;
                }
            }
            if (nbspace == 3) {
                if (fen[i] != '-') {
                    this->en_passant = true;
                    this->en_passant_square = {fen[i], fen[i+1] - '0'};
                    i++;
                }
            }
            if (nbspace == 4) break;
        }

        else if (fen[i] == 'r') {
            this->squares[idx] = new Rook(position, false);
        } else if (fen[i] == 'n') {
            this->squares[idx] = new Knight(position, false);
        } else if (fen[i] == 'b') {
            this->squares[idx] = new Bishop(position, false);
        } else if (fen[i] == 'q') {
            this->squares[idx] = new Queen(position, false);
        } else if (fen[i] == 'k') {
            this->squares[idx] = new King(position, false);
            this->black_king = this->squares[idx];
        } else if (fen[i] == 'p') {
            this->squares[idx] = new Pawn(position, false, line == 7,
                    &(this->en_passant), &(this->en_passant_square));
        }

        else if (fen[i] == 'R') {
            this->squares[idx] = new Rook(position, true);
        } else if (fen[i] == 'N') {
            this->squares[idx] = new Knight(position, true);
        } else if (fen[i] == 'B') {
            this->squares[idx] = new Bishop(position, true);
        } else if (fen[i] == 'Q') {
            this->squares[idx] = new Queen(position, true);
        } else if (fen[i] == 'K') {
            this->squares[idx] = new King(position, true);
            this->white_king = this->squares[idx];
        } else if (fen[i] == 'P') {
            this->squares[idx] = new Pawn(position, true, line == 2,
                    &(this->en_passant), &(this->en_passant_square));
        }

        else if (fen[i] == '/') {
            line--;
            row = 96; // 97 is for 'a' and 96 is because we increment row at the end of the loop
            idx--;
        } else {
            int nb = fen[i] - '0'; // char to int conversion
                if (nb >= 1 && nb <= 8) {
                    row += nb - 1;
                    for (int i = 0; i<nb; i++) {
                        (this->squares[idx + i]) = new Empty();
                    }

                    idx += nb - 1;
                } else {
                    cout << "Error in fen : " << fen << endl;
                    exit(-1);
                }
        }
        idx++;
        row++;
    }
}

void Board::print_pieces () {
    for (int i = 0; i<64; i++) {
        if (checkIfPiece(this->squares[i]))
            this->squares[i]->print_piece();
    }
}

void Board::print_move (const char* move) {
    square dep = {move[0], int(move[1] - '0')};
    square stop = {move[2], int(move[3] - '0')};
    int idx = squareToIdx(dep);
    if (checkIfPiece(this->squares[idx])) {
        cout << (this->squares[idx]->check_move(stop, this->squares) ? "true" : "false") << endl;
    }
}