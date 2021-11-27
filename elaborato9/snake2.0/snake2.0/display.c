#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <curses.h>
#include "display.h"

static void display_timeout(struct world *W);

static int display_pause(struct world *W);

static void display_border(struct world *W, unsigned int start_row, unsigned int start_col);

static void display_food(struct world *W, unsigned int start_row, unsigned int start_col);

static void display_snake(struct world *W, unsigned int start_row, unsigned int start_col);

void display_width(int *max_row, int *max_col) {
	getmaxyx(stdscr,*max_row,*max_col);	
}

void display_open(void) {
	initscr();
	cbreak();
	noecho();               
	keypad(stdscr, TRUE); 
	curs_set(0);          
}

void display_plot(struct world *W) {
	unsigned int start_row = (LINES - W->rows)/2;
	unsigned int start_col = (COLS - W->cols)/2;

	display_timeout(W);
	erase();
	mvprintw(start_row-2,start_col,"SCORE: %u",W->snake->length);
	mvprintw(start_row+W->rows+1,start_col+1,"[Q]uit [P]ause");
	display_border(W,start_row,start_col);
	display_food(W,start_row,start_col);
	display_snake(W,start_row,start_col);
	refresh();
}

int display_gameover(struct world *W) {
	unsigned int start_row = (LINES - W->rows)/2;
	unsigned int start_col = (COLS - W->cols)/2;
	struct position head = snake_head(W->snake);
	char *str = "GAME OVER";
	char new_game;

	erase();
	mvprintw(start_row-2, start_col,"SCORE: %u",W->snake->length);
	display_border(W,start_row,start_col);
	display_food(W,start_row,start_col);
	display_snake(W,start_row,start_col);
	mvaddch(start_row+head.i, start_col+head.j,'X');
	mvprintw(start_row+W->rows+1,start_col+1,"[Q]uit  [R]estart");
	mvprintw(start_row+W->rows+2,start_col+(((int)W->cols-strlen(str))/2),str);
	refresh();

	timeout(-1); 
	while((new_game = getch()) != 'q' && new_game != 'r');

	return new_game == 'r';
}

void display_close(void) {
	endwin();
}

enum direction display_input(struct world *W, enum direction previous) {
	int ch = getch();

	switch (ch) {
		case KEY_LEFT:  
			if (previous != RIGHT) return LEFT;
			else break;
		case KEY_RIGHT: 
			if (previous != LEFT)  return RIGHT;
			else break;
		case KEY_DOWN:  
			if (previous != UP)    return DOWN;
			else break;
		case KEY_UP:   
			if (previous != DOWN)  return UP;
			else break;
		case 'p': 
			if(display_pause(W) == 1)
				break;
		case 'q': 
			display_close();
			exit(0);
	}
	return previous;
}

static void display_timeout(struct world *W) {
	unsigned int time = MINIMUM_TIMEOUT < W->snake->length ? MINIMUM_TIMEOUT : STARTING_TIMEOUT-W->snake->length+1;
	timeout(time);
}

static int display_pause(struct world *W) {
	unsigned int start_row = (LINES - W->rows)/2;
	unsigned int start_col = (COLS - W->cols)/2;
	char resume;

	erase();
	mvprintw(start_row-2,start_col,"SCORE: %u",W->snake->length);
	mvprintw(start_row+W->rows+1,start_col+1,"[Q]uit [R]esume");
	display_border(W,start_row,start_col);
	display_food(W,start_row,start_col);
	display_snake(W,start_row,start_col);
	refresh();
	
	timeout(-1); 
	while((resume = getch()) != 'q' && resume != 'r');
	return resume == 'r';
}

static void display_border(struct world *W, unsigned int start_row, unsigned int start_col) {
	unsigned int i;
	
	mvaddch(start_row-1,start_col-1,ACS_ULCORNER);
	mvaddch(start_row-1,start_col+W->cols,ACS_URCORNER);
	mvaddch(start_row+W->rows,start_col-1,ACS_LLCORNER);
	mvaddch(start_row+W->rows,start_col+W->cols,ACS_LRCORNER);

	for(i = 0; i < W->rows; i++) {
		mvaddch(start_row+i,start_col-1,ACS_VLINE);
    mvaddch(start_row+i,start_col+W->cols,ACS_VLINE);
	}

	for(i = 0; i < W->cols; i++) {
		mvaddch(start_row-1,start_col+i,ACS_HLINE);
		mvaddch(start_row+W->rows,start_col+i,ACS_HLINE);
	}
	
}

static void display_food(struct world *W, unsigned int start_row, unsigned int start_col) {
	unsigned int i,j;

	for(i = 0; i < W->rows; i++)
		for(j = 0; j < W->cols; j++)
			switch(W->board[i][j]) {
				case GOOD_FOOD:   mvaddch(start_row+i,start_col+j,GOOD_FOOD_SYMBOL); break;
				case BAD_FOOD:    mvaddch(start_row+i,start_col+j,BAD_FOOD_SYMBOL); break;
				case CREEPY_FOOD: mvaddch(start_row+i,start_col+j,CREEPY_FOOD_SYMBOL); break;
				default: break;
			}
}

static void display_snake(struct world *W, unsigned int start_row, unsigned int start_col) {
	unsigned int i;
	struct position p;
	for(i = 0; i < W->snake->length; i++) {
		p = snake_body(W->snake,i);
		mvaddch(start_row+p.i, start_col+p.j,SNAKE_SYMBOL);
	}
}
