all: clean install

	./game_of_life examples/almosymmetric/almosymmetric.txt	

install: game_of_life
	

clean: 
	rm -rf *.o game_of_life

game_of_life: game_of_life.o 
	gcc -o game_of_life game_of_life.o

game_of_life.o:
	gcc -c game_of_life.c
