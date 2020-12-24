#include "bishop.h"
#include <math.h>

Bishop::Bishop(square position, bool white) : Piece(position, white) {
    this->name = "bishop";
}

bool Bishop::check_move(square goal, Piece* squares[]) {
    // Test if there is a not takeable piece at the goal
    if (checkIfPiece(squares[squareToIdx(goal)])) {
        if (!checkIfPieceIsTakeable(squares[squareToIdx(goal)])) {
            return false;
        }
    }

    int dist = abs(goal.line - this->position.line);
    int count = 1;

    if (this->position.row + dist == goal.row) {

        if (goal.line > this->position.line) {
            int init = this->position.row+1;
            auto test = [=] (int i) {return i < goal.row;};
            auto incr = [] (int *i) {*i = *i+1;};
            auto pos = [this, &count] (int i) -> square {
                square c = {char(i), this->position.line + count};
                count++;
                return c;
            };
            return this->itermove(init, squares, test, incr, pos);

        } else {
            int init = this->position.row+1;
            auto test = [=] (int i) {return i < goal.row;};
            auto incr = [] (int *i) {*i = *i+1;};
            auto pos = [this, &count] (int i) -> square {
                square c = {char(i), this->position.line - count};
                count++;
                return c;
            };
            return this->itermove(init, squares, test, incr, pos);
        }
    } 

    else if (this->position.row - dist == goal.row) {

        if (goal.line > this->position.line) {
            int init = this->position.row-1;
            auto test = [=] (int i) {return i > goal.row;};
            auto incr = [] (int* i) {*i = *i-1;};
            auto pos = [this, &count] (int i) -> square { 
                square c = {char(i), this->position.line + count};
                count++;
                return c;
            };
            return this->itermove(init, squares, test, incr, pos);

        } else {
            int init = this->position.row-1;
            auto test = [=] (int i) {return i > goal.row;};
            auto incr = [] (int* i) {*i = *i-1;};
            auto pos = [this, &count] (int i) -> square { 
                square c = {char(i), this->position.line - count};
                count++;
                return c;
            };
            return this->itermove(init, squares, test, incr, pos);
        }
    }

    return false;
}