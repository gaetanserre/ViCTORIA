#include "piece.h"

class Empty : public Piece {
    public:
        Empty() : Piece({'z', -1}, false) {
            this->name = "Null";
        }

        bool check_move(square goal, Piece* squares[]) override { return false; };
};