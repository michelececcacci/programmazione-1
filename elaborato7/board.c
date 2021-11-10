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
static void display_around(int board[][GAME_COLS], unsigned int x, unsigned int y);

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
    unsigned int mineIndex;
    for(mineIndex = 0; mineIndex <= num_mines; mineIndex++) {
        unsigned int mineX, mineY;
        /* Vengono generate le coordinate da 0 a <grandezza griglia> */
        do {
            mineX = rand() % GAME_COLS;
            mineY = rand() % GAME_ROWS;
        } while (board[mineX][mineY] == UNKN_MINE || is_nearby(mineX, mineY, i, j));
        board[mineX][mineY] = UNKN_MINE;
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
    switch (board[i][j]) {
        case UNKN_MINE:
        case MINE:
            board[i][j] = MINE;
            return -1;
        case UNKN_FREE: {
            int mines = mines_nearby(board, i, j);
            board[i][j] = mines;
            if(mines == C0) {
                display_around(board, i, j);
            }
            return 1;
        }
    }
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

static int is_in_grid(unsigned int x, unsigned int y) {
    return x >= 0 && x < GAME_COLS && y >= 0 && y < GAME_ROWS;
}

static int mines_nearby(int board[][GAME_COLS], unsigned int x, unsigned int y) {
    int mines = 0;
    unsigned int i, j;
    for(j = y == 0 ? y : y - 1; j <= y + 1; j++) {
        for(i = x == 0 ? x : x - 1; i <= x + 1; i++) {
            if(is_in_grid(i, j)) {
                if(board[i][j] == UNKN_MINE || board[i][j] == MINE) mines++;
            }
        }
    }
    return mines;
}

static void display_around(int board[][GAME_COLS], unsigned int x, unsigned int y) {
    unsigned int i, j;
    for(j = y == 0 ? y : y - 1; j <= y + 1; j++) {
        for(i = x == 0 ? x : x - 1; i <= x + 1; i++) {
            if(is_in_grid(i, j))
                if(board[i][j] != UNKN_MINE) display_board(board, GAME_ROWS, GAME_COLS, i, j);
        }
    }
}

#endif
