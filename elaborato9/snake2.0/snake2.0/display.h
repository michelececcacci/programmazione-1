#ifndef DISPLAY_H
#define DISPLAY_H

#include "world.h"

#define STARTING_TIMEOUT  250
#define MINIMUM_TIMEOUT   100

#define SNAKE_SYMBOL       '@'
#define GOOD_FOOD_SYMBOL   ACS_DIAMOND
#define BAD_FOOD_SYMBOL    ACS_DEGREE
#define CREEPY_FOOD_SYMBOL ACS_BOARD

/*
 * Gets the display's number of rows and columns
 */
void display_width(int *max_row, int *max_col);

/*
 * Opens the graphical display.
 */
void display_open(void);

/*
 * Closes the graphical display.
 */
void display_close(void);

/*
 * Plots the current world into the graphical display.
 */
void display_plot(struct world *W);

/*
 * Plots the final world into the graphical display.
 * Returns 1 to restart the game.
 */
int display_gameover(struct world *W);

/*
 * Gets the next input from keyboard. It can directly close the game.
 */
enum direction display_input(struct world *W, enum direction dir);

#endif
