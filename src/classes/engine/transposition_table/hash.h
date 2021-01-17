#include "../score/score.h"

#define U64 unsigned long long
#define hashfEXACT   0
#define hashfALPHA   1
#define hashfBETA    2
#define transposition_table_size 0x7A120 // 500 000 positions

struct Hash {
    U64 key;
    Score score;
    int flag;
    int depth;
    bool white;
};

// Check if the key is in the transposition table and return a value depending on alpha, beta and depth
Score ProbeHash (Score alpha, Score beta, int depth, U64 key, Hash* transposition_table, bool white);

// Record the key in the transposition table depending on depth, score and hashf
void RecordHash (int depth, Score score, int hashf, U64 key, Hash* transposition_table, bool white);
