args = -std=c++17

all: IA_chess

IA_chess : piece.o pawn.o rook.o knight.o bishop.o queen.o king.o board.o ../src/main.cpp
	g++ $^ $(args) -o ../out/$@

pawn.o : ../src/classes/pieces/pawn.cpp piece.o
	g++ $< $(args) -c

rook.o : ../src/classes/pieces/rook.cpp piece.o
	g++ $< $(args) -c

knight.o : ../src/classes/pieces/knight.cpp piece.o
	g++ $< $(args) -c

bishop.o : ../src/classes/pieces/bishop.cpp piece.o
	g++ $< $(args) -c

queen.o : ../src/classes/pieces/queen.cpp piece.o
	g++ $< $(args) -c

king.o : ../src/classes/pieces/king.cpp piece.o
	g++ $< $(args) -c

piece.o : ../src/classes/pieces/piece.cpp
	g++ $< $(args) -c

board.o: ../src/classes/board.cpp
	g++ $< $(args) -c

clean:
	rm *.o
	rm ../out/IA_chess