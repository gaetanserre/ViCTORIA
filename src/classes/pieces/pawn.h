#include "piece.h"

class Pawn: public Piece {
    public:
        Pawn(square position, bool white, bool start_pos,
           bool* en_passant, square* en_passant_square);
        bool check_move(square goal, Piece* squares[]) override;

    private:
        int forward (int n);
        bool start_pos;

        bool* en_passant;
        square* en_passant_square;
};