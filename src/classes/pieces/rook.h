#include "piece.h"

class Rook: public Piece {
    public:
        Rook(square position, bool white, bool black);
        bool check_move(square start, square stop) override { return false;};
};