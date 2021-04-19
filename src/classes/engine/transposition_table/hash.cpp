#include "hash.h"

#include <utility>

Score ProbeHash (int depth, U64 key, Hash* transposition_table, bool white) {
    Hash* phashe = &(transposition_table[key % transposition_table_size]);

    if (phashe->key == key) {
        if (phashe->depth >= depth) {
            Score s = Score(phashe->score.score);

            if (abs(s.score) == mate_value) {
                s.plies = vector<Ply>(phashe->score.plies);
            } else {
                s.plies = vector<Ply>();
                int size = phashe->score.plies.size();
                for (int i = size - depth; i < size; i++) {
                    s.plies.push_back(phashe->score.plies[i]);
                }
            }
            if (phashe->white != white)
                s.score *= -1;
            return s;
        }
    }
    return Score (unknown_value);
}

void RecordHash (int depth, Score score, U64 key, Hash* transposition_table, bool white) {
    Hash * phashe = &(transposition_table[key % transposition_table_size]);

    if (depth > phashe->depth) {
        phashe->key = key;
        phashe->score = std::move(score);
        phashe->depth = depth;
        phashe->white = white;
    }
}