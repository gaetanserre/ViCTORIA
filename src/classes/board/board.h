#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/queen.h"
#include "pieces/king.h"
#include "pieces/empty.h"

#include "../bitboard/magic_bitboard.h"

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
        Board (){ this->magic_bitboard.init(); };
        ~Board();

        Piece* squares [64];

        void init(string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        void printPieces();
        void printLegalMoves();

        bool play_move(ply p, bool force = false);
        bool play_move(string p);

        string getFen(bool nb_move = true);

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

        void undo_move ();


        void resetFens() { this->fens = vector<string> (); };

        int nb_piece;
        int nb_pawn;

        static ply StringToPly (string ply);

        vector<string> fens;

        U64 occupancy;

        bool last_move_capture;


    private:


        bool check_move_min(int start_idx, Square stop);
        bool isTakeable(Square s);

        bool check_castle (ply p);
        void remove_castles();
        void remove_s_castle();
        void remove_l_castle();
        void play_castle (ply p);

        bool check_move(ply p);

        vector<ply> legal_moves;
        bool white;

        Piece* white_king;
        Piece* black_king;

        bool castling_short_w = false;
        bool castling_long_w = false;
        bool castling_short_b = false;
        bool castling_long_b = false;
        
        bool en_passant;
        Square en_passant_square;

        int nb_moves;

        Magic_Bitboard magic_bitboard;
};
