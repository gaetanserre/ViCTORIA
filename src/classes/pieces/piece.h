#include <iostream>
#include <string>

struct square {
    char letter;
    int number;
};

class Piece {
    public:
        Piece (square position, bool white, bool black);
        void print_piece ();
    protected:
        square position;
        bool white;
        bool black;
        std::string name;
};