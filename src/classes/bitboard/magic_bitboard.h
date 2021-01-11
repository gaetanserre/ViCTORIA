#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "magics_number.h"

class Magic_Bitboard {
    public:
        Magic_Bitboard () {};
        void init ();
        bool check_square_rook (int start, int goal, U64 occupancy);
        bool check_square_bishop (int start, int goal, U64 occupancy);
        bool check_square_queen (int start, int goal, U64 occupancy);
};

void print_bitboard(U64 bitboard);
