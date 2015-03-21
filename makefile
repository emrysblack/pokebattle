##
## makefile for pokemon
##

a.out : game.o trainer.o pokeTest.o attack.o
	g++ game.o trainer.o pokeTest.o attack.o

game.o : game.cpp game.h trainer.h pokemon.h move.h server.h attack.h
	g++ -c game.cpp

trainer.o : trainer.cpp trainer.h pokemon.h
	g++ -c trainer.cpp

pokeTest.o : pokeTest.cpp trainer.h pokemon.h move.h game.h server.h
	g++ -c pokeTest.cpp

attack.o : attack.cpp attack.h pokemon.h move.h
	g++ -c attack.cpp

clean :
	rm *.o a.out