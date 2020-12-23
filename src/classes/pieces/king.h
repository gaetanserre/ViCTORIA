#include "piece.h"

class King : public Piece {
    public:
        King (square position, bool white);
        bool check_move(square goal, Piece* squares[]) override { return false;};
    private:
        bool is_check;
};