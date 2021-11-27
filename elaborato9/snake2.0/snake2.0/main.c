#include <stdio.h>
#include <stdlib.h>
#include "world.h"
#include "snake.h"
#include "display.h"

#define MIN(x,y) ((x)<(y)?(x):(y))

#define WORLD_ROWS       30
#define WORLD_COLS       (2*WORLD_ROWS) 
#define FOOD_AMOUNT      10

int main() {
	enum direction dir;
	struct world *W;
	int max_row, max_col;
	int new_game;

	do {
		dir = RIGHT; 
		display_open();

		display_width(&max_row,&max_col);

		W = world_create(MIN(WORLD_ROWS,max_row-5),MIN(WORLD_COLS,max_col),FOOD_AMOUNT);

		if(W == NULL) { 
			display_close();
			fprintf(stderr,"Error: cannot initialize the game\n");
			return 1;
		}

		do {
			display_plot(W);
			dir = display_input(W,dir);
		} while(world_update(W,&dir) == CONTINUE);

		new_game = display_gameover(W);

		world_destroy(W);
		display_close();
	} while(new_game);

  return 0;
}
