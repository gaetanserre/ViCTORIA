#include "piece.h"

class Queen : public Piece {
    public:
        Queen (square position, bool white);
        bool check_move(square goal, Piece* squares[]) override { return false;};
};