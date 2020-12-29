#include "engine.h"

void Score::print() {

    if (plies.size() > 0) {
        cout << "bestmove ";
        print_ply(this->plies[0]);
        if (plies.size() > 1) {
            cout << " ponder ";
            print_ply(this->plies[1]);
        }
        cout << endl;
    }
}

void Score::print_info(int depth) {
    cout << "info depth " << depth << " seldepth " << depth;
    cout << " score ";
    if (this->mate) {
        int n = this->n_mate / 2;
        if (this->n_mate % 2)
            n++;
        cout << "mate " << n;
    }
    else cout << "cp " << this->score;

    cout << " pv ";
    for (ply p : this->plies) {
        print_ply(p);
        cout << " ";
    }
    cout << endl;
}

void Score::print_ply(ply p) {
    p.dep.print();
    p.stop.print();
    if (p.promote)
        cout << p.prom;
}

Score Score::max (Score s1, Score s2, bool white) {

    if (s1.mate) {
        if (s2.mate) {
            if (s1.white_mate == white) {
                if (s2.white_mate == white) {
                    return (s1.n_mate < s2.n_mate ? s1 : s2);
                } else {
                    return s1;
                }
            } else {
                if (s2.white_mate == white){
                    return s2;
                }
                else {
                    return (s1.n_mate > s2.n_mate ? s1 : s2);
                }
            }
        } else {
            if (s1.white_mate == white) return s1;
            else return s2;
        }
    }

    else if (s2.mate) {
        if (s2.white_mate == white) return s2;
            else return s1;
    }

    else {
        if (white) {
            return s1.score > s2.score ? s1 : s2;
        } else {
            return s1.score < s2.score ? s1 : s2;
        }
    }
}