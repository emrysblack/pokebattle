##
## makefile for pokemon
##

a.out : game.o trainer.o pokeTest.o
	g++ game.o trainer.o pokeTest.o

game.o : game.cpp game.h trainer.h pokemon.h move.h server.h
	g++ -c game.cpp

trainer.o : trainer.cpp trainer.h pokemon.h
	g++ -c trainer.cpp

pokeTest.o : pokeTest.cpp trainer.h pokemon.h move.h game.h server.h
	g++ -c pokeTest.cpp

clean :
	rm *.o a.out