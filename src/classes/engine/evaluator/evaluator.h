#ifndef VICTORIA_EVALUATOR_H
#define VICTORIA_EVALUATOR_H

#include <vector>
#include <unordered_map>
#include "../score/score.h"
using namespace std;

class Evaluator {

    public:
        Score evalPosition(Board* board, bool end_game);

    private:

        int getNbCastlings (vector<Ply> legal_moves, Piece** squares, bool white);

        /*
        * We check if the opponent can check the king
        * If yes, we consider that the king is not safe (attaque à la découverte)
        */
        bool isKingSafe (Board* board);

        /*
         * We check for isolated and doubled pawns
         */
        void getPawnsInfos(unordered_map<int, int> pawn_columns, int &nb_isolated, int &nb_doubled);

};


#endif //VICTORIA_EVALUATOR_H
