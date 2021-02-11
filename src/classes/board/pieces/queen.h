#include "piece.h"

class Queen : public Piece {
    public:
        Queen (Square position, bool white, Magic_Bitboard* mg);
        virtual ~Queen () {};
        
        bool check_move(Square goal, Piece* squares[], U64 occupancy) override;
        bool en_prise(Square goal, Piece* squares[], U64 occupancy) override
            {return check_move(goal, squares, occupancy);}
    
    private:
        Magic_Bitboard* mg;
};