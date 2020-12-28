#include "piece.h"

class Pawn: public Piece {
    public:
        Pawn(Square position, bool white, bool start_pos,
           bool* en_passant, Square* en_passant_square);
        
        bool check_move(Square goal, Piece* squares[]) override;
        bool en_prise(Square goal, Piece* squares[]) override;

    private:
        int forward (int n);
        bool start_pos;

        bool* en_passant;
        Square* en_passant_square;
};