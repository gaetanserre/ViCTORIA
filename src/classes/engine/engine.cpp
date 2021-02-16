#include "engine.h"
#include <stdio.h>

Engine::Engine() {
    this->name = "ViCTORIA chess engine";
    this->board = new Board();
    this->board->init();

    this->killerMoves = vector<Ply> (this->maxDepth);

    // init Zobrist hash keys
    initRandomKeys();
    this->zobrist_hash_key = generateHashKey(this->board);
    this->transposition_table = (Hash*) calloc(transposition_table_size, sizeof(Hash));

    cout << this->name << endl;
}


Engine::~Engine() {
    free (this->transposition_table);
    delete this->board;
}

/*************** Begin search in opening book functions ***************/

// Checks if the line corresponds to a game
bool isGame (string line) {
    return line[0] != '[' && line.size() > 1;
}

bool isPly (string line, Ply p) {
    if (line[0] == p.dep.rank && line[1] == char(p.dep.file + '0')) {
        return line [2] == p.stop.rank && line[3] == char(p.stop.file + '0');
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
        If no move has been played, it's white turn and we return d2d4
        which is one of the most strongest opening
    */
    if (this->moves.size() == 0) {
        Score s;
        s.plies.push_back(Ply(Square("d2"), Square("d4")));
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
        IterativeDepthAnalysis(depth);
        return;
    }
    this->not_in_opening_table = true;
    IterativeDepthAnalysis(depth);
}

/*************** End search in opening book functions ***************/



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


U64 Engine::makeMove (Ply move) {
    U64 old_key = this->zobrist_hash_key;
    this->board->play_move(move, true);
    this->zobrist_hash_key = generateHashKey(this->board);
    return old_key;
}


void Engine::undoMove (U64 hash_key) {
    this->board->undo_move();
    this->zobrist_hash_key = hash_key;
}

bool Engine::checkRepetitions () {
    int count = 1;
    int size = this->positions.size() - 1;
    string position = this->positions[size];
    for (int i = 0; i<size; i++) {
        if (positions[i] == position)
            count ++;
    }
    return count == 3;
}

bool Engine::checkIfEven (vector<Ply> move_list) {
    bool is_over = false;
    for (Ply move : move_list) {
        this->board->play_move(move, true);
        this->positions.push_back(this->board->getFen(false));

        is_over = checkRepetitions ();

        this->board->undo_move ();
        this->positions.pop_back ();

        if (is_over) return true;
    }
    return false;
}

/*************** End useful funcs for deep search ***************/



/*************** Begin negamax alpha beta deep search ***************/
Score Engine::AlphaBetaNegamax (int depth, Score alpha, Score beta) {
    
    // We check for repetitions
    if (checkRepetitions ()) return Score (0);

    // Check in transposition table
    int hashf = hashfALPHA;
    bool white = this->board->isWhite();
    
    Score s = ProbeHash(alpha, beta, depth, this->zobrist_hash_key, this->transposition_table, white);
    if (s.score != unknown_value) {

        // Check if now it's a draw with repetitions
        if (!checkIfEven (s.plies))
            return s;
    }



    vector<Move> move_list = sortMoves ();    
    int size = move_list.size();


    if (depth == 0 || size == 0) {
        Score val = evalPosition(this->board);
        val.score *= white ? 1 : -1;
        RecordHash(depth, val, hashfEXACT, this->zobrist_hash_key, this->transposition_table, white);
        return val;
    }

    this->nodes++;

    for (int i = 0; i<size; i++) {

        /*
            If we want to kill the thread, we return a random Score to skip all variants
        */
        if (this->terminate_thread) {
            return Score();
        }

        // We play the move and we push back the new position to check repetitions
        U64 old_key = this->makeMove(move_list[i].ply);
        string pos = this->board->getFen(false);
        this->positions.push_back (pos);

        this->searchPly++;
        
        Score score = AlphaBetaNegamax (depth - 1, Score(-beta.score), Score(-alpha.score));
        score.score *= -1;
        score.plies.push_back(move_list[i].ply);


        this->undoMove(old_key);
        this->searchPly--;
        this->positions.pop_back();


        
        if (score.score >= beta.score) {
            
            // Check for capture and killer moves
            int i1 = squareToIdx (move_list[i].ply.dep);
            int i2 = squareToIdx (move_list[i].ply.stop);
            if (!isCapture(i1, i2, this->board->occupancy)) {
                this->killerMoves[this->searchPly] = move_list[i].ply;
            }

            // Check if alpha is a checkmate
            bool check_mate_score = score.score == mate_value
                                    && score.plies.size() >= 1
                                    && (score.plies.size() < beta.plies.size()
                                    || beta.plies.size() == 0);

            // Record in transposition table
            RecordHash(
                depth,
                (check_mate_score ? score : beta),
                (check_mate_score ? hashfEXACT : hashfBETA),
                this->zobrist_hash_key,
                this->transposition_table,
                white);

            return (check_mate_score ? score : beta);
        }

        if (score > alpha) {
            hashf = hashfEXACT;
            alpha = score;
        }
    }

    // Record in transposition table
    RecordHash(depth, alpha, hashf, this->zobrist_hash_key, this->transposition_table, white);
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


void Engine::IterativeDepthAnalysis (int depth) {
    this->is_terminated = false;
    u_int64_t start = millis();

    for (int i = 1; i<= depth; i++) {
        if (this->terminate_thread) break;
        this->nodes = 0;

        this->searchPly = 0;

        inDepthAnalysis(i);
        u_int64_t elapsed = millis() - start;

        /*
            If we want to kill the thread,
            we don't want to print the move that hasn't been really calculated
            since we returned a random Score from the Negamax function
        */
        if (!this->terminate_thread)
            this->best_move.print_info(i, this->nodes, elapsed, this->board->isWhite());

        /* 
            We check if there is a inevitable checkmate.
            If a checkmate in n moves has been found, it's useless to go deeper than depth n
        */
        if (this->best_move.score == mate_value || this->best_move.score == -mate_value) break;
    }
    this->is_terminated = true;
}

/*************** End in depth analysis functions ***************/
