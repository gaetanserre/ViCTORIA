#pragma once

#include <sstream>
#include <algorithm>
#include <fstream>
#include <thread>
#include <future>
#include <time.h>
#include <chrono>
#include "score.h"
#include "capture_table.h"


struct Move
{
    Ply ply;
    int score;
};


class Engine {
    public:
        Engine();
        ~Engine();
        void parse_expr(string expr);

    private:

        /*************** Begin time mesuring funcs ***************/
        static clock_t startChrono() { 
            return clock();
        }

        static double stopChrono(clock_t start) {
            return (double)(clock() - start) / 1000; //µs to ms
        }
        /*************** End time mesuring funcs ***************/

        string name;

        Board* board;

        void parse_go_command (vector<string> args);


        void searchOpeningBook (int depth);

        /*************** Begin useful funcs for in-depth search ***************/
        bool checkRepetitions (string position);

        vector<Move> PlyToMove (vector<Ply> move_list);
        vector<Move> sortMoves ();
        /*************** End useful funcs for in-depth search ***************/

        /*************** Begin Heuristics funcs ***************/
        bool NullPruning (Score beta, int depth, Score &res);
        /*************** End Heuristics funcs ***************/

        /*************** Begin in-depth search funcs ***************/
        Score evalPosition(Board* board);

        Score AlphaBetaNegamax (int depth, Score alpha, Score beta);

        void inDepthAnalysis (int depth);
        void MultiDepthAnalysis (int depth);

        void threadDepthAnalysis (future<void> future_object, int depth);
        /*************** End in-depth search funcs ***************/

        /*************** Attributes ***************/

        string opening_table_path = "/home/gaetan/Documents/Projets/Chess/chess_books/opening_book-2.5M.pgn";
        bool not_in_opening_table = false;

        const int maxDepth = 64;
        int searchPly = 0;
        vector<Ply> killerMoves;

        bool startpos = true;
        bool end_game;

        Score best_move;

        vector<Ply> moves;
        vector<string> positions;

        /*************** Thread attributes ***************/
        bool terminate_thread = false;
        bool is_terminated;
};