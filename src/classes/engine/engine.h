#pragma once

#include <sstream>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <thread>
#include <future>
#include <chrono>
#include "score/score.h"
#include "constants/capture_table.h"
#include "transposition_table/hashKey.h"
#include "transposition_table/hash.h"


struct Move
{
    Ply ply;
    int score;
};


class Engine {
    public:
        Engine(string path);
        ~Engine();
        void parseExpr(string expr);

    private:

        string transform_path (string path);

        /*************** Begin time mesuring funcs ***************/
        static u_int64_t millis() {
            return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::
                   now().time_since_epoch()).count();
        }
        /*************** End time mesuring funcs ***************/

        string name;

        Board* board;

        /*************** Begin useful funcs for parseExpr ***************/
        void parseGoCommand (vector<string> args);
        void launchTimeThread (u_int64_t dur, bool direct_analysis);
        void launchDepthSearch (int depth, bool direct_analysis);
        /*************** End useful funcs for parseExpr ***************/


        void searchOpeningBook (int depth);

        /*************** Begin useful funcs for in-depth search ***************/

        vector<Move> PlyToMove (vector<Ply> move_list);
        vector<Move> sortMoves ();
        bool checkRepetitions ();
        bool checkIfEven (vector<Ply> move_list);
        /*************** End useful funcs for in-depth search ***************/

        /*************** Begin Heuristics funcs ***************/
        bool NullPruning (Score beta, int depth, Score &res);
        /*************** End Heuristics funcs ***************/

        /*************** Begin in-depth search funcs ***************/
        U64 makeMove (Ply move);
        void undoMove (U64 hash_key);

        /*************** Begin evaluation functions ***************/
        Score evalPosition(Board* board);
        /*************** End evaluation functions ***************/

        Score AlphaBetaNegamax (int depth, Score alpha, Score beta);

        Score inDepthAnalysis (int depth, int alpha_score, int beta_score);
        void IterativeDepthAnalysis (int depth);

        void threadDepthAnalysis (future<void> future_object, int depth);
        /*************** End in-depth search funcs ***************/

        /*************** Attributes ***************/

        string opening_table_path = "/home/gaetan/Documents/Projets/Chess/ViCTORIA/books/modern_openings.pgn";
        bool not_in_opening_table = false;

        const int maxDepth = 64;
        int nodes = 0;
        int searchPly = 0;
        vector<Ply> killerMoves;

        bool startpos = true;
        bool end_game;

        Score best_move;

        vector<Ply> moves;
        vector<string> positions;

        /*************** Transposition tables attributes ***************/
        U64 zobrist_hash_key;
        //Hash* transposition_table;

        /*************** Thread attributes ***************/
        bool terminate_thread = false;
        bool is_terminated;
};