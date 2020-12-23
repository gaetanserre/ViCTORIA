#pragma once

#include <iostream>
#include <string>

struct square {
    char row;
    int line;
};

class Piece {
    public:
        Piece (square position, bool white);
        Piece();
        void print_piece ();
        std::string getName() { return this->name; }
        virtual bool check_move(square goal, Piece* squares[])=0;
    protected:
        square position;
        bool white;
        std::string name;
        bool has_moved;
};

bool checkIfPiece(Piece *p);
int squareToIdx(square c);