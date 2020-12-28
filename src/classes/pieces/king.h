#include "piece.h"

class King : public Piece {
    public:
        King (Square position, bool white);
        bool check_move(Square goal, Piece* squares[]) override;
        bool en_prise(Square goal, Piece* squares[]) override
            {return check_move(goal, squares);}
        
    private:
        bool is_check;
};