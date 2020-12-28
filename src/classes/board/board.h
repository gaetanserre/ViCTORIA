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
        ~Board();

        Piece* squares[64];

        void init(string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        void print_pieces();

        bool play_move(ply p);
        bool play_move(const char *);
        vector<ply> getLegalMoves() { return this->legal_moves; };
        void changeSide() { this->white = ! this->white; };
        bool isWhite() { return this->white; };

        bool isCheckmate(vector<ply> legal_moves);
        bool isStalemate(vector<ply> legal_moves);
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

        void computeLegalMoves();

        vector<ply> legal_moves;
        bool white;

        Piece* white_king;
        Piece* black_king;

        bool castling_short_w;
        bool castling_long_w;
        bool castling_short_b;
        bool castling_long_b;
        
        bool en_passant;
        Square en_passant_square;
};