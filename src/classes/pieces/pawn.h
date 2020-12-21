#include "piece.h"

class Pawn: public Piece {
    public:
        Pawn(square position, bool white, bool black);
    private:
        bool start_pos;
};