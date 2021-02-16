# ViCTORIA

![](images/icon150x150.png)

ViCTORIA is a UCI chess engine built from scratch using C++ 20.

ViCTORIA performs a in-depth analysis of the position with a handcrafted evaluation function.

It can perform an analysis in reasonable (10-25 seconds) time between depth 6 and 8+, depending on the number of possible moves.

You can play against it on Lichess [here](https://lichess.org/@/ViCTORIA_engine).

Its elo rating is 1694 in blitz (February 2021).

ViCTORIA is not a complete chess program and requires a UCI-compatible graphical user interface (GUI) (e.g. XBoard with PolyGlot, Scid, Cute Chess, eboard, Arena, Sigma Chess, Shredder, Chess Partner or Fritz) in order to be used comfortably

## Build
ViCTORIA is built from scratch, so you don't need any C++ library, only a compiler that supports C++ 20.

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
./ViCTORIA
```
UCI commands:
+ ```position starpos [moves move_list]```
+ ```position fen your_fen [moves move_list]```
+ ```go depth n```
+ ```go infinite```: wait for the stop command
+ ```go movetime t```: search for t milliseconds
+ ```go wtime t1 btime t2 winc t3 binc t4```: White has ```t1``` ms on clock Black has ```t2``` ms on clock. White increment their time by ```t3``` ms and Black increment their time by ```t4``` ms

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
+ Transposition table with Zobrist Hashing (500 000 positions)

You can add an opening table like this [one](https://mega.nz/file/fFl1CK4I#gMdpOIj_1FSgyxZzVhFHoJPsaeJYWjTjygSgOaUOTsQ). You have to modify the path in ```engine.h```.
The table have to be in UCI syntax, you can use [pgn-extract](https://www.cs.kent.ac.uk/people/staff/djb/pgn-extract/) to convert your table into this format.

## License
[GNU v3](https://choosealicense.com/licenses/gpl-3.0/)