#include "piece.h"

class Bishop : public Piece {
    public:
        Bishop(Square position, bool white);
        virtual ~Bishop () {};
        bool check_move(Square goal, Piece* squares[]) override;
        bool en_prise(Square goal, Piece* squares[]) override
            {return check_move(goal, squares);}
};