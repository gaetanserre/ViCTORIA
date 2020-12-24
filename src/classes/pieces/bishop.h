#include "piece.h"

class Bishop : public Piece {
    public:
        Bishop(square position, bool white);
        bool check_move(square goal, Piece* squares[]) override;
};