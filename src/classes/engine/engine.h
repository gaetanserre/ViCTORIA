#pragma once

#include "../board/board.h"

#include <sstream>
#include <algorithm>
#include <fstream>

const int mate_value = 99999;

class Score {
    public:
        Score (int score) {
            this->score = score;
        };

        Score() {
            this->score=0;
        };

        bool operator == (Score s);
        bool operator != (Score s);

        static Score max (Score s1, Score s2);
        static Score min (Score s1, Score s2);

        void print();
        void print_info(int depth, int nodes, int time_ms, bool white);
        static void print_ply (ply p);

        int score;
        vector<ply> plies;
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

        bool NullPruning (Score beta, int depth, Score &res);

        bool checkRepetitions (string position);

        Score alphaBetaMax (int depth, Score alpha, Score beta);
        Score alphaBetaMin (int depth, Score alpha, Score beta);
        Score AlphaBeta (int depth, Score alpha, Score beta);

        Score inDepthAnalysis (int depth);
        Score MultiDepthAnalysis (int depth);

        Score searchOpeningBook (int depth);

        bool startpos = true;
        bool end_game;

        Score best_move;

        vector<ply> moves;
        vector<string> positions;
};