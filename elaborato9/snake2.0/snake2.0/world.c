#include <stdlib.h>
#include <time.h>
#include "world.h"
#include "snake.h"

/* Allocates the world structure */
static struct world *world_alloc(unsigned int rows, unsigned int cols);

static enum cell **board_alloc(unsigned int row, unsigned int col);

static void board_free(enum cell **board);

static void world_init(struct world *W, unsigned int food_amount);

static void random_food(struct world *W, enum cell food);

enum status update(struct world *W, enum direction *dir);

static enum direction select_dir(struct world *W, enum direction dir);


struct world *world_create(unsigned int rows, unsigned int cols, unsigned int food_amount) {
	struct world *w = NULL;

	if((w = world_alloc(rows,cols)) != NULL)
		world_init(w,food_amount);

	return w;
}

void world_destroy(struct world *W) {
	if(W != NULL) {
		board_free(W->board);
		snake_kill(W->snake);
		free(W);
	}
}

enum status world_update(struct world *W, enum direction *dir) {
	snake_move(W->snake,*dir);	
	return update(W,dir);
}


static enum cell **board_alloc(unsigned int row, unsigned int col) {
	enum cell **board = (enum cell **)calloc(row,sizeof(enum cell *));
	
	if(board != NULL) {
		board[0] = (enum cell *)calloc(row*col,sizeof(enum cell));
		if(board[0] == NULL) {
			free(board);
			board = NULL;
		} else {
			unsigned int i;

			for(i = 1; i < row; i++)
				board[i] = &board[0][i*col];
		}
	}
	return board;
}

static void board_free(enum cell **board) {
	if(board != NULL) {
		free(board[0]);
		free(board);
	}
}

static struct world *world_alloc(unsigned int rows, unsigned int cols) {
	struct world *W = NULL;

	
	if((W = (struct world *)calloc(1,sizeof(struct world))) != NULL) {
		W->rows = rows;
		W->cols = cols;
		if((W->board = board_alloc(rows,cols)) == NULL) 
			free(W);
	}
	
	return W;
}

static void random_food(struct world *W, enum cell food) {
	unsigned int i, j;
	int tries = W->rows*W->cols-W->snake->length;
	struct position head = snake_head(W->snake);

	do {
		i = rand() % W->rows;
		j = rand() % W->cols;
	} while(--tries > 0 && (W->board[i][j] != EMPTY || (head.i == i && head.j == j)));

	if(tries > 0)
		W->board[i][j] = food;
}


static void world_init(struct world *W, unsigned int food_amount) {
	unsigned int i, j;

	srand(time(0));

	for(i = 0; i < W->rows; i++)
		for(j = 0; j < W->cols; j++)
			W->board[i][j] = EMPTY;
		
	W->snake = snake_create(W->rows,W->cols);

	for(i = 0; i < food_amount; i++) {
		random_food(W,GOOD_FOOD);
		random_food(W,BAD_FOOD);
		random_food(W,CREEPY_FOOD);
	}
}


enum status update(struct world *W, enum direction *dir) {
	if(snake_knotted(W->snake)) {
		return GAMEOVER;
	} else {
		struct position head = snake_head(W->snake);
		enum cell type = W->board[head.i][head.j];

		W->board[head.i][head.j] = EMPTY; 
		switch(type) {
			case GOOD_FOOD:   
				snake_increase(W->snake,*dir);
				if(update(W,dir) == GAMEOVER) {
					return GAMEOVER;
				} else {
					random_food(W,GOOD_FOOD);
					return CONTINUE;
				} 
			case BAD_FOOD: 
				if(W->snake->length > 1) { 
					snake_decrease(W->snake,(unsigned int)(W->snake->length/2.0+0.5));
				}
				random_food(W,BAD_FOOD); 
				return CONTINUE;
			case CREEPY_FOOD: 
				snake_reverse(W->snake); 
				*dir = select_dir(W,*dir); 
				random_food(W,CREEPY_FOOD); 
				return CONTINUE;
			default:          
					return CONTINUE;
		}
	}
}

static enum direction select_dir(struct world *W, enum direction dir) {	
	if(W->snake->length == 1) { 
		switch(dir) {
			case UP:    return DOWN;
			case DOWN:  return UP;	
			case LEFT:  return RIGHT;
			case RIGHT: return LEFT;
		}		
	} else { 
		struct position head = snake_head(W->snake);
		struct position neck = snake_body(W->snake,1);

		if(head.i == neck.i) 
			return head.j == (neck.j-1+W->cols)%W->cols ? LEFT : RIGHT;
		else                 
			return head.i == (neck.i-1+W->rows)%W->rows ? UP : DOWN;
	}
}
