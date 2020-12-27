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
        bool check_move(square dep, square stop);
        bool play_move(const char* move);
    private:
        Piece* squares[64];
        Piece* white_king;
        Piece* black_king;

        bool castling_short_w = true;
        bool castling_long_w = true;

        bool castling_short_b = true;
        bool castling_long_b = true;

        bool white = true;

        bool en_passant = false;
        square en_passant_square;
};