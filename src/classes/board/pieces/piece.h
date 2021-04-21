#pragma once

#include <iostream>
#include <vector>
#include "../square.h"
#include "table.h"
#include "../../bitboard/magic_bitboard.h"

class Piece {
    public:
        Piece (Square position, bool white);
        virtual ~Piece () {};
        std::string toString ();
        
        char getName() { return this->name; }
        void setPosition(Square position) { this->position = position; };
        Square getPosition() { return this->position; }
        bool isWhite() { return this->white; };

        bool checkIfPieceIsTakeable(Piece* p);
        virtual bool check_move(Square goal, Piece* squares[], U64 occupancy) = 0;
        virtual bool en_prise(Square goal, Piece* squares[], U64 occupancy) = 0;

        float getPieceValue (bool end_game);

        
    protected:
        Square position;
        bool white;
        char name;
        std::string name_str;
        
        int pieceValue;
        const float* table;
        const float* table_end_game;

        
};

bool PlusOrMinus(int value1, int value2, int n);
bool checkIfPiece(Piece *p);
int squareToIdx(Square c);
Square IdxToSquare(int idx);
