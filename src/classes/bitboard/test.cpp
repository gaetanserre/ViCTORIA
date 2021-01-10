#include "magic_bitboard.h"
#include "../board/pieces/rook.h"
#include "../board/pieces/bishop.h"
#include "../board/pieces/queen.h"
#include "../board/pieces/pawn.h"
#include <iostream>
using namespace std;

int main () {
    Magic_Bitboard mb;

    U64 occupancy = 0ULL;
    set_bit (occupancy, squareToIdx(Square("g3")));
    set_bit (occupancy, squareToIdx(Square("b1")));
    set_bit (occupancy, squareToIdx(Square("f8")));
    set_bit (occupancy, squareToIdx(Square("b8")));
    cout << "\n\n     Occupancy" << endl;
    print_bitboard (occupancy);


    Bishop b (Square("g3"), true);
    cout << mb.check_square_bishop(&b, squareToIdx(Square("b8")), occupancy) << endl;
}