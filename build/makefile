args = -std=c++2a -O3

all: AlphaBeta_Chess

AlphaBeta_Chess : piece.o pawn.o rook.o knight.o bishop.o queen.o king.o magic_bitboard.o board.o score.o engine.o ../src/main.cpp
	rm -rf ../out
	mkdir ../out
	g++ $^ $(args) -o ../out/$@

pawn.o : ../src/classes/board/pieces/pawn.cpp piece.o
	g++ $< $(args) -c

rook.o : ../src/classes/board/pieces/rook.cpp piece.o
	g++ $< $(args) -c

knight.o : ../src/classes/board/pieces/knight.cpp piece.o
	g++ $< $(args) -c

bishop.o : ../src/classes/board/pieces/bishop.cpp piece.o
	g++ $< $(args) -c

queen.o : ../src/classes/board/pieces/queen.cpp piece.o
	g++ $< $(args) -c

king.o : ../src/classes/board/pieces/king.cpp piece.o
	g++ $< $(args) -c

piece.o : ../src/classes/board/pieces/piece.cpp
	g++ $< $(args) -c

magic_bitboard.o : ../src/classes/bitboard/magic_bitboard.cpp
	g++ $< $(args) -c

board.o: ../src/classes/board/board.cpp
	g++ $< $(args) -c

engine.o: ../src/classes/engine/engine.cpp score.o
	g++ $< $(args) -c

score.o: ../src/classes/engine/score.cpp
	g++ $< $(args) -c

clean:
	rm *.o
	rm -rf ../out