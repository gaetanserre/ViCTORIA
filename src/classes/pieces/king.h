#include "piece.h"

class King : public Piece {
    public:
        King (square position, bool white, bool black);
    private:
        bool is_check;
};