#define BOARD_STUDENT
#ifdef BOARD_STUDENT
#include "board.h"
#include <time.h>
#include <stdlib.h>

#define HANDLE_START(x) !x ? x : x - 1
#define HANDLE_END(y, par2) (y == par2 - 1) ? y : y +1
/*
 * Verifica se le coordinate target si trovano nell'intorno 3x3 di check
 */
static int is_nearby(unsigned int target_x, unsigned int target_y, unsigned int check_x, unsigned int check_y);

/*
 * Verifica se le coordinate fanno parte della griglia
 */
static int is_in_grid(unsigned int x, unsigned int y);

/*
 * Verifica il numero di mine nell'intorno 3x3 di x,y
 */
static int mines_nearby(int board[][GAME_COLS], unsigned int x, unsigned int y);

/*
 * Rivela le caselle nell'intorno 3x3 di x,y
 */
static int display_around(int board[][GAME_COLS], unsigned int x, unsigned int y);

/*
 * Fills the rows*cols board with num_mines random mines
 * leaving free the neighborhood of position i,j
 */
void random_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j, unsigned int num_mines) {
    srand(time(NULL)); /* Inizializzazione del seed random */

    /* Vengono riempite tutte le celle con UNKN_FREE */
    unsigned int curr_row, curr_col;
    for (curr_row = 0; curr_row < rows; curr_row++) {
        for (curr_col = 0; curr_col < cols; curr_col++) {
            board[curr_row][curr_col] = UNKN_FREE;
        }
    }

    /* Vengono generate le mine */
    unsigned int mine_index;
    for(mine_index = 0; mine_index < num_mines; mine_index++) {
        unsigned int mine_x, mine_y;
        /* Vengono generate le coordinate da 0 a <grandezza griglia> */
        do {
            mine_x = rand() % GAME_COLS;
            mine_y = rand() % GAME_ROWS;
        } while (board[mine_x][mine_y] == UNKN_MINE || is_nearby(mine_x, mine_y, i, j));
        board[mine_x][mine_y] = UNKN_MINE;
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
    switch (board[i][j]) {
        case FLAG_FREE:
            board[i][j] = UNKN_FREE;
            return -1;
        case FLAG_MINE:
            board[i][j] = UNKN_MINE;
            return -1;
        case UNKN_FREE:
            board[i][j] = FLAG_FREE;
            return 1;
        case UNKN_MINE:
            board[i][j] = FLAG_MINE;
            return 1;
    }
    return 0;
}

/*
* Displays position i,j in the board. Returns the number of
* displayed cells or -1 if i,j contains a mine.
*/
int display_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {
    int y_end, x_end, y_start, x_start, n_mines, ret_val, x, y, cell_val;
    x_start = HANDLE_START(i);
    y_start = HANDLE_START(j);
    x_end = HANDLE_END(i, cols);
    y_end = HANDLE_END(j, rows);
    cell_val = board[i][j];
    if (cell_val == UNKN_FREE){
        n_mines = 0;
        for (x = x_start; x <= x_end; x++) {
            for (y = y_start; y <= y_end; y++){
                if (board[x][y] == UNKN_MINE || board[x][y] == FLAG_MINE) 
                    n_mines++;
            }
        }
        board[i][j] = n_mines;
        ret_val = 1;
        if (!n_mines) {
            for (x = x_start; x <= x_end; x++) {
                for (y = y_start; y <= y_end; y++){
                    if (x != i || y!= j) {
                        cell_val = display_board(board, rows, cols, x, y);
                        ret_val += cell_val;
                    }
                }
            }
        }
    }
    else {
        if (cell_val == UNKN_MINE){
            board[i][j] = MINE;
            ret_val = -1;
        }
        else {
            ret_val = 0;
        }
    }
    return ret_val;
}



/*
 * Expands all the free cells sourrounding  position i,j in
 * the board. Returns the number of expanded cells or -1 if
 * one contains a mine.
 */
int expand_board(int board[][GAME_COLS], unsigned int rows, unsigned int cols, unsigned int i, unsigned int j) {

    return 0;
}

static int is_nearby(unsigned int target_x, unsigned int target_y, unsigned int checkX, unsigned int check_y) {
    return ((target_x >= checkX - 1 && target_x <= checkX + 1) && (target_y >= check_y - 1 && target_y <= check_y + 1));
}

static int is_in_grid(unsigned int x, unsigned int y) {
    return x >= 0 && x < GAME_COLS && y >= 0 && y < GAME_ROWS;
}

static int mines_nearby(int board[][GAME_COLS], unsigned int x, unsigned int y) {
    int mines = 0;
    unsigned int i, j;
    for(j = y == 0 ? y : y - 1; j <= y + 1; j++) {
        for(i = x == 0 ? x : x - 1; i <= x + 1; i++) {
            if(is_in_grid(i, j)) {
                if(board[i][j] == UNKN_MINE || board[i][j] == MINE || board[i][j] == FLAG_MINE) mines++;
            }
        }
    }
    return mines;
}

static int display_around(int board[][GAME_COLS], unsigned int x, unsigned int y) {
    int count = 0; /* Posizioni svelate */
    unsigned int i, j;
    for(j = y == 0 ? y : y - 1; j <= y + 1; j++) {
        for(i = x == 0 ? x : x - 1; i <= x + 1; i++) {
            if(is_in_grid(i, j))
                if(board[i][j] != UNKN_MINE) count += display_board(board, GAME_ROWS, GAME_COLS, i, j);
        }
    }
    return count;
}

#endif
