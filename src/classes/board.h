#include "pieces/pawn.h"
#include <vector>
using namespace std;

class Board {
    public:
        Board (string fen);
        Board ();
        void print_pieces();
    private:
        vector<Piece> pieces;
};