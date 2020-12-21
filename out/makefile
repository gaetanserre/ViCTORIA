args = -std=c++17

all: IA_chess

IA_chess : piece.o pawn.o board.o ../src/main.cpp
	g++ $^ $(args) -o $@

pawn.o : ../src/classes/pieces/pawn.cpp piece.o
	g++ $< $(args) -c

piece.o : ../src/classes/pieces/piece.cpp
	g++ $< $(args) -c

board.o: ../src/classes/board.cpp
	g++ $< $(args) -c

clean:
	rm *.o
	rm IA_chess