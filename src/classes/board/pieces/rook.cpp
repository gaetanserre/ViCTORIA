#include "rook.h"

Rook::Rook(Square position, bool white) : Piece(position, white) {
    this->name = "rook";

    this->pieceValue = 500;

    this->table = &rook_table[0];
    this->table_end_game = &rook_table[0];
}

bool Rook::check_move(Square goal, Piece* squares[]) {
    // Test if there is a not takeable piece at the goal
    if (checkIfPiece(squares[squareToIdx(goal)])) {
        if (!checkIfPieceIsTakeable(squares[squareToIdx(goal)])) {
            return false;
        }
    }

    if (this->position.row == goal.row) {
        if (goal.line > this->position.line) {
            int init = this->position.line+1;
            auto test = [=] (int i) {return i < goal.line;};
            auto incr = [] (int* i) {*i = *i+1;};
            auto pos = [=] (int i) -> Square {
                return Square(goal.row, i); 
            };
            return this->itermove(init, squares, test, incr, pos);

        } else {
            int init = this->position.line-1;
            auto test = [=] (int i) {return i > goal.line;};
            auto incr = [] (int* i) {*i = *i-1;};
            auto pos = [=] (int i) -> Square {
                return Square(goal.row, i); 
            };
            return this->itermove(init, squares, test, incr, pos);
        }
    } 
    
    else if (this->position.line == goal.line) {
        if (goal.row > this->position.row) {
            int init = this->position.row+1;
            auto test = [=] (int i) {return i < goal.row;};
            auto incr = [] (int* i) {*i = *i+1;};
            auto pos = [=] (int i) -> Square {
                return Square(char(i), goal.line);
            };
            return this->itermove(init, squares, test, incr, pos);
        }

        else {
            int init = this->position.row-1;
            auto test = [=] (int i) {return i > goal.row;};
            auto incr = [] (int* i) {*i = *i-1;};
            auto pos = [=] (int i) -> Square {
                return Square(char(i), goal.line);
            };
            return this->itermove(init, squares, test, incr, pos);
        }

    } else return false;
}