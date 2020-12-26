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
        bool isWhite();
        bool checkIfPieceIsTakeable(Piece* p);
        
    protected:
        square position;
        bool white;
        std::string name;
        bool has_moved;
        bool itermove(
            int init, Piece* squares[],
            std::function<bool(int)> test,
            std::function<void(int*)> incr,
            std::function<square(int)> pos
        );
        bool PlusOrMinus(int value1, int value2, int n);
};

bool checkIfPiece(Piece *p);
int squareToIdx(square c);