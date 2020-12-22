#include "piece.h"

class King : public Piece {
    public:
        King (square position, bool white, bool black);
        bool check_move(square start, square stop) override { return false;};
    private:
        bool is_check;
};