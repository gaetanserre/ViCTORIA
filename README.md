# Victoria
Victoria is a UCI chess engine built from scratch using C++ 20.

Victoria performs a in-depth analysis of the position with a handcrafted evaluation function.

It can perform an analysis in reasonable time between depth 5 and 7, depending on the number of pieces on the chessboard.

I estimate its elo to around 1500, because it beats almost all engines at 1500 elo on [chess.com](www.chess.com)
Its also beats almost every human players under 1500 elo.

Victoria is not a complete chess program and requires a UCI-compatible graphical user interface (GUI) (e.g. XBoard with PolyGlot, Scid, Cute Chess, eboard, Arena, Sigma Chess, Shredder, Chess Partner or Fritz) in order to be used comfortably

## Build
Victoria is built from scratch, so you don't need any C++ library, only a compiler that supports C++ 20.

If you are on Linux or macOs, you can use the makefile in the ```build``` directory like this:
```bash
cd build
make
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

## Evaluation function
Among other thing, the evaluation function takes into account:
+ Material score
+ Mobility score
+ Pieces/position tables
+ Different evaluation for end game (differents pieces/position tables, pawn value is slightly increased, etc...)

## Features
+ Alpha-Beta pruning
+ Magic bitboard for sliding pieces
+ Move ordering
    + Iterative deepening
    + Captures table
    + Killer move heuristic
You can add an opening table like this [one](https://mega.nz/file/fFl1CK4I#gMdpOIj_1FSgyxZzVhFHoJPsaeJYWjTjygSgOaUOTsQ). You have to modify the path in ```engine.h```.
The table have to be in UCI syntax, you can use [pgn-extract](https://www.cs.kent.ac.uk/people/staff/djb/pgn-extract/) to convert your table into this format.