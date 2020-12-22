#include "piece.h"

class Empty : public Piece {
    public:
        Empty() : Piece({'z', -1}, false, false) {
            this->name = "Null";
        }

        bool check_move(square start, square stop) override { return false; };
};