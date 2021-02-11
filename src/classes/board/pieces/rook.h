#include "piece.h"

class Rook: public Piece {
    public:
        Rook(Square position, bool white, Magic_Bitboard* mg);
        virtual ~Rook () {};
        
        bool check_move(Square goal, Piece* squares[], U64 occupancy) override;
        bool en_prise(Square goal, Piece* squares[], U64 occupancy) override
            {return check_move(goal, squares, occupancy);}
    private:
        Magic_Bitboard* mg;
};