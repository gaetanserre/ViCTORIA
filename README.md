# Victoria
Victoria is a UCI chess engine build from scratch using C++ 20.
Victoria performs a in-depth analysis of the position with a handcrafted evaluation function.
Victoria can perform an analysis in reasonable time between depth 5 and 7, depending on the number of pieces on the chessboard.
I estimate its elo to around 1500, because it beats almost all engine at 1500 elo on [chess.com](www.chess.com)
Its also beats almost every human players under 1500 elo.
Victoria is not a complete chess program and requires a UCI-compatible graphical user interface (GUI) (e.g. XBoard with PolyGlot, Scid, Cute Chess, eboard, Arena, Sigma Chess, Shredder, Chess Partner or Fritz) in order to be used comfortably

[Opening book 2.5M games](https://mega.nz/file/fFl1CK4I#gMdpOIj_1FSgyxZzVhFHoJPsaeJYWjTjygSgOaUOTsQ)

## Build
Victoria is build from scratch so you don't need any C++ library, only a compiler that support C++ 20.
If you are on Linux or macOs, you can use the makefile in the ```build``` directory like this:
```bash
cd build
make
<<<<<<< Updated upstream
../out./AlphaBeta_chess
[position fen type_your_fen] (optional)
go
=======
>>>>>>> Stashed changes
```
If you are on Windows, use your own compiler.
In the future, I will provide binaries.

## Usage
```bash
cd out
./Victoria
```
UCI commands:
+ position starpos moves [move_list]
+ position fen your_fen moves [move_list]
+ go depth n
+ go infinite: wait for the stop command
+ go movetime t: search for t milliseconds

## Features
<<<<<<< Updated upstream
+ Alpha-Beta pruning: 300% more efficient
+ Magic bitboard for sliding pieces: 200% more efficient
+ Simple move ordering (captures & iterative deepening)
+ Killer move heuristic
=======
+ Alpha-Beta pruning
+ Magic bitboard for sliding pieces
+ Move ordering
    + Killer move
>>>>>>> Stashed changes
