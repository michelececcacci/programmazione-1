#ifndef WORLD_H
#define WORLD_H

#include "snake.h"

enum status {GAMEOVER, CONTINUE};
enum cell   {EMPTY, GOOD_FOOD, BAD_FOOD, CREEPY_FOOD};

struct world {
  unsigned int rows;         
  unsigned int cols;         
  unsigned int snake_length; 
  struct snake *snake;
  enum cell **board;         
};

/*
 * Creates a rows*cols world matrix with random food_amount bad and
 * good resources.
 * 
 * A snake of length 1 is positioned approximatively in the middle of the
 * world matrix;
 */
struct world *world_create(unsigned int rows, unsigned int cols, unsigned int food_amount);


/*
 * Deallocates the world structure.
 */
void world_destroy(struct world *W);


/*
 * Updates the world by moving the snake one step forward in dir direction.
 *
 * Returns the status of the game: continue or game over.
 */
enum status world_update(struct world *W, enum direction *dir);

#endif
