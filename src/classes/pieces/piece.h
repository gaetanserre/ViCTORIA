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
        void print_piece ();
        
        std::string getName() { return this->name; }
        void setPosition(square position) {this->position = position; };
        bool isWhite() { return this->white; };

        bool checkIfPieceIsTakeable(Piece* p);
        virtual bool check_move(square goal, Piece* squares[])=0;

        
    protected:
        square position;
        bool white;
        std::string name;
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