#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/queen.h"
#include "pieces/king.h"
#include "pieces/empty.h"

#include <vector>
#include <cstring>
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
        //~Board();

        Piece* squares[64];

        void init(string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        void printPieces();
        void printLegalMoves();

        bool play_move(ply p, bool force = false);
        bool play_move(string p);

        void undo_move();
        string getFen();

        vector<ply> getLegalMoves() { return this->legal_moves; };
        void setLegalMoves(vector<ply> legal_moves) { this->legal_moves = legal_moves; };
        void changeSide() { this->white = ! this->white; };
        bool isWhite() { return this->white; };
        void setWhite(bool isWhite) { this->white = isWhite; } 

        bool isCheck();
        bool isCheckmate(int size);
        bool isStalemate(int size);
        bool isOver();
        void computeLegalMoves();

        void resetFens() { this->fens.clear(); };

        int nb_pieces;

        static ply StringToPly (string ply);


    private:
        bool check_move_min(Square dep, Square stop);
        bool isTakeable(Square s);

        bool check_castle (ply p);
        void remove_castles();
        void remove_s_castle();
        void remove_l_castle();
        void play_castle (ply p);

        bool check_move(ply p);


        void checkRepetitions();

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

        int nb_moves;
        vector<string> fens;

        vector<ply> last_move;
        int nb_rep = 0;
};
