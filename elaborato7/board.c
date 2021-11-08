#define BOARD_STUDENT
#ifdef BOARD_STUDENT
#include "board.h"
#include <time.h>
#include <stdlib.h>


/*
 * Fills the rows*cols board with num_mines random mines
 * leaving free the neighborhood of position i,j
 */
void random_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j, unsigned int num_mines) {
    srand(time(NULL));   /* Initialization, should only be called once. */
    int curr_row, curr_col, count = 0;
    for (curr_row  = 0; curr_row < rows; curr_row++){
        for (curr_col = 0; curr_col < cols; curr_col++){
            /* second condition is basically to detect the condition of being around in the point i, j (where i is considered as column)*/
            if (count >= num_mines || (curr_col == i || curr_col == i + 1 || curr_col == i - 1) && (curr_row == j || curr_row == j + 1 ||curr_row == j - 1)) {
                board[curr_row][curr_col] = UNKN_FREE;
            }
            else {
                if (rand() % 2) {
                    board[curr_row][curr_col] = UNKN_MINE;
                    count++;
                }
                else 
                    board[curr_row][curr_col] = UNKN_FREE;
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

#endif
