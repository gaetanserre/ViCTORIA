#pragma once

#include "../board/board.h"

#include <sstream>
#include <algorithm>

class Score {
    public:
        Score (int score, bool mate, bool white_mate, int n_mate) {
            this->score = score;
            this->mate = mate;
            this->white_mate = white_mate;
            this->n_mate = n_mate;
        };

        static Score max (Score s1, Score s2, bool white);

        void print();
        static void print_ply (ply p);

        int score;
        bool mate;
        bool white_mate;
        int n_mate;
        vector<ply> plies;
};


class Engine {
    public:
        Engine();
        void parse_expr(string expr);

    private:
        Board board;
        Score evalPosition();
        Score inDepthAnalysis (int depth);
};