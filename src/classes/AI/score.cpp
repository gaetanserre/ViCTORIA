#include "engine.h"

void Score::print() {

    if (plies.size() > 0) {
        cout << "bestmove ";
        print_ply(this->plies[0]);
        if (plies.size() > 1) {
            cout << " ponder ";
            Score::print_ply(this->plies[1]);
        }
        cout << endl;
    }
}

void Score::print_info(int depth, bool white) {
    cout << "info depth " << depth << " seldepth " << depth;
    cout << " score ";

    if (this->mate) {
        // We convert plies to moves and we check the color of the mate
        int n = this->n_mate / 2;
        if (this->n_mate % 2)
            n++;
        cout << "mate " << (this->white_mate == white ? n : -n);
    }

    else {
        
        int score = this->score;
        // If white has advantage and it's black to play, we multiply score by -1  
        if (this->score > 0 && !white) {
            score *= -1;
        }
    
        cout << "cp " << score;
    }

    cout << " pv ";
    for (ply p : this->plies) {
        Score::print_ply(p);
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

Score Score::max (vector<Score> scores, bool white) {
    Score max_score;
    bool first = true;

    for (Score score: scores) {
        if (first) {
            max_score = score;
            first = false;
        }

        max_score = max (max_score, score, white);
    }

    return max_score;
}

bool Score::operator <= (Score s1) {
    if (this->mate) {
        if (s1.mate) {
            if (this->white_mate) {
                if (s1.white_mate) {
                    return this->n_mate >= s1.n_mate;
                } else {
                    return false;
                }
            } else {
                if (s1.white_mate){
                    return true;
                }
                else {
                    return this->n_mate <= s1.n_mate;
                }
            }
        } else {
            if (this->white_mate) return false;
            else return true;
        }
    }

    else if (s1.mate) {
        if (s1.white_mate) return true;
            else return false;
    }

    else {
        return this->score <= s1.score;
    }
}