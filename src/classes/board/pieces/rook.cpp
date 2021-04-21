#include "rook.h"

Rook::Rook(Square position, bool white, Magic_Bitboard* mg) : Piece(position, white) {
    this->name = 'r';
    this->name_str = "Rook";

    this->pieceValue = 500;

    this->table = &rook_table[0];
    this->table_end_game = &rook_table[0];

    this->mg = mg;
}

bool Rook::check_move(Square goal, Piece* squares[], U64 occupancy) {
    return mg->check_square_rook(squareToIdx(this->position), squareToIdx(goal), occupancy);
}