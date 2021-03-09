#include "hash.h"

Score ProbeHash (int depth, U64 key, Hash* transposition_table, bool white) {
    Hash* phashe = &transposition_table[key % transposition_table_size];

    if (phashe->key == key) {
        if (phashe->depth >= depth) {
            Score s = phashe->score;
            if (phashe->white != white)
                s.score *= -1;
            return s;
        }
    }
    return Score (unknown_value);
}

void RecordHash (int depth, Score score, U64 key, Hash* transposition_table, bool white) {
    Hash * phashe = &transposition_table[key % transposition_table_size];

    if (depth > phashe->depth) {
        phashe->key = key;
        phashe->score = score;
        phashe->depth = depth;
        phashe->white = white;
    }
}