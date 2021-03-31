#include "hashKey.h"

unsigned int seed;

void resetSeed () {
    seed = 1924273048;
}

U64 get_64_random () {
    //mt19937_64 gen (random_device{}());
    mt19937_64 gen (seed); // I use seed for debug
    seed += 1;
    return gen();
}


U64 piece_keys [12][64];

U64 enpassant_keys [64];

U64 castlings_keys [16];

U64 side_key;

void initRandomKeys () {

    resetSeed();

    // loop over pieces
    for (int piece = 0; piece<12; piece++) {
        for (int square = 0; square < 64; square++) {
            piece_keys[piece][square] = get_64_random();

            // init enpassant only once
            if (piece == 0)
                enpassant_keys[square] = get_64_random();
        }
    }

    for (int castlings = 0; castlings < 16; castlings++)
        // init castlings keys
        castlings_keys[castlings] = get_64_random();
    
    // init side key
    side_key = get_64_random();
}

int getPieceKey (Piece* p) {
    int padding = p->isWhite() ? 0 : 6;
    char name = p->getName();

    switch (name)
    {
        case 'p':
            return 0 + padding;
        
        case 'n':
            return 1 + padding;
        
        case 'b':
            return 2 + padding;
        
        case 'r':
            return 3 + padding;
        
        case 'q':
            return 4 + padding;
        
        case 'k':
            return 5 + padding;
    }
    exit(-1);
}

int getCastlingsKey (Board* board) {
    bool castlings_rights [] = {
        board->castling_long_b,
        board->castling_long_w,
        board->castling_short_b,
        board->castling_short_w
    };

    int res = 0;
    int coeff = 1;

    for (int i = 0; i<4; i++) {
        res += coeff * castlings_rights[i];
        coeff *= 2;
    }
    return res;
}

U64 generateHashKey (Board* board) {
    U64 final_hash = 0ULL;

    for (int square = 0; square < 64; square++) {

        if (checkIfPiece(board->squares[square]))
            final_hash ^= piece_keys[getPieceKey (board->squares[square])] [square];
    }

    if (board->getEnPassant()) {
        final_hash ^= enpassant_keys[squareToIdx(board->getEnPassantSquare())];
    }

    final_hash ^= castlings_keys[getCastlingsKey(board)];

    if (!board->isWhite())
        final_hash ^= side_key;
    

    resetSeed();

    return final_hash;
}

