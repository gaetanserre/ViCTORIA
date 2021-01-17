#include "hash.h"

Score ProbeHash (Score alpha, Score beta, int depth, U64 key, Hash* transposition_table, bool white) {
    Hash* phashe = &transposition_table[key % transposition_table_size];

    if (phashe->key == key) {
        if (phashe->depth >= depth) {
            if (phashe->flag == hashfEXACT) {
                Score s = phashe->score;
                if (phashe->white != white)
                    s.score *= -1;
                return s;
            }
            
            if (phashe->flag == hashfALPHA && phashe->score.score <= alpha.score)
                return alpha;
            
            if (phashe->flag == hashfBETA && phashe->score.score >= beta.score)
                return beta;
        }
    }
    return Score (unknown_value);
}

void RecordHash (int depth, Score score, int hashf, U64 key, Hash* transposition_table, bool white) {
    Hash * phashe = &transposition_table[key % transposition_table_size];

    if (depth > phashe->depth) {
        phashe->key = key;
        phashe->score = score;
        phashe->flag = hashf;
        phashe->depth = depth;
        phashe->white = white;
    }
}