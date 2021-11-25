#ifndef GHOSTS_H
#define GHOSTS_H

#include "global.h"
#include "pacman.h"
#include <stdlib.h>
#include <stdio.h>
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

/* Returns 1 if the position is in the arena */
static int is_in_arena(struct position pos, struct ghosts *G);

/* Distance between 2 positions */
static double distance(struct position pos1, struct position pos2) ;

/* Direction that has the smallest possible distance from a position */
static enum direction closest_direction(struct position old_pos, struct ghosts *G, struct pacman *P, struct ghost *ghost);

/* Direction that has the biggest possible distance from a position */
static enum direction furthest_direction(struct position old_pos, struct ghosts *G, struct pacman *P, struct ghost *ghost);


static int can_move_dir(struct position pos, enum direction dir);

struct position ghosts_move(struct ghosts *G , struct pacman *P , unsigned int id ){
    struct ghost *g = &G->ghosts_arr[id];
    if (g->status == NORMAL){
        g->dir = closest_direction(g->pos, G, P, g);   /* should minimize distance */
        g->pos = new_position(g->pos, g->dir, G->nrow, G->ncol);
    }
    else if (g->status == EYES){
        char c = G->A[g->pos.i][g->pos.j];
        struct position eyes_pos = g->pos;
        switch (c) {
            case UP_SYM:
                eyes_pos.i--;
                break;
            case DOWN_SYM:
                eyes_pos.i++;
                break;
            case LEFT_SYM:
                eyes_pos.j--;
                break;
            case RIGHT_SYM:
                eyes_pos.j++;
                break;
        } 
        /* todo find a decent way to implement eyes*/
        #ifdef LOGGING
        FILE *fp;
        fp = fopen("eyes.log", "a");
        fprintf(fp ,"symbol: %c\n", c);
        fclose(fp);
        #endif
        if (is_free_other(eyes_pos, G, P)) {
            g->dir = closest_direction(g->pos, G, P, g);   /* should maximize distance */
            g->pos = new_position(g->pos, g->dir, G->nrow, G->ncol);
        }
    }
    else {

    g->pos = new_position(g->pos, g->dir, G->nrow, G->ncol);
    }
    return g->pos;
}


static int is_in_arena(struct position pos, struct ghosts *G){
    return (pos.i < G->ncol + 1 && pos.j < G->nrow);
}
static struct position new_position(struct position pos, enum direction dir, unsigned int nrow, unsigned int ncol) {
	struct position new = pos;
	switch (dir) {
		case LEFT:  new.j = (pos.j+(ncol-1)) % ncol; break;
		case RIGHT: new.j = (pos.j+1)        % ncol; break;
		case UP:    new.i = (pos.i+(nrow-1)) % nrow; break;
		case DOWN:  new.i = (pos.i+1)        % nrow; break;
		case UNK_DIRECTION: break;
	}
	return new;
}

static int is_free(struct position pos, struct ghosts *G, struct pacman *P) {
    int i;
    char mat_val = G->A[pos.i][pos.j];
    if (mat_val == XWALL_SYM)  
        return 0;
    for (i = 0; i < G->num_ghosts; i++) {
        if ((pos.i == G->ghosts_arr[i].pos.i) && (pos.j == G->ghosts_arr[i].pos.j)) 
            return 0;
    }
    return 1;
}


static int is_free_other(struct position pos, struct ghosts *G, struct pacman *P){
    struct position pacman_pos = pacman_get_position(P);
    if (pos.i == pacman_pos.i && pos.j == pacman_pos.j)
        return 0;
    return is_free(pos, G, P);
}

static enum direction closest_direction(struct position old_pos, struct ghosts *G, struct pacman *P, struct ghost *ghost){
        struct position pacman_pos = pacman_get_position(P);
        struct position up_pos = old_pos, down_pos = old_pos, left_pos = old_pos, right_pos = old_pos;
        float left_dis = 1000, right_dis = 1000, up_dis = 1000, down_dis = 1000, best_dis = 1000;
        up_pos.i--;
        down_pos.i++;
        left_pos.j--;
        right_pos.j++;
        if (is_in_arena(up_pos, G) && is_free(up_pos, G, P)) {
            up_dis = distance(up_pos, pacman_pos);
        }
        if (is_in_arena(down_pos, G) && is_free(down_pos, G, P)) {
            down_dis = distance(down_pos, pacman_pos);
        }
        
        if (is_in_arena(left_pos, G) && is_free(left_pos, G, P)) {
            left_dis = distance(left_pos, pacman_pos);
        }
        if (is_in_arena(right_pos, G) && is_free(right_pos, G, P)) {
            right_dis = distance(right_pos, pacman_pos);
        }
        best_dis = MIN_4(up_dis, down_dis, left_dis, right_dis);
        #ifdef LOGGING
        FILE *fp;
        fp = fopen("closest_position.log", "a");
        fprintf(fp, "up: %f, down: %f, left: %f, right: %f, best: %f\n", up_dis, down_dis, left_dis, right_dis,  best_dis);
        fclose(fp);
        #endif
        if (best_dis == right_dis) return RIGHT;
        else if (best_dis == up_dis) return UP;
        else if (best_dis == down_dis) return DOWN;
        else if (best_dis == left_dis) return LEFT;
        else return UNK_DIRECTION;
}

/* not working idk why */
enum direction furthest_direction(struct position old_pos, struct ghosts *G, struct pacman *P, struct ghost *ghost){
    struct position pacman_pos = pacman_get_position(P);
    struct position up_pos = old_pos, down_pos = old_pos, left_pos = old_pos, right_pos = old_pos;
    float left_dis = 0, right_dis = 0, up_dis = 0, down_dis = 0, best_dis = 0;
    up_pos.i--;
    down_pos.i++;
    left_pos.j--;
    right_pos.j++;
    if (is_in_arena(up_pos, G) && is_free_other(up_pos, G, P)) {
        up_dis = distance(up_pos, pacman_pos);
    }
    if (is_in_arena(down_pos, G) && is_free_other(down_pos, G, P)) {
        down_dis = distance(down_pos, pacman_pos);
    }
    
    if (is_in_arena(left_pos, G) && is_free_other(left_pos, G, P)) {
        left_dis = distance(left_pos, pacman_pos);
    }
    if (is_in_arena(right_pos, G) && is_free_other(right_pos, G, P)) {
        right_dis = distance(right_pos, pacman_pos);
    }
    best_dis = MAX_4(up_dis, down_dis, left_dis, right_dis);
    #ifdef LOGGING
    FILE *fp;
    fp = fopen("furthest_position.log", "a");
    fprintf(fp, "up: %f, down: %f, left: %f, right: %f, best: %f\n", up_dis, down_dis, left_dis, right_dis,  best_dis);
    fclose(fp);
    #endif
    if (best_dis == right_dis) return RIGHT;
    else if (best_dis == up_dis) return UP;
    else if (best_dis == down_dis) return DOWN;
    else if (best_dis == left_dis) return LEFT;
    else return UNK_DIRECTION;
}

static double distance(struct position pos1, struct position pos2) {
    unsigned int distance_x = (pos1.i - pos2.i) * (pos1.i - pos2.i);
    unsigned int distance_y = (pos1.j - pos2.j) * (pos1.j - pos2.j);
    return sqrt(distance_x + distance_y);
}

#endif