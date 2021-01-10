args = -std=c++2a -O3

all: test

test : piece.o pawn.o rook.o knight.o bishop.o queen.o king.o magic_bitboard.o test.cpp
	g++ $^ $(args) -o $@

pawn.o : ../board/pieces/pawn.cpp piece.o
	g++ $< $(args) -c

rook.o :  ../board/pieces/rook.cpp piece.o
	g++ $< $(args) -c

knight.o :  ../board/pieces/knight.cpp piece.o
	g++ $< $(args) -c

bishop.o :  ../board/pieces/bishop.cpp piece.o
	g++ $< $(args) -c

queen.o :  ../board/pieces/queen.cpp piece.o
	g++ $< $(args) -c

king.o :  ../board/pieces/king.cpp piece.o
	g++ $< $(args) -c

piece.o :  ../board/pieces/piece.cpp
	g++ $< $(args) -c

magic_bitboard.o: magic_bitboard.cpp
	g++ $< $(args) -c

clean:
	rm *.o
	rm test