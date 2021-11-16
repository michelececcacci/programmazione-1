#include "global.h"
#define GHOSTS_STUD
#ifdef GHOSTS_STUD

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ghosts.h"
#include "pacman.h"
#include "matrix.h"
#include "math.h"

#define UP   -1
#define DOWN  1
#define LEFT -1
#define RIGHT 1

typedef struct ghost {
    unsigned int id;
    int status;
    struct position pos;
} ghost;

struct arena {
    char **matrix;
    unsigned int rows;
    unsigned int columns;
};

struct ghosts {
    unsigned int num_ghosts;
    struct arena arena;
    ghost ghosts[];
};

static struct position convert_direction(char c);
static ghost *by_id(struct ghosts *G, unsigned int id);

static int can_move_hor(struct arena arena, ghost *ghost, int direction);
static int can_move_vert(struct arena arena, ghost *ghost, int direction);

/* Create the ghosts data structure */
struct ghosts *ghosts_setup(unsigned int num_ghosts) {
    struct ghosts *ghosts = malloc(sizeof(struct ghosts) + sizeof(ghost) * num_ghosts);
    ghosts->num_ghosts = num_ghosts;

    unsigned int i;
    for (i = 0; i < num_ghosts; i++) {
        struct position pos = {0, 0};
        ghost ghost = { i, NORMAL, pos};
        ghosts->ghosts[i] = ghost;
    }

    return ghosts;
}

/* Destroy the ghost data structure */
void ghosts_destroy(struct ghosts *G) {
    free(G);
}

/* Set the arena (A) matrix */
void ghosts_set_arena(struct ghosts *G, char **A, unsigned int nrow, 
                                                      unsigned int ncol) {
    struct arena arena = { A, nrow, ncol };
    G->arena = arena;
}

/* Set the position of the ghost id. */
void ghosts_set_position(struct ghosts *G, unsigned int id, struct position pos) {
    by_id(G, id)->pos = pos;
}

/* Set the status of the ghost id. */
void ghosts_set_status(struct ghosts *G, unsigned int id, enum ghost_status status) {
    by_id(G, id)->status = status;
}

/* Return the number of ghosts */
unsigned int ghosts_get_number(struct ghosts *G) {
    return G->num_ghosts;
}

/* Return the position of the ghost id. */
struct position ghosts_get_position(struct ghosts *G, unsigned int id) {
    return by_id(G, id)->pos;
}

/* Return the status of the ghost id. */
enum ghost_status ghosts_get_status(struct ghosts *G, unsigned int id) {
    return by_id(G, id)->status;
}

/* Move the ghost id (according to its status). Returns the new position */
struct position ghosts_move(struct ghosts *G, struct pacman *P, unsigned int id) {
    ghost *ghost = by_id(G, id);
    /* test **/
    /*if(can_move_hor(G->arena, ghost, RIGHT)) ghost->pos.i++;  */
    /* if(can_move_vert(G->arena, ghost, DOWN)) ghost->pos.j++; */

    if (ghost->status == NORMAL) {
    }
    else if (ghost->status == SCARED_NORMAL || ghost->status == SCARED_BLINKING) {

    }
    else if (ghost->status == EYES) {
        struct position home_pos = convert_direction(G->arena.matrix[ghost->pos.i][ghost->pos.j]);
        ghost->pos.i += home_pos.i;
        ghost->pos.j += home_pos.j;
        /* 
        FILE *fp;
        fp = fopen("eyes.log", "a");
        fprintf(fp, "Position x: %d, position y: %d\n", ghost->pos.i, ghost->pos.j);
        fclose(fp);
        */
    }
}

static ghost *by_id(struct ghosts *G, unsigned int id) {
    unsigned int i;
    for(i = 0; i < G->num_ghosts; i++) {
        if(G->ghosts[i].id == id) return &G->ghosts[i];
    }
    return NULL;
}

static int can_move_hor(struct arena arena, ghost *ghost, int direction) {
    return arena.matrix[ghost->pos.i + direction][ghost->pos.j] == XWALL_SYM;
}

static int can_move_vert(struct arena arena, ghost *ghost, int direction) {
    return arena.matrix[ghost->pos.i][ghost->pos.j + direction] == XWALL_SYM;
}


static float  distance(struct position pos1, struct position pos2){
    float distance_x =  (pos1.i - pos2.i) * (pos1.i - pos2. i);
    float distance_y  = (pos1.j - pos2.j) * (pos1.j - pos2.j);
    return sqrt(distance_x + distance_y);

}

static struct position convert_direction(char c){
    struct position path_pos;
    switch (c) {
        case UP_SYM:
            path_pos.i = UP;
            break;
        case DOWN_SYM:
            path_pos.i = DOWN;
            break;
        case LEFT_SYM:
            path_pos.j = LEFT;
            break;
        case RIGHT_SYM:
            path_pos.j = RIGHT;
            break;
    }
    return path_pos;
}

#endif


