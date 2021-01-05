#include "piece.h"

class Queen : public Piece {
    public:
        Queen (Square position, bool white);
        virtual ~Queen () {};
        bool check_move(Square goal, Piece* squares[]) override;
        bool en_prise(Square goal, Piece* squares[]) override
            {return check_move(goal, squares);}
};