#include "piece.h"

class Pawn: public Piece {
    public:
        Pawn(square position, bool white, bool black);
        bool check_move(square start, square end) override {
            return true;
        };
    private:
        bool start_pos;
};