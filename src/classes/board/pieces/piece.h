#pragma once

#include <iostream>
#include <functional>
#include "../square.h"

class Piece {
    public:
        Piece (Square position, bool white);
        void print_piece ();
        
        std::string getName() { return this->name; }
        void setPosition(Square position) { this->position = position; };
        Square getPosition() { return this->position; }
        bool isWhite() { return this->white; };

        bool checkIfPieceIsTakeable(Piece* p);
        virtual bool check_move(Square goal, Piece* squares[])=0;
        virtual bool en_prise(Square goal, Piece* squares[])=0;

        
    protected:
        Square position;
        bool white;
        std::string name;
        bool itermove(
            int init, Piece* squares[],
            std::function<bool(int)> test,
            std::function<void(int*)> incr,
            std::function<Square(int)> pos
        );
        bool PlusOrMinus(int value1, int value2, int n);
};

bool checkIfPiece(Piece *p);
int squareToIdx(Square c);
Square IdxToSquare(int idx);
