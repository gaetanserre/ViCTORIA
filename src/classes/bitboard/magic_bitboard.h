#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../board/pieces/piece.h"
#include "magics_number.h"

class Magic_Bitboard {
    public:
        Magic_Bitboard ();
        bool check_square_rook (Piece* rook, int goal, U64 occupancy);
        bool check_square_bishop (Piece* bishop, int goal, U64 occupancy);
        bool check_square_queen (Piece* queen, int goal, U64 occupancy);
};

void print_bitboard(U64 bitboard);
