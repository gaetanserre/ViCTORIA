cmake_minimum_required(VERSION 3.17)
project(ViCTORIA)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -pthread")

include_directories(src/classes/bitboard)
include_directories(src/classes/board)
include_directories(src/classes/board/pieces)
include_directories(src/classes/engine)
include_directories(src/classes/engine/constants)
include_directories(src/classes/engine/score)
include_directories(src/classes/engine/transposition_table)

add_executable(ViCTORIA
        src/classes/bitboard/magic_bitboard.cpp
        src/classes/board/pieces/bishop.cpp
        src/classes/board/pieces/king.cpp
        src/classes/board/pieces/knight.cpp
        src/classes/board/pieces/pawn.cpp
        src/classes/board/pieces/piece.cpp
        src/classes/board/pieces/queen.cpp
        src/classes/board/pieces/rook.cpp
        src/classes/board/board.cpp
        src/classes/engine/score/score.cpp
        src/classes/engine/transposition_table/hash.cpp
        src/classes/engine/transposition_table/hashKey.cpp
        src/classes/engine/evaluator/evaluator.cpp
        src/classes/engine/engine.cpp
        src/classes/engine/parse_expr.cpp
        src/main.cpp)
