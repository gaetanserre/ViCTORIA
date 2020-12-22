#include "piece.h"

class Queen : public Piece {
    public:
        Queen (square position, bool white, bool black);
        bool check_move(square start, square stop) override { return false;};
};