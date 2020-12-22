#include "board.h"
#include <stdio.h>

Board::~Board() {
    free(this->pieces);
}

void Board::init(string fen) {
    int row = 97; // ASCII for a
    int line = 8;
    int idx = 0;

    this->pieces = (Piece**) calloc(64, sizeof(Piece*));
    for (int i = 0; i<64; i++) {
        this->pieces[i] = (Piece*) calloc(1, sizeof(Piece));
    }

    for (int i = 0; i<fen.length(); i++) {
        square position = {char(row), line};

        if (fen[i] == ' ') break;

        else if (fen[i] == 'r') {
            (this->pieces[idx]) = new Rook(position, false, true);
        } else if (fen[i] == 'n') {
            (this->pieces[idx]) = new Knight(position, false, true);
        } else if (fen[i] == 'b') {
            (this->pieces[idx]) = new Bishop(position, false, true);
        } else if (fen[i] == 'q') {
            (this->pieces[idx]) = new Queen(position, false, true);
        } else if (fen[i] == 'k') {
            (this->pieces[idx]) = new King(position, false, true);
        } else if (fen[i] == 'p') {
            (this->pieces[idx]) = new Pawn(position, false, true);
        }

        else if (fen[i] == 'R') {
            (this->pieces[idx]) = new Rook(position, true, false);
        } else if (fen[i] == 'N') {
            (this->pieces[idx]) = new Knight(position, true, false);
        } else if (fen[i] == 'B') {
            (this->pieces[idx]) = new Bishop(position, true, false);
        } else if (fen[i] == 'Q') {
            (this->pieces[idx]) = new Queen(position, true, false);
        } else if (fen[i] == 'K') {
            (this->pieces[idx]) = new King(position, true, false);
        } else if (fen[i] == 'P') {
            (this->pieces[idx]) = new Pawn(position, true, false);
        }

        else if (fen[i] == '/') {
            line--;
            row = 96;
            idx--;
        } else {
            int nb = int(fen[i]) - 48;
                if (nb >= 1 && nb <= 8) {
                    row += nb - 1;
                    for (int i = 0; i<nb; i++) {
                        (this->pieces[idx + i]) = new Empty();
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
        if (this->pieces[i]->getName() != "Null")
            this->pieces[i]->print_piece();
    }
}

void Board::print_move (char* move) {
    square s = {'e', 4};
    for (int i = 0; i<64; i++) {
            cout << (this->pieces[i]->check_move(s, s) ? "true" : "false") << endl;
    }
}