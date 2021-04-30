#pragma once

#include <sstream>
#include <algorithm>
#include <math.h>
#include <fstream>
#include <thread>
#include <future>
#include <chrono>
#include "constants/capture_table.h"
#include "transposition_table/hashKey.h"
#include "transposition_table/hash.h"
#include "evaluator/evaluator.h"


struct Move
{
    Ply ply;
    int score;
};


class Engine {
    public:
        Engine(string path, Evaluator evaluator);
        ~Engine();
        void parseExpr(string expr);

    private:

        /*************** Attributes ***************/

        string name;

        Board* board;

        Evaluator evaluator;


        string opening_table_path;
        string logs_path;
        bool not_in_opening_table = false;

        const int maxDepth = 64;
        int nodes = 0;
        int searchPly = 0;
        vector<Ply> killerMoves;

        bool startpos = true;
        bool end_game;
        bool early_game;

        Score best_move;

        vector<Ply> moves;
        unordered_map<U64, int> positions;

        /*************** Transposition tables attributes ***************/
        U64 zobrist_hash_key;
        Hash* transposition_table;


        /*************** Thread attributes ***************/
        bool terminate_thread = false;
        bool is_terminated;

        static string transform_path (string path);

        /*************** Begin time mesuring funcs ***************/
        static u_int64_t millis() {
            return chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::
                   now().time_since_epoch()).count();
        }

        static u_int64_t micros() {
            return chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::
                                                               now().time_since_epoch()).count();
        }
        /*************** End time mesuring funcs ***************/


        /*************** Begin useful funcs for parseExpr ***************/
        void definePartGame ();
        void parseGoCommand (vector<string> args);
        void launchTimeThread (u_int64_t dur, bool direct_analysis);
        void launchDepthSearch (int depth, bool direct_analysis, int nodes_max=-1);
        /*************** End useful funcs for parseExpr ***************/


        void searchOpeningBook (int depth);

        /*************** Begin useful funcs for in-depth search ***************/
        vector<Move> PlyToMove (vector<Ply> move_list);
        vector<Move> sortMoves ();
        bool checkRepetitions (U64 position);
        bool checkRepetitionsTrans(const vector<Ply>& plies);
        /*************** End useful funcs for in-depth search ***************/

        /*************** Begin in-depth search funcs ***************/
        U64 makeMove (Ply move);
        void undoMove (U64 hash_key);
        void addInHashMap(U64 position);
        void removeInHashMap(U64 position);

        Score AlphaBetaNegamax (int depth, Score alpha, Score beta);

        Score inDepthAnalysis (int depth, int alpha_score, int beta_score);
        void IterativeDepthAnalysis (int depth, int nodes_max=-1);

        /*************** End in-depth search funcs ***************/

};