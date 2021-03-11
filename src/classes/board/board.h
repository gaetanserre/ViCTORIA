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

        /************* End Setters/Getters/Tools *************/

        static Ply StringToPly (string ply);        


        /************* Attributes *************/

        int nb_piece;
        int nb_pawn;

        Piece* white_king;
        Piece* black_king;

        vector<string> fens;

        U64 occupancy;

        bool last_move_capture;

        bool castling_short_w = false;
        bool castling_long_w = false;
        bool castling_short_b = false;
        bool castling_long_b = false;

        // True if players castles
        bool has_castling_w = false;
        bool has_castling_b = false;

        int nb_plies_50_rule = 0;


    private:


        bool check_move_min(int start_idx, Square stop);
        bool isTakeable(Square s);

        bool check_castling (Ply p);
        void remove_castlings();
        void remove_s_castling(bool inverse);
        void remove_l_castling(bool inverse);
        void play_castling (Ply p);

        bool check_move(Ply p);

        void undoCastlings ();


        /************* Attributes *************/

        vector<Ply> legal_moves;
        bool white;
        
        bool en_passant;
        Square en_passant_square;

        int nb_moves;

        Magic_Bitboard magic_bitboard;

        // Counter to check when reset castle booleans
        int nb_moves_since_castling_w = 0;
        int nb_moves_since_castling_b = 0;
};
