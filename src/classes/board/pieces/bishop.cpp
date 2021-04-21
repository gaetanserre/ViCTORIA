#include "bishop.h"
#include <math.h>

Bishop::Bishop(Square position, bool white, Magic_Bitboard* mg) : Piece(position, white) {
    this->name = 'b';
    this->name_str = "Bishop";

    this->pieceValue = 330;

    this->table = &bishop_table[0];
    this->table_end_game = &bishop_table[0];

    this->mg = mg;
}

bool Bishop::check_move(Square goal, Piece* squares[], U64 occupancy) {
    return mg->check_square_bishop(squareToIdx(this->position), squareToIdx(goal), occupancy);
}