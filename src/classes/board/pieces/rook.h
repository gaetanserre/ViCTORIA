#include "piece.h"

class Rook: public Piece {
    public:
        Rook(Square position, bool white);
        virtual ~Rook () {};
        bool check_move(Square goal, Piece* squares[]) override;
        bool en_prise(Square goal, Piece* squares[]) override
            {return check_move(goal, squares);}
};