#include "piece.h"

class Knight : public Piece {
    public:
        Knight (square position, bool white, bool black);
        bool check_move(square start, square stop) override { return false;};
};