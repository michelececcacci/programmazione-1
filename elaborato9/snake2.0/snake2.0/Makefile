CFLAG = -Wall -pedantic -Wno-comment -O3 -std=c89
LDFLAGS = -l

ifeq ($(OS),Windows_NT)
	LDFLAGS += pdcurses
else
	LDFLAGS += ncurses
endif
 
all: snake

snake.o: snake.h snake.c
	gcc $(CFLAG) -c snake.c

world.o: world.h world.c
	gcc $(CFLAG) -c world.c

display.o: world.h display.h display.c
	gcc $(CFLAG) -c display.c

snake: snake.h world.h display.h snake.o world.o display.o main.c
	gcc $(CFLAG) snake.o world.o display.o main.c -o snake $(LDFLAGS)

clean:
	rm -rf *.o snake 
