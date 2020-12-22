#pragma once

#include <iostream>
#include <string>

struct square {
    char row;
    int line;
};

class Piece {
    public:
        Piece (square position, bool white, bool black);
        Piece();
        void print_piece ();
        std::string getName() { return this->name; }
        virtual bool check_move(square start, square stop)=0;
    protected:
        square position;
        bool white;
        bool black;
        std::string name;
        int squareToIdx(square c);

};