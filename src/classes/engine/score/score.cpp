#include "score.h"


void Score::print() {

    if (plies.size() > 0) {
        cout << "bestmove " << this->plies[0].toString();
        if (plies.size() > 1) {
            cout << " ponder " << this->plies[1].toString();
        }
        cout << endl;
    }
}

void Score::print_info(int nodes, u_int64_t time_ms, bool white) {
    int depth = this->plies.size();
    cout << "info depth " << depth << " seldepth " << depth;
    cout << " score ";

    if (this->score == mate_value || this->score == -mate_value) {
        // We convert plies to moves and we check the color of the mate
        int n = depth / 2;
        if (depth % 2)
            n++;
        bool white_mate = this->score > 0;
        cout << "mate " << (white == white_mate ? n : -n);
    }

    else {

        // If it's black to play we multiply score by -1
        int score = white ? this->score : -this->score;

       cout << "cp " << score;
    }

    cout << " nodes " << nodes; 

    cout << " time " << time_ms;

    cout << " pv";
    for (Ply p : this->plies) {
        cout << " " << p.toString(); 
    }
    cout << endl;
}

bool Score::operator== (Score s) {
    if (this->score != s.score) return false;
    int size = this->plies.size();
    if (size != s.plies.size()) return false;

    for (int i = 0; i<size; i++) {
        if (!(this->plies[i].dep == s.plies[i].dep) || !(this->plies[i].stop == s.plies[i].stop))
            return false;
    }

    return true;
}

bool Score::operator!= (Score s) {
    return !(*this == s);
}

bool Score::operator> (Score s) {
    if (this->score == -mate_value && s.score == -mate_value) {
        return this->plies.size() > s.plies.size();

    } else if (this->score == mate_value && s.score == mate_value) {
        return this->plies.size() < s.plies.size();

    } else {
        return this->score > s.score;
    }
}

Score Score::max (Score s1, Score s2) {
    if (s1.score == -mate_value && s2.score == -mate_value) {
        return (s1.plies.size() > s2.plies.size() ? s1 : s2);

    } else if (s1.score == mate_value && s2.score == mate_value) {
        return (s1.plies.size() < s2.plies.size() ? s1 : s2);

    }else if (s1.score > s2.score) {
        return s1;
    } else {
        return s2;
    }
}

Score Score::min (Score s1, Score s2) {
    if (s1.score == mate_value) {
        if (s2.score == mate_value) {
            return (s1.plies.size() > s2.plies.size() ? s1 : s2);
        } else {
            return s2;
        }
    }

    if (s2.score == mate_value) {
        return s1;
    }

    if (s1.score == -mate_value) {
        if (s2.score == -mate_value) {
            return (s1.plies.size() < s2.plies.size() ? s1 : s2);
        } else {
            return s1;
        }
    }

    if (s2.score == -mate_value) {
        return s2;
    }

    else {
        return (s1.score < s2.score ? s1 : s2);
    }
}
