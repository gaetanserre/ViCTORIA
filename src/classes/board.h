#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/queen.h"
#include "pieces/king.h"
#include "pieces/empty.h"
using namespace std;

class Board {
    public:
        Board (){};
        void init(string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        ~Board();
        void print_pieces();
        void print_move(char* move);
    private:
        Piece** pieces;
};