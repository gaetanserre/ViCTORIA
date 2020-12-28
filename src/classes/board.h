#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/queen.h"
#include "pieces/king.h"
#include "pieces/empty.h"

#include <vector>
using namespace std;

struct ply {
    Square dep;
    Square stop;
    bool promote = false;
    char prom;
};

class Board {
    public:
        Board (){};
        void init(string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        ~Board();
        void print_pieces();
        bool play_move(const char* move);
        void getLegalMoves();
        bool isOver();

    private:
        bool check_move_min(ply p);
        bool isTakeable(Square s);

        bool check_castle (ply p);
        void remove_castles();
        void remove_s_castle();
        void remove_l_castle();
        void play_castle (ply p);

        bool check_move(ply p);

        bool isCheck();

        bool isCheckmate(vector<ply> legal_moves);
        bool isStalemate(vector<ply> legal_moves);

        Piece* squares[64];
        Piece* white_king;
        Piece* black_king;

        bool castling_short_w = false;
        bool castling_long_w = false;

        bool castling_short_b = false;
        bool castling_long_b = false;

        bool white = true;

        bool en_passant = false;
        Square en_passant_square;

        vector<ply> legal_moves;
};