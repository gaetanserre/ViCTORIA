#pragma once

#include "../board/board.h"

#include <sstream>
#include <algorithm>

class Score {
    public:
        Score (int score, bool mate, int n_mate) {
            this->score = score;
            this->mate = mate;
            this->n_mate = n_mate;
        };

        static Score max (Score s1, Score s2, bool white) {
            if (s1.mate) {
                if (s2.mate) {
                    return (s1.n_mate < s2.n_mate ? s1 : s2);
                } else {
                    return s1;
                }
            } 
            
            else if (s2.mate) return s2;

            else {
                if (white) {
                    return s1.score > s2.score ? s1 : s2;
                } else {
                    return s1.score < s2.score ? s1 : s2;
                }
            }
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

        void print() {
            if (this->mate) {
                cout << "mate in: " << this->n_mate << endl;
            } else {
                cout << "score: " << this->score << endl;
            }

            reverse(plies.begin(), plies.end());
            for (ply p : plies)
                print_ply(p);
        }

        static void print_ply (ply p) {
            p.dep.print();
            p.stop.print();
            if (p.promote)
                cout << p.prom;
            cout << endl;
        }

        int score;
        bool mate;
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