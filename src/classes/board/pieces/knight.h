#include "piece.h"

class Knight : public Piece {
    public:
        Knight (Square position, bool white);
        virtual ~Knight () {};
        bool check_move(Square goal, Piece* squares[]) override;
        bool en_prise(Square goal, Piece* squares[]) override
            {return check_move(goal, squares);}
};