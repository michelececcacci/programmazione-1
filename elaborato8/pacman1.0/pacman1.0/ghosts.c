#ifndef GHOSTS_H
#define GHOSTS_H

#include "global.h"
#include "pacman.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
 
#define LOGGING

#define MIN_4(a, b, c, d) (MIN_2(MIN_2(a, b), MIN_2(c, d)))
#define MIN_2(a, b) (a) < (b) ? (a) : (b)
#define MAX_2(a, b) (a) > (b) ? (a) : (b)
#define MAX_4(a, b, c, d) (MAX_2(MAX_2(a, b), MAX_2(c, d)))
static const struct position UNK_POSITION = {-1,-1}; 

struct ghost {
    struct position pos;
    enum direction dir;
    int id;
    enum ghost_status status;
};


struct ghosts {
    char **A;
    unsigned int nrow;
    unsigned int ncol;
    int num_ghosts;
    struct ghost ghosts_arr[];
}; 

/* Create the ghosts data structure */
struct ghosts *ghosts_setup(unsigned int num_ghosts){
    srand(time(NULL));
    struct ghosts *G  = (struct ghosts *) malloc(sizeof(struct ghosts) + sizeof(struct ghost) * num_ghosts);
    G->A = NULL;
    G->nrow = 0;
    G->ncol = 0;
    G->num_ghosts = num_ghosts;
    int i;
    for (i = 0; i < num_ghosts; i++) {
        struct ghost new_ghost = {UNK_POSITION, UNK_DIRECTION, i, UNK_GHOST_STATUS};
        G->ghosts_arr[i] = new_ghost;
    }
    return G;
}

/* Destroy the ghost data structure */
void ghosts_destroy(struct ghosts * G){
    free(G);
}

/* Set the arena ( A ) matrix */
void ghosts_set_arena(struct ghosts *G , char ** A , unsigned int nrow , unsigned int ncol) {
    if (G != NULL) {
        G->A = A;
        G->nrow = nrow;
        G->ncol = ncol;
    }
}

/* Set the position of the ghost id . */
void ghosts_set_position(struct ghosts *G , unsigned int id , struct position pos) {
    if (G != NULL) G->ghosts_arr[id].pos = pos;
}

/* Set the status of the ghost id . */
void ghosts_set_status(struct ghosts *G , unsigned int id , enum ghost_status status) {
    if (G != NULL) G->ghosts_arr[id].status = status;
}

/* Return the number of ghosts */
unsigned int ghosts_get_number(struct ghosts * G) {
    return G->num_ghosts;
}

/* Return the position of the ghost id . */
struct position ghosts_get_position(struct ghosts *G , unsigned int id){
    return (G != NULL) ? G->ghosts_arr[id].pos : UNK_POSITION;
}

/* returns the new position of the ghost based on its direction */
static struct position new_position(struct position pos, enum direction dir, unsigned int nrow, unsigned int ncol);
/* Move the ghost id ( according to its status ). Returns the new position */

static int is_free(struct position pos, struct ghosts *G, struct pacman *P);

static int is_free_other(struct position pos, struct ghosts *G, struct pacman *P);

/* Return the status of the ghost id . */
enum ghost_status ghosts_get_status(struct ghosts *G , unsigned int id){
    return (G != NULL) ? G->ghosts_arr[id].status : UNK_GHOST_STATUS;
}


static enum direction eyes_suggested_direction(char c);

struct position ghosts_move(struct ghosts *G , struct pacman *P , unsigned int id ){
    struct ghost *g = &G->ghosts_arr[id];
    if (g->status == NORMAL){
        struct position dir_pos = new_position(g->pos, g->dir, G->nrow, G->ncol);
        if (!is_free(g->pos, G, P)){
            struct position left_pos = new_position(g->pos, LEFT, G->nrow, G->ncol), 
            right_pos = new_position(g->pos, RIGHT, G->nrow, G->ncol), 
            up_pos= new_position(g->pos, UP, G->nrow, G->ncol), 
            down_pos= new_position(g->pos, DOWN, G->nrow, G->ncol);
            if (is_free(left_pos, G, P)) g->dir = LEFT;
            else if (is_free(right_pos, G, P)) g->dir = RIGHT;
            else if (is_free(up_pos, G, P)) g->dir = UP;
            else if (is_free(down_pos, G, P)) g->dir = DOWN;
            else   g->dir = UNK_DIRECTION;
        }
        g->pos = new_position(g->pos, g->dir, G->nrow, G->ncol);
   }
    else if (g->status == EYES){
        struct position eyes_pos = g->pos;
        char c = G->A[g->pos.i][g->pos.j];
        g->dir = eyes_suggested_direction(c);
        #ifdef LOGGING
        FILE *fp;
        fp = fopen("eyes.log", "a");
        fprintf(fp ,"symbol: %c\n", c);
        fclose(fp);
        #endif
        eyes_pos = new_position(g->pos, g->dir, G->nrow, G->ncol);
        if (!is_free_other(eyes_pos, G, P)){
            struct position left_pos = new_position(g->pos, LEFT, G->nrow, G->ncol), 
            right_pos = new_position(g->pos, RIGHT, G->nrow, G->ncol), 
            up_pos= new_position(g->pos, UP, G->nrow, G->ncol), 
            down_pos= new_position(g->pos, DOWN, G->nrow, G->ncol);
            if (is_free_other(left_pos, G, P)) g->dir = LEFT;
            else if (is_free_other(right_pos, G, P)) g->dir = RIGHT;
            else if (is_free_other(up_pos, G, P)) g->dir = UP;
            else if (is_free_other(down_pos, G, P)) g->dir = DOWN;
            else   g->dir = UNK_DIRECTION;
        }
        g->pos = new_position(g->pos, g->dir, G->nrow, G->ncol);
    }
    else {
        struct position dir_pos = new_position(g->pos, g->dir, G->nrow, G->ncol);
        if (!is_free_other(g->pos, G, P)){
            struct position left_pos = new_position(g->pos, LEFT, G->nrow, G->ncol), 
            right_pos = new_position(g->pos, RIGHT, G->nrow, G->ncol), 
            up_pos= new_position(g->pos, UP, G->nrow, G->ncol), 
            down_pos= new_position(g->pos, DOWN, G->nrow, G->ncol);
            if (is_free_other(left_pos, G, P)) g->dir = LEFT;
            else if (is_free_other(right_pos, G, P)) g->dir = RIGHT;
            else if (is_free_other(up_pos, G, P)) g->dir = UP;
            else if (is_free_other(down_pos, G, P)) g->dir = DOWN;
            else   g->dir = UNK_DIRECTION;
        }
        g->pos = new_position(g->pos, g->dir, G->nrow, G->ncol);
    }


    return g->pos;
}



static struct position new_position(struct position pos, enum direction dir, unsigned int nrow, unsigned int ncol) {
	struct position new = pos;
    if (dir == LEFT)  new.j = (pos.j+(ncol-1)) % ncol; 
    else if (dir == RIGHT) new.j = (pos.j+1) % ncol; 
    else if (dir == UP) new.i = (pos.i+(nrow-1)) % nrow; 
	else if (dir == DOWN)  new.i = (pos.i+1) % nrow; 
	return new;
}

static int is_free(struct position pos, struct ghosts *G, struct pacman *P) {
    int i;
    for (i = 0; i < G->num_ghosts; i++) {
        if ((pos.i == G->ghosts_arr[i].pos.i) && (pos.j == G->ghosts_arr[i].pos.j)) 
            return 0;
    }
    return !IS_WALL(G->A, pos);
}


static int is_free_other(struct position pos, struct ghosts *G, struct pacman *P){
    struct position pacman_pos = pacman_get_position(P);
    if (pos.i == pacman_pos.i && pos.j == pacman_pos.j)
        return 0;
    return is_free(pos, G, P);
}


static enum direction eyes_suggested_direction(char c){
    switch (c) {
            case UP_SYM:
            return UP;
                break;
            case DOWN_SYM:
            return  DOWN;
                break;
            case LEFT_SYM:
            return  LEFT;
                break;
            case RIGHT_SYM:
            return RIGHT;
        }
    return UNK_DIRECTION;
}

#endif