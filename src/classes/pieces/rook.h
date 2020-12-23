#include "piece.h"

class Rook: public Piece {
    public:
        Rook(square position, bool white);
        bool check_move(square goal, Piece* squares[]) override { return false;};
};