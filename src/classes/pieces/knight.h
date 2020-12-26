#include "piece.h"

class Knight : public Piece {
    public:
        Knight (square position, bool white);
        bool check_move(square goal, Piece* squares[]) override;
};