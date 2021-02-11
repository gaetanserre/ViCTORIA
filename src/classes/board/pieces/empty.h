#include "piece.h"

class Empty : public Piece {
    public:
        Empty() : Piece(Square('z', -1), false) {
            this->name = 'z';
        }
        
        virtual ~Empty() {};

        bool check_move(Square goal, Piece* squares[], U64 occupancy) override { return false; };
        bool en_prise (Square goal, Piece* squares[], U64 occupancy) override { return false; };
};
