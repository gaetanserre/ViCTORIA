#include "queen.h"
#include "bishop.h"
#include "rook.h"

Queen::Queen (Square position, bool white, Magic_Bitboard* mg) : Piece(position, white) {
    this->name = 'q';
    this->name_str = "Queen";

    this->pieceValue = 900;

    this->table = &queen_table[0];
    this->table_end_game = &queen_table[0];

    this->mg = mg;
}

bool Queen::check_move(Square goal, Piece* squares[], U64 occupancy) {
    return mg->check_square_queen(squareToIdx(this->position), squareToIdx(goal), occupancy);
};