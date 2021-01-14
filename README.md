# IA-Chess

[Opening book 2.5M games](https://mega.nz/file/fFl1CK4I#gMdpOIj_1FSgyxZzVhFHoJPsaeJYWjTjygSgOaUOTsQ)

## Usage
```
cd build
make
../out./AlphaBeta_chess
[position fen type_your_fen] (optional)
go
```

## Features
+ Alpha-Beta pruning: 300% more efficient
+ Magic bitboard for sliding pieces: 200% more efficient
+ Simple move ordering (captures & iterative deepening)
+ Killer move heuristic