#pragma once

#include "pieces/pawn.h"
#include "pieces/rook.h"
#include "pieces/knight.h"
#include "pieces/bishop.h"
#include "pieces/queen.h"
#include "pieces/king.h"
#include "pieces/empty.h"
#include "../bitboard/magic_bitboard.h"
#include "ply.h"

#include <vector>
#include <cstring>
using namespace std;

class Board {
    public:
        Board (){ this->magic_bitboard.init(); };
        ~Board();

        Piece* squares [64];

        void init(string fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
        void printPieces();
        void printLegalMoves();

        bool play_move(Ply p, bool force = false);
        bool play_move(string p);

        string getFen(bool nb_move = true);

        bool isCheck();
        bool isCheckmate(int size);
        bool isStalemate(int size);
        bool isOver();
        void computeLegalMoves();

        void undo_move ();

        /************* Begin Setters/Getters/Tools *************/
        
        vector<Ply> getLegalMoves() { return this->legal_moves; };
        void setLegalMoves(vector<Ply> legal_moves) { this->legal_moves = legal_moves; };

        void changeSide() { this->white = ! this->white; };

        bool isWhite() { return this->white; };
        void setWhite(bool isWhite) { this->white = isWhite; }
        
        void resetFens() { this->fens = vector<string> (); };

        void setEnPassant (bool b) { this->en_passant = b; }
        bool getEnPassant () { return this->en_passant; }
        Square getEnPassantSquare () { return this->en_passant_square; }

        int getNbCastlings (bool white) {
            if (white) return this->castling_long_w + this->castling_short_w;
            else return this->castling_long_b + this->castling_short_b;
        }

        /************* End Setters/Getters/Tools *************/

        static Ply StringToPly (string ply);        



        int nb_piece;
        int nb_pawn;

        vector<string> fens;

        U64 occupancy;

        bool last_move_capture;

        bool castling_short_w = false;
        bool castling_long_w = false;
        bool castling_short_b = false;
        bool castling_long_b = false;


    private:


        bool check_move_min(int start_idx, Square stop);
        bool isTakeable(Square s);

        bool check_castle (Ply p);
        void remove_castles();
        void remove_s_castle(bool inverse);
        void remove_l_castle(bool inverse);
        void play_castle (Ply p);

        bool check_move(Ply p);



        vector<Ply> legal_moves;
        bool white;

        Piece* white_king;
        Piece* black_king;
        
        bool en_passant;
        Square en_passant_square;

        int nb_moves;

        Magic_Bitboard magic_bitboard;
};
