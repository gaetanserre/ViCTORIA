#include "../score/score.h"

#define U64 unsigned long long
#define transposition_table_size 0xF4240 // 1 000 000 positions

struct Hash {
    U64 key;
    Score score;
    int depth;
    bool white;
};

// Check if the key is in the transposition table and return a value depending on alpha, beta and depth
Score ProbeHash (int depth, U64 key, Hash* transposition_table, bool white);

// Record the key in the transposition table depending on depth, score and hashf
void RecordHash (int depth, Score score, U64 key, Hash* transposition_table, bool white);