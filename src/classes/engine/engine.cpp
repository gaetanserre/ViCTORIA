#include "engine.h"
#include <stdio.h>

Engine::Engine() {
    this->name = "Victoria UCI chess engine";
    this->board = new Board();
    this->board->init();

    this->killerMoves = vector<Ply> (this->maxDepth);

    cout << this->name << endl;
}


Engine::~Engine() {
    delete this->board;
}

/*************** Begin search in opening book functions ***************/

// Checks if the line corresponds to a game
bool isGame (string line) {
    return line[0] != '[' && line.size() > 1;
}

bool isPly (string line, Ply p) {
    if (line[0] == p.dep.row && line[1] == char(p.dep.line + '0')) {
        return line [2] == p.stop.row && line[3] == char(p.stop.line + '0');
    }
    return false;
}

// Checks if the game contained in line is a win
bool isWin (string line, bool white) {
    int end = line.size() - 1;

    if (line[end] == '2') return false;
    if (line[end] == '1') return ! white;
    else return white;
}

// Erase the n firsts char in line
void eraseNchars (string &line, int n) {
    for (int i = 0; i<n; i++)
        line.erase(line.begin());
}

// Convert the first ply in line into a ply
Ply lineToPly (string line) {
    string move = "";
    for (int i = 0; i<4; i++)
        move += line[i];

    return Board::StringToPly(move);
}



/*
    We search for the next move in a opening book
    This function is called only if the starting position was
    the standard starting position in chess
*/
void Engine::searchOpeningBook (int depth) {
    this->is_terminated = false;

    /*
        If no move has been played, it's white turn and we return e2e4
        which is one of the most strongest opening
    */
    if (this->moves.size() == 0) {
        Score s;
        s.plies.push_back(Ply(Square("e2"), Square("e4")));
        s.print_info(1, 1, 0, true);
        this->best_move = s;
        this->is_terminated = true;

        return;
    }

    ifstream opening_book;
    opening_book.open (this->opening_table_path);

    if (opening_book.is_open()) {
        cout << "Searching in opening book.." << endl;
        string line;
        while (getline(opening_book, line)) {

            // We check if the line corresponds to a game
            if (isGame (line)) {
                
                // We check if the game contains the moves already played.
                bool found = true;
                for (Ply p : this->moves) {
                    if (isPly (line, p)) {
                        eraseNchars(line, 5);
                    } else {
                        found = false;
                        break;
                    }
                }

                // If yes, we return it
                if (found && isWin(line, this->board->isWhite())) {
                    Score s;
                    s.plies.push_back(lineToPly(line));
                    opening_book.close();
                    s.print_info(1, 1, 0, this->board->isWhite());
                    this->best_move = s;

                    this->is_terminated = true;
                    return;
                }
            }
        }
        opening_book.close();
        this->not_in_opening_table = true;
        MultiDepthAnalysis(depth);
        return;
    }
    this->not_in_opening_table = true;
    MultiDepthAnalysis(depth);
}

/*************** End search in opening book functions ***************/



/*************** Begin evaluation funcion ***************/

Score Engine::evalPosition(Board* board) {
    vector<Ply> legal_moves = board->getLegalMoves();
    int size = legal_moves.size();
    
    if (size == 0) {
        if (board->isCheck())
            return Score(-mate_value);
        else return Score();

    } else {
        
        int wK = 0, bK = 0, wQ = 0, bQ = 0, wR = 0, bR = 0,
            wN = 0, bN = 0, wB = 0, bB =0, wP = 0, bP = 0;
        
        int material_score = board->getNbCastlings(board->isWhite()) * 10;

        for (int i = 0; i<64; i++) {

            if (checkIfPiece(board->squares[i])) {
                char name = board->squares[i]->getName();
                material_score += board->squares[i]->getPieceValue(this->end_game);

                if (name == 'k') {
                    board->squares[i]->isWhite() ? wK++ : bK++;
                }

                if (name == 'q') {
                    board->squares[i]->isWhite() ? wQ++ : bQ++;
                }

                if (name == 'r') {
                    board->squares[i]->isWhite() ? wR++ : bR++;
                }

                if (name == 'n') {
                    board->squares[i]->isWhite() ? wN++ : bN++;
                }

                if (name == 'b') {
                    board->squares[i]->isWhite() ? wB++ : bB++;
                }

                if (name == 'p') {
                    board->squares[i]->isWhite() ? wP++ : bP++;
                }
            }
        }

        if (this->end_game) {

            // Pair of bishop
            if (wB >= 2)
                material_score += 10;

            if (bB >= 2)
                material_score -= 10;
            
            // Increase pawn value
            material_score += wP*200;
            material_score -= bP*200;

        }

        //cout << wK << " " << bK << " " << wQ << " " << bQ << " " << wR << " " << bR << " " << wN << " " << bN << " " << wB << " " << bB << " " << wP << " " << bP << endl;
            

        const float mobilityV = 3;

        int mobility_white, mobility_black;
        int *other_mobility;

        if (board->isWhite()) {
            mobility_white = legal_moves.size();
            other_mobility = &mobility_black;
        }
        else {
            mobility_black = legal_moves.size();
            other_mobility = &mobility_white;
        }
            
        // Compute mobility for the other side
        board->changeSide();
        board->setEnPassant(false);
        board->computeLegalMoves();
        
        *other_mobility = board->getLegalMoves().size();
        board->changeSide();

        int mobility_score = mobilityV * (mobility_white - mobility_black);
        int score = (material_score + mobility_score) * (board->isWhite() ? 1 : -1);

        return Score(score);

    }
}

/*************** End evaluation funcion ***************/


/*************** Begin Heuristics funcs ***************/

bool Engine::NullPruning (Score beta, int depth, Score &res) {
    this->board->changeSide();
    Score score = AlphaBetaNegamax (depth - 1 - 2, Score (-beta.score), Score (-beta.score+1));
    this->board->changeSide();
    score.score = -score.score;

    if (score.score >= beta.score) {
        res = beta;
        return true;
    }
    return false;
}

/*************** End Heuristics funcs ***************/



/*************** Begin useful funcs for deep search ***************/

bool Engine::checkRepetitions (string position) {
    int count = 1;
    for (int i = 0; i<this->positions.size() - 1; i++) {
        if (positions[i] == position)
            count ++;
    }
    return count == 3;
}

bool isCapture (int idx_p1, int idx_p2, U64 occupancy) {
    return get_bit(occupancy, idx_p1) && get_bit (occupancy, idx_p2);
}

int getPieceIdx (char name) {
    switch (name) {
        case 'k':
            return 0;
        case 'p':
            return 1;
        case 'n':
            return 2;
        case 'b':
            return 3;
        case 'r':
            return 4;
        case 'q':
            return 5;
        default:
            return -1;
    }
}

vector<Move> Engine::PlyToMove (vector<Ply> move_list) {
    vector<Move> res;
    int size = this->best_move.plies.size();

    for (int i = 0; i < move_list.size(); i++) {
        int idx1 = squareToIdx(move_list[i].dep);
        int idx2 = squareToIdx(move_list[i].stop);

        Move m = {
            move_list[i],
            0
        };

        if (size > 0 && move_list[i] == this->best_move.plies[0]) {
            m.score = 1000;
        } 
    
        else if (isCapture (idx1, idx2, this->board->occupancy)) {
            m.score = 900;
            m.score += capture_table
                      [getPieceIdx (this->board->squares[idx1]->getName())]
                      [getPieceIdx (this->board->squares[idx2]->getName())];
        }

        else if (this->killerMoves[searchPly] == move_list[i]) {
            m.score = 800;
        }

        res.push_back (m);
    }
    return res;
}

vector<Move> Engine::sortMoves () {
    this->board->computeLegalMoves();
    vector<Ply> legal_moves = this->board->getLegalMoves();
    vector <Move> res = PlyToMove(legal_moves);

    sort (res.begin(), res.end(), [](Move m1, Move m2) { return m1.score > m2.score; });

    return res;
}

/*************** End useful funcs for deep search ***************/



/*************** Begin negamax alpha beta deep search ***************/
int nodes = 0;
Score Engine::AlphaBetaNegamax (int depth, Score alpha, Score beta) {
    nodes++;

    vector<Move> move_list = sortMoves ();
    
    int size = move_list.size();

    // We don't check for repetitions at the root
    if (nodes > 1) {
        string pos = this->board->getFen(false);

        this->positions.push_back (pos);
    

        if (checkRepetitions (pos)) return Score (0);
    }

    if (depth == 0 || size == 0) return evalPosition(this->board);

    for (int i = 0; i<size; i++) {

        /*
            If we want to kill the thread, we return a random Score to skip all variants
        */
        if (this->terminate_thread) {
            return Score();
        }

        this->board->play_move(move_list[i].ply, true);
        this->searchPly++;
        
        Score score = AlphaBetaNegamax (depth - 1, Score(-beta.score), Score(-alpha.score));

        this->board->undo_move();
        this->searchPly--;
        this->positions.pop_back();


        score.score = -score.score;
        score.plies.push_back(move_list[i].ply);
        
        if (alpha.score >= beta.score) {

            int i1 = squareToIdx (move_list[i].ply.dep);
            int i2 = squareToIdx (move_list[i].ply.stop);
            if (!isCapture(i1, i2, this->board->occupancy)) {
                this->killerMoves[this->searchPly] = move_list[i].ply;
            }

            bool check_mate = alpha.score == mate_value && alpha.plies.size() >= 1;
            return (check_mate ? alpha : beta);
        }
        
        alpha = Score::max (score, alpha);
    }
    return alpha;
}

/*************** End negamax alpha beta deep search ***************/


/*************** Begin in depth analysis functions ***************/

void Engine::inDepthAnalysis (int depth) {

    Score alpha (-mate_value); // Black checkmate
    Score beta (mate_value); // White Checkmate

    Score bestMove = AlphaBetaNegamax (depth, alpha, beta);

    reverse(bestMove.plies.begin(), bestMove.plies.end());

    if (!this->board->isWhite()) bestMove.score *= -1;
    
    /*
        If we want to kill the thread, we don't want best_move to be modified
    */
    if (!this->terminate_thread) this->best_move = bestMove;
}


void Engine::MultiDepthAnalysis (int depth) {
    this->is_terminated = false;

    for (int i = 1; i<= depth; i++) {
        if (this->terminate_thread) break;
        nodes = 0;

        this->searchPly = 0;

        clock_t start = startChrono();
        inDepthAnalysis(i);
        int dur = stopChrono(start);

        /*
            If we want to kill the thread,
            we don't want to print the move that hasn't been really calculated
            since we returned a random Score from the Negamax function
        */
        if (!this->terminate_thread)
            this->best_move.print_info(i, nodes, dur, this->board->isWhite());

        /* 
            We check if there is a inevitable checkmate.
            If a checkmate in n moves has been found, it's useless to go deeper than depth n
        */
        if (this->best_move.score == mate_value) break;
    }
    this->is_terminated = true;
}

/*************** End in depth analysis functions ***************/
