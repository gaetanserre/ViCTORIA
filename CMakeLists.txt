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
        src/classes/bitboard/magic_bitboard.h
        src/classes/bitboard/magics_number.h
        src/classes/board/pieces/bishop.cpp
        src/classes/board/pieces/bishop.h
        src/classes/board/pieces/empty.h
        src/classes/board/pieces/king.cpp
        src/classes/board/pieces/king.h
        src/classes/board/pieces/knight.cpp
        src/classes/board/pieces/knight.h
        src/classes/board/pieces/pawn.cpp
        src/classes/board/pieces/pawn.h
        src/classes/board/pieces/piece.cpp
        src/classes/board/pieces/piece.h
        src/classes/board/pieces/queen.cpp
        src/classes/board/pieces/queen.h
        src/classes/board/pieces/rook.cpp
        src/classes/board/pieces/rook.h
        src/classes/board/pieces/table.h
        src/classes/board/board.cpp
        src/classes/board/board.h
        src/classes/board/ply.h
        src/classes/board/square.h
        src/classes/engine/constants/capture_table.h
        src/classes/engine/score/score.cpp
        src/classes/engine/score/score.h
        src/classes/engine/transposition_table/hash.cpp
        src/classes/engine/transposition_table/hash.h
        src/classes/engine/transposition_table/hashKey.cpp
        src/classes/engine/transposition_table/hashKey.h
        src/classes/engine/engine.cpp
        src/classes/engine/engine.h
        src/classes/engine/evaluation.cpp
        src/classes/engine/parse_expr.cpp
        src/main.cpp)
