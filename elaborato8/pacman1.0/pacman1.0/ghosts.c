#ifndef GHOSTS_H
#define GHOSTS_H

#include "global.h"
#include "pacman.h"
#include <stdlib.h>

static const struct position UNK_POSITION = {-1,-1}; 
struct ghosts {
    char **A;
    unsigned int nrow;
    unsigned int ncol;
    struct ghost* ghosts_arr;
    int num_ghosts;
}; 
struct ghost {
    struct position pos;
    enum direction dir;
    int id;
    int status;
};

/* Create the ghosts data structure */
struct ghosts *ghosts_setup(unsigned int num_ghosts){
    struct ghosts *G  = (struct ghosts *) calloc(1, sizeof(struct ghosts) + sizeof(struct ghost) * num_ghosts);
    G->A = NULL;
    G->nrow = 0;
    G->ncol = 0;
    G->num_ghosts = num_ghosts;
    int i ;
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
    if (G != NULL){
        G->ghosts_arr[id].pos = pos;
    }
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
    struct position new_position = {-1, -1};
    return (G != NULL) ? G->ghosts_arr[id].pos : new_position;
}

/* Move the ghost id ( according to its status ). Returns the new position */
struct position ghosts_move(struct ghosts *G , struct pacman *P , unsigned int id ){
    return UNK_POSITION;
}

/* Return the status of the ghost id . */
enum ghost_status ghosts_get_status(struct ghosts *G , unsigned int id){
    return (G != NULL) ? G->ghosts_arr[id].status : UNK_GHOST_STATUS;
}

/* returns the new position of the ghost based on its direction */
static struct position new_position(struct position pos, enum direction dir, unsigned int nrow, unsigned int ncol);



#endif