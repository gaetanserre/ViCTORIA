#pragma once

#include <iostream>
#include <string>

struct square {
    char letter;
    int number;
};

class Piece {
    public:
        Piece (square position, bool white, bool black);
        Piece();
        void print_piece ();
        std::string getName() { return this->name; }
    protected:
        square position;
        bool white;
        bool black;
        std::string name;
};