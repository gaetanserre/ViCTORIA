#include "board.h"
#include <stdio.h>

int lines [] = {1, 2, 3, 4, 5, 6, 7, 8};
enum rows {a = 'a', b = 'b', c='c', d='d', e='e', f='f', g='g'};

Board::Board(string fen) {
    int row = 97; // ASCII for a
    int line = 8;
    int idx = 0;

    for (int i = 0; i<fen.length(); i++) {
        square position = {char(row), line};
        if (fen[i] == ' ') break;
        switch (fen[i]) {
            case 'r' :
                this->pieces[idx] = Rook(position, false, true);
                idx++;
                break;
            case 'n' :
                this->pieces[idx] = Knight(position, false, true);
                idx++;
                break;
            case 'b' :
                this->pieces[idx] = Bishop(position, false, true);
                idx++;
                break;
            case 'q' :
                this->pieces[idx] = Queen(position, false, true);
                idx++;
                break;
            case 'k' : 
                this->pieces[idx] = King(position, false, true);
                idx++;
                break;
            case 'p' : 
                this->pieces[idx] = Pawn(position, false, true);
                idx++;
                break;

            case 'R' :
                this->pieces[idx] = Rook(position, true, false);
                idx++;
                break;
            case 'N' :
                this->pieces[idx] = Knight(position, true, false);
                idx++;
                break;
            case 'B' :
                this->pieces[idx] = Bishop(position, true, false);
                idx++;
                break;
            case 'Q' :
                this->pieces[idx] = Queen(position, true, false);
                idx++;
                break;
            case 'K' : 
                this->pieces[idx] = King(position, true, false);
                idx++;
                break;
            case 'P' : 
                this->pieces[idx] = Pawn(position, true, false);
                idx++;
                break;
            
            case '/' : 
                line--;
                row = 96; //ASCII for char before 'a' because row++ at the end of the for
                break;
            
            default : 
                int nb = int(fen[i]) - 48;
                if (nb >= 1 && nb <= 8) {
                    row += nb - 1;
                    idx += nb;
                    break;
                } else {
                    cout << "Error in fen : " << fen << endl;
                    exit(-1);
                }
        };
        row ++;
    }
    cout << idx << endl;
}

void Board::print_pieces () {
    for (Piece p : this->pieces) {
        if (p.getName() != "Null")
            p.print_piece();
    }
}