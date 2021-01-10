#pragma once

#include <iostream>
#include <functional>
#include <vector>
#include "../square.h"
#include "table.h"

class Piece {
    public:
        Piece (Square position, bool white);
        virtual ~Piece () {};
        void print_piece ();
        
        char getName() { return this->name; }
        void setPosition(Square position) { this->position = position; };
        Square getPosition() { return this->position; }
        bool isWhite() { return this->white; };

        bool checkIfPieceIsTakeable(Piece* p);
        virtual bool check_move(Square goal, Piece* squares[]) = 0;
        virtual bool en_prise(Square goal, Piece* squares[]) = 0;

        float getPieceValue (bool end_game);

        
    protected:
        Square position;
        bool white;
        char name;
        
        int pieceValue;
        const float* table;
        const float* table_end_game;

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
