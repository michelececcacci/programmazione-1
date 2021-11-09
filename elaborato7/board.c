#define BOARD_STUDENT
#ifdef BOARD_STUDENT
#include "board.h"
#include <time.h>
#include <stdlib.h>

/*
 * Verifica se le coordinate target si trovano nell'intorno 3x3 di check
 */
static int is_nearby(unsigned int targetX, unsigned int targetY, unsigned int checkX, unsigned int checkY);

/*
 * Un boolean random 0/1
 */
static int rand_bool();

/*
 * Fills the rows*cols board with num_mines random mines
 * leaving free the neighborhood of position i,j
 */
void random_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j, unsigned int num_mines) {
    srand(time(NULL)); /* Inizializzazione del seed random */
    unsigned int curr_row, curr_col, count = 0;
    for (curr_row  = 0; curr_row < rows; curr_row++){
        for (curr_col = 0; curr_col < cols; curr_col++){
            if ((count >= num_mines || is_nearby(curr_row, curr_col, i, j)) && !rand_bool()) {
                board[curr_row][curr_col] = UNKN_FREE;
            } else {
                board[curr_row][curr_col] = UNKN_MINE;
                count++;
            }
        }
    }
}




/*
* Flags/unflags the i,j position in the board. Returns
* - -1 if the position was flagged. Removes the flag
* -  0 if the position is already displyed
* -  1 if the position is not flagged and not already
*    displayed. Puts a flag in position i,j.
*/
int flag_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {
    return 0;
    
}

/*
* Displays position i,j in the board. Returns the number of
* displayed cells or -1 if i,j contains a mine.
*/

int display_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {

    return 0;
}



/*
 * Expands all the free cells sourrounding  position i,j in
 * the board. Returns the number of expanded cells or -1 if
 * one contains a mine.
 */
int expand_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {

    return 0;
}

static int is_nearby(unsigned int targetX, unsigned int targetY, unsigned int checkX, unsigned int checkY) {
    return ((targetX >= checkX - 1 && targetX <= checkX + 1) && (targetY >= checkY - 1 && targetY <= checkY + 1));
}

static int rand_bool() {
    return rand() % 2;
}

#endif
