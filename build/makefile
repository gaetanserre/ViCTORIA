args = -std=c++2a -O3

all: IA_chess

IA_chess : piece.o pawn.o rook.o knight.o bishop.o queen.o king.o board.o ../src/main.cpp
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

board.o: ../src/classes/board/board.cpp
	g++ $< $(args) -c

clean:
	rm *.o
	rm -rf ../out