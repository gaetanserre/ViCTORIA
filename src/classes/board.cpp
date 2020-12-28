#include "board.h"
#include <stdio.h>

Board::~Board() {
    for (int i = 0; i<64; i++)
        free(this->squares[i]);
}

void Board::init (string fen) {
    int row = 97; // ASCII for a
    int line = 8;
    int idx = 0;
    int nbspace = 0;

    for (int i = 0; i<fen.length(); i++) {
        Square position(char(row), line);

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
                    this->en_passant_square = Square(fen[i], fen[i+1] - '0');
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

    cout << this->castling_long_w << " " << castling_short_w << endl;
    cout << this->castling_long_b << " " << castling_short_b << endl;

    if (this->en_passant) {
        cout << this->en_passant_square.row << this->en_passant_square.line << endl;
    }

}

bool Board::isTakeable (Square s) {
    for (int i = 0; i<64; i++) {
        if (checkIfPiece (this->squares[i]) && 
            this->white != this->squares[i]->isWhite()) {
                if (this->squares[i]->en_prise (s, this->squares))
                    return true;
            }
    }
    return false;
}

bool Board::isCheck() {
    if (this->white) 
        return isTakeable (this->white_king->getPosition());
    else
        return isTakeable (this->black_king->getPosition());
}

bool Board::check_castle (ply p) {
    Square dep = p.dep; Square stop = p.stop;

    Square l[3];
    int size;
    bool castling = false;
    int line = this->white ? 1 : 8;
    bool c_short = this->white ? this->castling_short_w : this->castling_short_b;
    bool c_long = this->white ? this->castling_long_w : this->castling_long_b;

    if (dep == Square('e', line)) {
        if (stop == Square('g', line) && c_short) {
            l[0] = Square('f', line); l[1] = Square('g', line);
            size = 2;
            castling = true;
        }

        if (stop == Square('c', line) && c_long) {
            l[0] = Square('d', line); l[1] = Square('c', line);
            l[2] = Square('b', line);
            size = 3;
            castling = true;
        }
    }

    /*
        We first check if the king is in check,
        then if there is a piece blocking the castle 
        and finally, if any the cases is en prise.
        It's more efficient to do 2 for loops 
        because it's much more easy to verify is there a piece blocking the castle.
    */

    if (castling) {
        if (isCheck()) return false;

        for (int i = 0; i<size; i++) {
            if (checkIfPiece(this->squares[squareToIdx(l[i])]))
                return false;
        }

        for (int i = 0; i<size; i++) {
            if (isTakeable(l[i])) return false;
        }
        return true;
    }
    return false;
}

void Board::remove_s_castle() {
    if (this->white)
        this->castling_short_w = false;
    else
        this->castling_short_b = false;
}

void Board::remove_l_castle() {
    if (this->white)
        this->castling_long_w = false;
    else
        this->castling_long_b = false;
}

void Board::remove_castles () {
    remove_s_castle();
    remove_l_castle();
}

/*
    We assume that we already call check_castle
*/
void Board::play_castle (ply p) {
    Square dep = p.dep; Square stop = p.stop;
    int line = this->white ? 1 : 8;
    bool c_short = stop == Square('g', line);

    if (c_short) {
        //Move king
        Piece* temp = this->squares[squareToIdx(Square('e', line))];
        temp->setPosition(Square('g', line));
        this->squares[squareToIdx(Square('g', line))] = temp;
        this->squares[squareToIdx(Square('e', line))] = new Empty();

        //Move rook
        Piece* temp2 = this->squares[squareToIdx(Square('h', line))];
        temp2->setPosition(Square('f',line));
        this->squares[squareToIdx(Square('f', line))] = temp2;
        this->squares[squareToIdx(Square('h', line))] = new Empty();

    } else {
        //Move king
        Piece* temp = this->squares[squareToIdx(Square('e', line))];
        temp->setPosition(Square('c', line));
        this->squares[squareToIdx(Square('c', line))] = temp;
        this->squares[squareToIdx(Square('e', line))] = new Empty();

        //Move rook
        Piece* temp2 = this->squares[squareToIdx(Square('a', line))];
        temp2->setPosition(Square('d',line));
        this->squares[squareToIdx(Square('d', line))] = temp2;
        this->squares[squareToIdx(Square('a', line))] = new Empty();
    }

    remove_castles();
    this->white = not white;
}

bool Board::check_move_min (ply p) {
    Square dep = p.dep; Square stop = p.stop;
    int idx_dep = squareToIdx(dep);
    if (checkIfPiece(this->squares[idx_dep])) {
        if (this->squares[idx_dep]->isWhite() == this->white) { 
            return this->squares[idx_dep]->check_move(stop, this->squares);
        }
    }
    return false;
}

bool isPromote (Piece* p) {
    if (p->getName() == "pawn") {
        if (p->isWhite()) return p->getPosition().line == 7;
        else return p->getPosition().line == 2;
    }
    return false;
}

bool Board::check_move (ply p) {
    Square dep = p.dep;
    Square stop = p.stop;
    int idx_dep = squareToIdx(dep);
    int idx_stop = squareToIdx(stop);

    /*
        If the move is playable, play it and then check if the king is in check. 
        If it is the case, return to the previous position.
    */
    if (check_move_min ({dep, stop})) {
        Piece* temp = this->squares[idx_dep];
        Piece* temp_stop = this->squares[idx_stop];

        // Promotion
        if (p.promote) {
            if (! isPromote (this->squares[idx_dep])) return false;
            if (p.prom == 'q')
                this->squares[idx_stop] = new Queen(stop, temp->isWhite());
            else
                this->squares[idx_stop] = new Knight(stop, temp->isWhite());
        } else {
            temp->setPosition(stop);
            this->squares[idx_stop] = temp;
        }

        this->squares[idx_dep] = new Empty();

        
        if (isCheck()) {
            this->squares[idx_dep] = temp;
            this->squares[idx_dep]->setPosition(dep);
            this->squares[idx_stop] = temp_stop;
            return false;
        }

        this->squares[idx_dep] = temp;
        this->squares[idx_dep]->setPosition(dep);
        this->squares[idx_stop] = temp_stop;
        return true;
    }

    // If the move was illegal, we check if it was a castle.
    return check_castle({dep, stop});
}

bool Board::play_move(const char* move) {
    Square dep = Square(move[0], int(move[1] - '0'));
    Square stop = Square(move[2], int(move[3] - '0'));

    ply p;

    if (strlen(move) == 5) {
        p = {dep, stop, true, move[4]};
    } else
        p = {dep, stop, false, ' '};

    bool find = false;

    for (ply m : this->legal_moves) {
        if (m.dep == p.dep && m.stop == p.stop) {
            find = true;
            break;
        }
    }

    if (find) {

        int line = this->white ? 1 : 8;
        bool castling = false;

        if (dep == Square('e', line)) {
            castling = stop == Square('g', line) || stop == Square('c', line);    
        }

        if (! castling) {
            int idx_dep = squareToIdx(dep);
            int idx_stop = squareToIdx(stop);

            Piece* temp = this->squares[idx_dep];
            this->squares[idx_dep] = new Empty();

            if (p.promote) {
                if (p.prom == 'q')
                    this->squares[idx_stop] = new Queen(stop, temp->isWhite());
                else
                    this->squares[idx_stop] = new Knight(stop, temp->isWhite());
            } else {
                temp->setPosition(stop);
                /*
                    If we want to play the move, we check castles are still possible 
                    and we change side
                */
                if (temp->getName() == "king") remove_castles();
                if (temp->getName() == "rook") {
                    if (dep.row == 'a') {
                        remove_l_castle();
                    }
                    if (dep.row == 'h') {
                        remove_s_castle();
                    }
                }

                /*
                    We check pawn
                */
                if (temp->getName() == "pawn") {
                    temp = new Pawn(temp->getPosition(), temp->isWhite(), false,
                                &(this->en_passant), &(this->en_passant_square));
                    
                    // If pawn move 2 squares ahead
                    if (abs(dep.line - stop.line) == 2) {
                        this->en_passant = true;
                        if (this->white)
                            this->en_passant_square = Square(stop.row, stop.line-1);
                        else
                            this->en_passant_square = Square(stop.row, stop.line+1);
                    } else
                        this->en_passant = false;

                    // If takes en passant
                    if (stop == this->en_passant_square) {
                        cout << "too" << endl;
                        if (this->white) {
                            this->squares[squareToIdx(Square(stop.row, stop.line-1))] = new Empty();
                        } else
                            this->squares[squareToIdx(Square(stop.row, stop.line+1))] = new Empty();

                        this->en_passant = false;
                    }
                // en passant become false after moving a piece that is not a pawn
                } else 
                    this->en_passant = false;
                
                this->squares[idx_stop] = temp;
            }

            this->white = !this->white;
            this->squares[idx_dep] = new Empty();

            return true;

        } else {
            play_castle(p);
            return true;
        }

    } else return false;
}


void Board::getLegalMoves () {
    this->legal_moves.resize(0);
    for(int i = 0; i<64; i++) {
        for (int j = 0; j<64; j++) {
            if (checkIfPiece(this->squares[i]) && this->squares[i]->isWhite() == this->white) {
                Square dep = this->squares[i]->getPosition();
                Square stop = IdxToSquare(j);
                int line = this->white ? 8 : 1;

                if (this->squares[i]->getName() == "pawn" && stop.line == line) {
                    if (check_move({dep, stop, true, 'q'}))
                        this->legal_moves.push_back({dep, stop, true, 'q'});

                    if (check_move({dep, stop, true, 'n'}))
                        this->legal_moves.push_back({dep, stop, true, 'n'});
                } 
                
                else {
                    if (check_move({dep, stop, false, ' '}))
                        this->legal_moves.push_back({dep, stop, false, ' '});
                }
            }
        }
    }
    
    for (ply p : this->legal_moves) {
        if (p.promote)
            cout << p.dep.row << p.dep.line << p.stop.row << p.stop.line << p.prom << endl;
        else
            cout << p.dep.row << p.dep.line << p.stop.row << p.stop.line << endl;
    }
    cout << this->legal_moves.size() << endl;
}

bool Board::isCheckmate(vector<ply> legal_moves) {
    return legal_moves.size() == 0 && isCheck();
}

bool Board::isStalemate(vector<ply> legal_moves) {
    return legal_moves.size() == 0 && !isCheck();
}

bool Board::isOver() {
    getLegalMoves();
    if (isCheckmate(this->legal_moves)) {
        cout << (this->white ? "Black" : "White") << " wins." << endl;
        return true;
    }

    if (isStalemate(this->legal_moves)) {
        cout << "Stalemate." << endl;
        return true;
    }

    return false;
}