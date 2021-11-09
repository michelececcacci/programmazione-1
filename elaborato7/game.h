#ifndef GAME_H
#define GAME_H

#define GAME_ROWS       21
#define GAME_COLS       GAME_ROWS
#define PERC_MINE       20 

/* Game status */
enum status {CONTINUE, RESTART, GAMEOVER};

/* Input actions for game update */
enum input {LEFT, RIGHT, DOWN, UP, FLAG, DISPLAY, EXPAND, NONE};

struct game {
  unsigned int rows;         
  unsigned int cols;         
	unsigned int flags;        
	unsigned int mines;        
	unsigned int displayed;    
	unsigned int cursor_row;   
	unsigned int cursor_col;   
	int board[GAME_ROWS][GAME_COLS]; 
};


/* 
 * Allocates the game data structure and returns a pointer to it.
 */
struct game *game_create(void);

/*
 * Initialize the game data structure.
 */
void game_init(struct game *G);

/*
 *  Destroys the game data structure.
 */
void game_destroy(struct game *G);

/*
 * Updates the game data structure and returns the current game state:
 * CONTINUE or GAMEOVER.
 */
enum status game_update(struct game *G, enum input input);

#endif
