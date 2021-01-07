#pragma once

const float pawn_table [] = {
        0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,
        10.0,  10.0,  10.0,  10.0,  10.0,  10.0,  10.0,  10.0,
        2.0,  2.0,  4.0,  6.0,  6.0,  4.0,  2.0,  2.0,
        1.0,  1.0,  2.0,  5.0,  5.0,  2.0,  1.0,  1.0,
        0.0,  0.0,  0.0,  4.0,  4.0,  0.0,  0.0,  0.0,
        1.0, -1.0, -2.0,  0.0,  0.0, -2.0, -1.0,  1.0,
        1.0,  2.0, 2.0,  -4.0, -4.0,  2.0,  2.0,  1.0,
        0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0
};

const float bishop_table [] = {
        -4.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -4.0,
        -2.0,  0.0,  0.0,  0.0,  0.0,  0.0,  0.0, -2.0,
        -2.0,  0.0,  1.0,  2.0,  2.0,  1.0,  0.0, -2.0,
        -2.0,  1.0,  1.0,  2.0,  2.0,  1.0,  1.0, -2.0,
        -2.0,  0.0,  2.0,  2.0,  2.0,  2.0,  0.0, -2.0,
        -2.0,  2.0,  2.0,  2.0,  2.0,  2.0,  2.0, -2.0,
        -2.0,  1.0,  0.0,  0.0,  0.0,  0.0,  1.0, -2.0,
        -4.0, -2.0, -2.0, -2.0, -2.0, -2.0, -2.0, -4.0
};

const float knight_table [] = {
        -10.0, -8.0, -6.0, -6.0, -6.0, -6.0, -8.0, -10.0,
        -8.0, -4.0,  0.0,  0.0,  0.0,  0.0, -4.0, -8.0,
        -6.0,  0.0,  2.0,  3.0,  3.0,  2.0,  0.0, -6.0,
        -6.0,  1.0,  3.0,  4.0,  4.0,  3.0,  1.0, -6.0,
        -6.0,  0.0,  3.0,  4.0,  4.0,  3.0,  0.0, -6.0,
        -6.0,  1.0,  2.0,  3.0,  3.0,  2.0,  1.0, -6.0,
        -8.0, -4.0,  0.0,  1.0,  1.0,  0.0, -4.0, -8.0,
        -10.0, -8.0, -6.0, -6.0, -6.0, -6.0, -8.0, -10.0
};

const float rook_table [] = {
        0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 
        1.0, 2.0, 2.0, 2.0, 2.0, 2.0, 2.0, 1.0, 
        -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 
        -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 
        -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 
        -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 
        -1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0, 
        0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0
};

const float queen_table [] = {
        -4.0, -2.0, -2.0, -1.0, -1.0, -2.0, -2.0, -4.0, 
        -2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -2.0, 
        -2.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -2.0, 
        -1.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0, 
        0.0, 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, -1.0, 
        -2.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, -2.0, 
        -2.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, -2.0, 
        -4.0, -2.0, -2.0, -1.0, -1.0, -2.0, -2.0, -4.0
};

const float king_table [] = {
        -6.0, -8.0, -8.0, -10.0, -10.0, -8.0, -8.0, -6.0, 
        -6.0, -8.0, -8.0, -10.0, -10.0, -8.0, -8.0, -6.0, 
        -6.0, -8.0, -8.0, -10.0, -10.0, -8.0, -8.0, -6.0, 
        -6.0, -8.0, -8.0, -10.0, -10.0, -8.0, -8.0, -6.0, 
        -4.0, -6.0, -6.0, -8.0, -8.0, -6.0, -6.0, -4.0, 
        -2.0, -4.0, -4.0, -4.0, -4.0, -4.0, -4.0, -2.0, 
        4.0, 4.0, 0.0, 0.0, 0.0, 0.0, 4.0, 4.0, 
        4.0, 6.0, 2.0, 0.0, 0.0, 6.0, 4.0, 4.0
};

const float king_table_end_game [] = {
        -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0,
        -10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -10.0,
        -10.0, 0.0, 10.0, 10.0, 10.0, 10.0, 0.0, -10.0,
        -10.0, 0.0, 10.0, 20.0, 20.0, 10.0, 0.0, -10.0,
        -10.0, 0.0, 10.0, 20.0, 20.0, 10.0, 0.0, -10.0,
        -10.0, 0.0, 10.0, 10.0, 10.0, 10.0, 0.0, -10.0,
        -10.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -10.0,
        -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0, -10.0,
};