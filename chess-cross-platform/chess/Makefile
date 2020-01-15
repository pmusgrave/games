all: main.o 
	g++ main.cpp -o chess

main.o: main.cpp game.o board.o
	g++ -c main.cpp -o main.o

game.o: game.h game.cpp player.o king.h king.cpp queen.h queen.cpp rook.h rook.cpp knight.h knight.cpp bishop.h bishop.cpp pawn.h pawn.cpp
	g++ game.cpp -o game.o
#	g++ king.cpp -o king.o
#	g++ queen.cpp -o queen.o
#	g++ rook.cpp -o rook.o
#	g++ knight.cpp -o knight.o
#	g++ bishop.cpp -o bishop.o
#	g++ pawn.cpp -o pawn.o

player.o: player.h player.cpp
	g++ player.cpp -o player.o

square.o: square.h
	g++ square.h -o square.o

bishop.o: bishop.h bishop.cpp piece.o
	g++ -c bishop.cpp -o bishop.o

piece.o: piece.h piece.cpp
	g++ -c piece.cpp -o piece.o

clean:
	rm -r *.o chess
