#include "piece.h"

class Pawn: public Piece {
    public:
        Pawn(Square position, bool white,
           bool* en_passant, Square* en_passant_square);
        
        virtual ~Pawn () {};

        bool check_move(Square goal, Piece* squares[], U64 occupancy) override;
        bool en_prise(Square goal, Piece* squares[], U64 occupancy) override;

    private:
        int forward (int n);

        bool* en_passant;
        Square* en_passant_square;
};