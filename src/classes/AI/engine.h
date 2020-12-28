#include "../board/board.h"

#include <sstream>

class Score {
    public:
        Score (int score, bool mate, int n_mate) {
            this->score = score;
            this->mate = mate;
            this->n_mate = n_mate;
        };

        bool operator> (Score s) {
            if (this->mate) {
                if (s.mate) {
                    return this->n_mate < s.n_mate;
                } else {
                    return true;
                }
            } else if (s.mate) return false;
            else return this->score > s.score;
        };

        int score;
        bool mate;
        int n_mate;
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