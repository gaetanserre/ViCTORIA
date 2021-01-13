#pragma once

#include <sstream>
#include <algorithm>
#include <fstream>
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
        string name;

        Board* board;
        Score evalPosition(Board* board);

        /*************** Begin useful funcs for deep search ***************/
        bool checkRepetitions (string position);

        vector<Move> sortMoveByCapture (vector<Ply> move_list);
        vector<Move> sortMoves ();
        /*************** End useful funcs for deep search ***************/

        /*************** Begin Heuristics funcs ***************/
        bool NullPruning (Score beta, int depth, Score &res);
        /*************** End Heuristics funcs ***************/


        Score AlphaBetaNegamax (int depth, Score alpha, Score beta);

        Score inDepthAnalysis (int depth);
        Score MultiDepthAnalysis (int depth);

        Score searchOpeningBook (int depth);

        bool startpos = true;
        bool end_game;

        Score best_move;

        vector<Ply> moves;
        vector<string> positions;
};