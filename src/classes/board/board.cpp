#include "board.h"

Board::~Board() {
    for (int i = 0; i<64; i++)
        delete this->squares[i];
}

void Board::init (string fen) {

    this->occupancy = 0ULL;

    this->nb_piece = 0;
    this->nb_pawn = 0;

    int row = 97; // ASCII for 'a'
    int line = 8;
    int idx = 0;
    int nbspace = 0;
    string nb_moves_str = "";

    for (int i = 0; i<fen.length(); i++) {
        Square position(char(row), line);

        if (fen[i] == ' ') {nbspace++; i++;}

        if (nbspace != 0) {

            if (nbspace == 1) {
                if (fen[i] == 'b') this->white = false;
                else this->white = true;
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
                } else this->en_passant = false;
            }
            if (nbspace == 5) {
                nb_moves_str += fen[i];
            }
        }

        else if (fen[i] == 'r') {
            this->squares[idx] = new Rook(position, false, &this->magic_bitboard);
            this->nb_piece++;

            set_bit(this->occupancy, squareToIdx(position));

        } else if (fen[i] == 'n') {
            this->squares[idx] = new Knight(position, false);
            this->nb_piece++;

            set_bit(this->occupancy, squareToIdx(position));

        } else if (fen[i] == 'b') {
            this->squares[idx] = new Bishop(position, false, &this->magic_bitboard);
            this->nb_piece++;
            
            set_bit(this->occupancy, squareToIdx(position));
            
        } else if (fen[i] == 'q') {
            this->squares[idx] = new Queen(position, false, &this->magic_bitboard);
            this->nb_piece++;

            set_bit(this->occupancy, squareToIdx(position));
            
        } else if (fen[i] == 'k') {
            this->squares[idx] = new King(position, false);
            this->nb_piece++;
            this->black_king = this->squares[idx];

            set_bit(this->occupancy, squareToIdx(position));

        } else if (fen[i] == 'p') {
            this->squares[idx] = new Pawn(position, false,
                    &(this->en_passant), &(this->en_passant_square));
            this->nb_piece++;
            this->nb_pawn++;

            set_bit(this->occupancy, squareToIdx(position));

        }

        else if (fen[i] == 'R') {
            this->squares[idx] = new Rook(position, true, &this->magic_bitboard);
            this->nb_piece++;

            set_bit(this->occupancy, squareToIdx(position));

        } else if (fen[i] == 'N') {
            this->squares[idx] = new Knight(position, true);
            this->nb_piece++;

            set_bit(this->occupancy, squareToIdx(position));

        } else if (fen[i] == 'B') {
            this->squares[idx] = new Bishop(position, true, &this->magic_bitboard);
            this->nb_piece++;

            set_bit(this->occupancy, squareToIdx(position));

        } else if (fen[i] == 'Q') {
            this->squares[idx] = new Queen(position, true, &this->magic_bitboard);
            this->nb_piece++;

            set_bit(this->occupancy, squareToIdx(position));

        } else if (fen[i] == 'K') {
            this->squares[idx] = new King(position, true);
            this->nb_piece++;
            this->white_king = this->squares[idx];

            set_bit(this->occupancy, squareToIdx(position));

        } else if (fen[i] == 'P') {
            this->squares[idx] = new Pawn(position, true,
                    &(this->en_passant), &(this->en_passant_square));
            this->nb_piece++;
            this->nb_pawn++;

            set_bit(this->occupancy, squareToIdx(position));

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
    this->nb_moves = stoi(nb_moves_str);
}

void Board::printPieces () {
    for (int i = 0; i<64; i++) {
        if (checkIfPiece(this->squares[i]))
            this->squares[i]->print_piece();
    }

    cout << this->castling_long_w << " " << castling_short_w << endl;
    cout << this->castling_long_b << " " << castling_short_b << endl;

    if (this->en_passant) {
        cout << this->en_passant_square.row << this->en_passant_square.line << endl;
    }
    cout << "pieces: " << this->nb_piece << endl;
    cout << "pawns: " << this->nb_pawn << endl;
    cout << "last_move_capture: " << this->last_move_capture << endl;
}

void Board::printLegalMoves () {
    computeLegalMoves();
    for (Ply p : this->legal_moves) {
        if (p.promote)
            cout << p.dep.row << p.dep.line << p.stop.row << p.stop.line << p.prom << endl;
        else
            cout << p.dep.row << p.dep.line << p.stop.row << p.stop.line << endl;
    }
    cout << "nb: " << this->legal_moves.size() << endl;
} 

bool Board::isTakeable (Square s) {
    if (s.line < 1 || s.line > 8) return true; // Bug to fix
    for (int i = 0; i<64; i++) {
        if (checkIfPiece (this->squares[i]) && this->squares[i]->isWhite() != this->white) {
            if (this->squares[i]->en_prise (s, this->squares, this->occupancy))
                return true;
            }
    }
    return false;
}

bool Board::isCheck () {
    if (this->white){
        return isTakeable (this->white_king->getPosition());
    }
    else {
        return isTakeable (this->black_king->getPosition());
    }
}

bool Board::check_castle (Ply p) {
    Square dep = p.dep; Square stop = p.stop;

    Square l[3];
    int size = 2;
    bool castling = false;
    int line = this->white ? 1 : 8;
    bool c_short = this->white ? this->castling_short_w : this->castling_short_b;
    bool c_long = this->white ? this->castling_long_w : this->castling_long_b;

    if (c_short || c_long) {

        if (dep == Square('e', line)) {
            if (stop == Square('g', line) && c_short) {
                l[0] = Square('f', line); l[1] = Square('g', line);
                castling = true;
            }

            if (stop == Square('c', line) && c_long) {
                l[0] = Square('d', line); l[1] = Square('c', line);
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
    }

    return false;
}

void Board::remove_s_castle () {
    if (this->white)
        this->castling_short_w = false;
    else
        this->castling_short_b = false;
}

void Board::remove_l_castle () {
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
void Board::play_castle (Ply p) {
    Square dep = p.dep; Square stop = p.stop;
    int line = this->white ? 1 : 8;
    bool c_short = stop == Square('g', line);

    if (c_short) {

        int idx_h = squareToIdx(Square('h', line));
        int idx_e = squareToIdx(Square('e', line));
        int idx_f = squareToIdx(Square('f', line));
        int idx_g = squareToIdx(Square('g', line));

        //Move king
        Piece* temp = this->squares[idx_e];
        temp->setPosition(Square('g', line));

        // Prevent memory leak
        delete this->squares[idx_g];
        this->squares[idx_g] = temp;

        this->squares[idx_e] = new Empty();

        //Move rook
        Piece* temp2 = this->squares[idx_h];
        temp2->setPosition(Square('f',line));

        // Prevent memory leak
        delete this->squares[idx_f];
        this->squares[idx_f] = temp2;

        this->squares[idx_h] = new Empty();

        pop_bit (this->occupancy, idx_h);
        pop_bit (this->occupancy, idx_e);

        set_bit (this->occupancy, idx_f);
        set_bit (this->occupancy, idx_g);

    } else {

        int idx_e = squareToIdx(Square('e', line));
        int idx_c = squareToIdx(Square('c', line));
        int idx_d = squareToIdx(Square('d', line));
        int idx_a = squareToIdx(Square('a', line));

        //Move king
        Piece* temp = this->squares[idx_e];
        temp->setPosition(Square('c', line));

        // Prevent memory leak
        delete this->squares[idx_c];
        this->squares[idx_c] = temp;

        this->squares[idx_e] = new Empty();

        //Move rook
        Piece* temp2 = this->squares[idx_a];
        temp2->setPosition(Square('d',line));

        // Prevent memory leak
        delete this->squares[idx_d];
        this->squares[idx_d] = temp2;
        
        this->squares[idx_a] = new Empty();

        pop_bit (this->occupancy, idx_e);
        pop_bit (this->occupancy, idx_a);

        set_bit (this->occupancy, idx_c);
        set_bit (this->occupancy, idx_d);
    }

    remove_castles();
    this->white = !this->white;
    this->nb_moves++;
}

bool Board::check_move_min (int start_idx, Square stop) {
    return this->squares[start_idx]->check_move(stop, this->squares, this->occupancy);
}

bool isPromote (Piece* p) {
    if (p->getName() == 'p') {
        if (p->isWhite()) return p->getPosition().line == 7;
        else return p->getPosition().line == 2;
    }
    return false;
}

bool Board::check_move (Ply p) {
    
    Square start = p.dep;
    Square stop = p.stop;
    int start_idx = squareToIdx(start);
    int stop_idx = squareToIdx(stop);

    if (check_castle(p)) {
        return true;

    } else if (check_move_min(start_idx, stop)) {


        Piece* temp = this->squares[start_idx];
        Piece* temp_stop = this->squares[stop_idx];

        temp->setPosition(stop);
        this->squares[stop_idx] = temp;

        this->squares[start_idx] = new Empty();

        U64 old_occupancy = this->occupancy;
        pop_bit (this->occupancy, start_idx);
        set_bit (this->occupancy, stop_idx);

        // We check for en passant
        int e_p_idx;
        bool e_p = false;
        Piece* e_p_pawn;
        if (this->en_passant && temp->getName() == 'p' && stop == this->en_passant_square) {
            e_p = true;
            e_p_idx = squareToIdx (Square (this->en_passant_square.row, start.line));
            e_p_pawn = this->squares[e_p_idx];
            this->squares[e_p_idx] = new Empty();
        }

        bool check = isCheck();

        delete this->squares[start_idx];

        this->squares[start_idx] = temp;
        this->squares[start_idx]->setPosition(start);
        this->squares[stop_idx] = temp_stop;

        this->occupancy = old_occupancy;

        // If there was en passant
        if (e_p) {
            delete this->squares[e_p_idx];
            this->squares[e_p_idx] = e_p_pawn;
        }

        return !check;

    } else {
        return false;
    }
}

bool Board::play_move (Ply p, bool force) {
    Square dep = p.dep;
    Square stop = p.stop;

    bool found = false;

    if (! force) {
        for (Ply m : this->legal_moves) {
            if (m.dep == p.dep && m.stop == p.stop) {
                found = true;
                break;
            }
        }
    }

    if (found || force) {

        this->fens.push_back(getFen());
        
        this->en_passant = false;

        int line = this->white ? 1 : 8;
        bool castling = false;
        int idx_dep = squareToIdx(dep);

        if (dep == Square('e', line)) {
            castling = (stop == Square('g', line) || stop == Square('c', line)) && 
                        this->squares[idx_dep]->getName() == 'k';    
        }

        if (! castling) {
            int idx_stop = squareToIdx(stop);

            Piece* temp = this->squares[idx_dep];
            this->squares[idx_dep] = new Empty();

            this->last_move_capture = checkIfPiece(this->squares[idx_stop]);

            /*
                We check if we are capturing a rook, we need to remove castles
            */
           if (this->squares[idx_stop]->getName() == 'r') {
               if (stop.row == 'a') {
                        remove_l_castle();
                    }
                if (stop.row == 'h') {
                        remove_s_castle();
                }
           }

            delete this->squares[idx_stop];

            pop_bit(this->occupancy, idx_dep);
            set_bit(this->occupancy, idx_stop);

            // Promotion
            if (p.promote) {
                if (p.prom == 'q') {
                    this->squares[idx_stop] = new Queen(stop, temp->isWhite(), &this->magic_bitboard);
                }
                else if (p.prom == 'n') {
                    this->squares[idx_stop] = new Knight(stop, temp->isWhite());
                }
                else if (p.prom == 'r') {
                    this->squares[idx_stop] = new Rook(stop, temp->isWhite(), &this->magic_bitboard);
                }
                else if (p.prom == 'b') {
                    this->squares[idx_stop] = new Bishop(stop, temp->isWhite(), &this->magic_bitboard);
                }
                this->nb_pawn--;
                delete temp;

            } else {
                temp->setPosition(stop);
                /*
                    We remove castles if we move the king or one of the rook
                */
                if (temp->getName() == 'k') remove_castles();
                if (temp->getName() == 'r') {
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
                if (temp->getName() == 'p') {                   
                    // If pawn move 2 squares ahead
                    if (abs(dep.line - stop.line) == 2) {
                        this->en_passant = true;

                        if (this->white)
                            this->en_passant_square = Square(stop.row, stop.line-1);
                        else
                            this->en_passant_square = Square(stop.row, stop.line+1);
                    }

                    // If takes en passant
                    else if (stop == this->en_passant_square) {
                        int idx = squareToIdx(Square(stop.row, dep.line));

                        this->last_move_capture = true;

                        delete this->squares[idx];
                        this->squares[idx] = new Empty();

                        pop_bit (this->occupancy, idx);
                    }
                }
                
                this->squares[idx_stop] = temp;
            }


            this->white = !this->white;

            this->nb_moves++;

            return true;

        } else {
            this->last_move_capture = false;
            play_castle(p);
            return true;
        }

    } else  {
        return false;
    }
}

bool Board::play_move (string p) {
    return play_move(Board::StringToPly(p));
}

void Board::computeLegalMoves () {
    this->legal_moves = vector<Ply> ();
    this->nb_piece = 0;
    this->nb_pawn = 0;

    for(int i = 0; i<64; i++) {
        if (checkIfPiece(this->squares[i])) {
            nb_piece++;
            if (this->squares[i]->getName() == 'p') this->nb_pawn++;

            if (this->squares[i]->isWhite() == this->white) {

                for (int j = 0; j<64; j++) {

                    if (!checkIfPiece(this->squares[j]) || this->squares[j]->isWhite() != this->white) {

                        Square dep = this->squares[i]->getPosition();
                        Square stop = IdxToSquare(j);
                        int line = this->white ? 8 : 1;

                        if (check_move({dep, stop})) {
                            if (this->squares[i]->getName() == 'p' && stop.line == line) {
                                
                                this->legal_moves.push_back(Ply (dep, stop, true, 'q'));
                                this->legal_moves.push_back(Ply (dep, stop, true, 'q'));
                                this->legal_moves.push_back(Ply (dep, stop, true, 'q'));
                                this->legal_moves.push_back(Ply (dep, stop, true, 'q'));
                            }
                            else
                                this->legal_moves.push_back(Ply (dep, stop));
                        }
                    }
                }
            }
        }
    }
}


bool Board::isCheckmate (int size) {
    return size == 0 && isCheck();
}

bool Board::isStalemate (int size) {
    return size == 0 && !isCheck();
}

bool Board::isOver () {
    int legal_moves_size = this->legal_moves.size();
    return isCheckmate(legal_moves_size) || isStalemate(legal_moves_size);
}


void Board::undo_move() {
    string fen = this->fens.back();
    this->fens.pop_back();

    for (int i = 0; i<64; i++) {
        delete this->squares[i];
    }
        
    init(fen);
}

string Board::getFen (bool nb_move) {
    string fen = "";

    int empty = 0;
    for (int i = 0; i<64; i++) {
        if (i % 8 == 0 && i != 0) {
            if (empty > 0)
                fen += to_string(empty); empty = 0;
            fen += "/";
        }

        if (! checkIfPiece(this->squares[i]))
            empty++;
        else {
            if (empty > 0) fen += to_string(empty); empty = 0;

            char name = this->squares[i]->getName();
            bool white = this->squares[i]->isWhite();

            if (name == 'k')
                fen += (white ? "K" : "k");
            if (name == 'q')
                fen += (white ? "Q" : "q");
            if (name == 'r')
                fen += (white ? "R" : "r");
            if (name == 'b')
                fen += (white ? "B" : "b");
            if (name == 'n')
                fen += (white ? "N" : "n");
            if (name == 'p')
                fen += (white ? "P" : "p");
        }
    }

    if (empty > 0)
        fen += to_string(empty);

    fen += " ";
    fen += (this->white ? "w " : "b ");

    if (this->castling_short_w ||
        this->castling_short_b ||
        this->castling_long_w ||
        this->castling_long_b) {

        fen += (this->castling_short_w ? "K" : "");
        fen += (this->castling_long_w ? "Q" : "");
        fen += (this->castling_short_b ? "k" : "");
        fen += (this->castling_long_b ? "q " : " ");
    } else
        fen += "- ";

    if (this->en_passant)
        fen += this->en_passant_square.row + to_string(this->en_passant_square.line) + " ";
    else
        fen += "-";

    if (nb_move)
        fen += " 0 " + to_string((this->nb_moves - 1) / 2 + 1);

    return fen;
}

Ply Board::StringToPly (string ply) {
    Square dep = Square(ply[0], int(ply[1] - '0'));
    Square stop = Square(ply[2], int(ply[3] - '0'));


    if (ply.size() == 5) {
        return Ply (dep, stop, true, ply[4]);
    } else
        return Ply (dep, stop);
}