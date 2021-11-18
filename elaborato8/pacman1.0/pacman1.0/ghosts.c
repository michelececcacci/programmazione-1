#include "global.h"

#define GHOSTS_STUD
#ifdef GHOSTS_STUD
#define LOGGING

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

#define MIN_4(a, b, c, d) (MIN_2(MIN_2(a, b), MIN_2(c, d)))
#define MIN_2(a, b) (a) > (b) ? (a) : (b)

typedef struct ghost {
    unsigned int id;
    int status;
    struct position pos;
    struct position dir;
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

/*
 * Ottiene un fantasma da un ID.
 */
static ghost *by_id(struct ghosts *G, unsigned int id);

/*
 * Controlla se una posizione è libera da muri o fantasmi.
 */
static int is_free(struct position pos, struct ghosts *G);

/*
 * Controlla se il fantasma può muoversi dalla sua posizione verso un determinato offset.
 */
static int can_move_offs(struct ghosts *G, ghost *ghost, unsigned int offsetX, unsigned int offsetY);

/*
 * Controlla se il fantasma può muoversi dalla sua posizione verso la sua direzione.
 */
static int can_move_dir(struct ghosts *G, ghost *ghost);

/*
 * Controlla se il fantasma può muoversi lateralmente rispetto alla sua direzione.
 */
static int can_move_side(struct ghosts *G, ghost *ghost);

/*
 * Calcola la distanza tra due posizioni.
 */
static double distance(struct position pos1, struct position pos2);

/*
 * Trova la possibile direzione più vicina verso pacman.
 */
static struct position closest_direction(struct ghosts *G, struct pacman *P, ghost *ghost);

/* Create the ghosts data structure */
struct ghosts *ghosts_setup(unsigned int num_ghosts) {
    struct ghosts *ghosts = malloc(sizeof(struct ghosts) + sizeof(ghost) * num_ghosts);
    ghosts->num_ghosts = num_ghosts;

    unsigned int i;
    for (i = 0; i < num_ghosts; i++) {
        struct position pos = {0, 0};
        struct position dir = {0, 0};
        ghost ghost = {i, NORMAL, pos, dir};
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
    struct arena arena = {A, nrow, ncol};
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

    if (ghost->status == NORMAL) {
        if((!ghost->dir.i && !ghost->dir.j) || !can_move_dir(G, ghost)) {
            ghost->dir = closest_direction(G, P, ghost);
        } else if(can_move_side(G, ghost)) {
            /*
             * La direzione può essere aggiornata se il fantasma si trova ad un "incrocio"
             * per avere un movimento laterale (e non all'indietro)
             */
            struct position new_dir = closest_direction(G, P, ghost);
            if(ghost->dir.i != -new_dir.i && ghost->dir.j != -new_dir.j) {
                ghost->dir = new_dir;
            }
        }
        ghost->pos.i += ghost->dir.i;
        ghost->pos.j += ghost->dir.j;
        /* should try to find the move that brings the ghost closest to pacman */
        #ifdef LOGGING
        FILE *fp;
        fp = fopen("normal.log", "a");
        fprintf(fp, "Position x: %d, position y: %d, ghost id: %d\n", ghost->pos.i, ghost->pos.j, ghost->id);
        fclose(fp);
        #endif
    } else if (ghost->status == SCARED_NORMAL || ghost->status == SCARED_BLINKING) {
        /* same thing as before, but should bring further */

    } else if (ghost->status == EYES) {
        /* seems to work decently even though it's not pretty at all. Edge case handling not needed*/
        char c = G->arena.matrix[ghost->pos.j][ghost->pos.i];
        switch (c) {
            case UP_SYM:
                ghost->pos.j += UP;
                break;
            case DOWN_SYM:
                ghost->pos.j += DOWN;
                break;
            case LEFT_SYM:
                ghost->pos.i += LEFT;
                break;
            case RIGHT_SYM:
                ghost->pos.i += RIGHT;
                break;
        }
        #ifdef LOGGING
        FILE *fp;
        fp = fopen("eyes.log", "a");
        fprintf(fp, "Position x: %d, position y: %d, ghost id: %d\n", ghost->pos.i, ghost->pos.j, ghost->id);
        fclose(fp);
        #endif
    }
}

static ghost *by_id(struct ghosts *G, unsigned int id) {
    return &G->ghosts[id];
}

static int can_move_offs(struct ghosts *G, ghost *ghost, unsigned int offsetX, unsigned int offsetY) {
    struct position pos = {ghost->pos.i + offsetX, ghost->pos.j + offsetY};
    return is_free(pos, G);
}

static int can_move_dir(struct ghosts *G, ghost *ghost) {
    return can_move_offs(G, ghost, ghost->dir.i, ghost->dir.j);
}

static int can_move_side(struct ghosts *G, ghost *ghost) {
    if(ghost->dir.i) {
        return can_move_offs(G, ghost, 0, UP) || can_move_offs(G, ghost, 0, DOWN);
    } else if(ghost->dir.j) {
        return can_move_offs(G, ghost, RIGHT, 0) || can_move_offs(G, ghost, LEFT, 0);
    }
}

static int is_free(struct position pos, struct ghosts *G) {
    if(G->arena.matrix[pos.i][pos.j] == XWALL_SYM) return 0;

    unsigned int i;
    for (i = 0; i < G->num_ghosts; i++) {
        ghost ghost = G->ghosts[i];
        if (ghost.pos.i == pos.i && ghost.pos.j == pos.j) return 0;
    }
    return 1;
}

static double distance(struct position pos1, struct position pos2) {
    unsigned int distance_x = (pos1.i - pos2.i) * (pos1.i - pos2.i);
    unsigned int distance_y = (pos1.j - pos2.j) * (pos1.j - pos2.j);
    return sqrt(distance_x + distance_y);
}

static struct position closest_direction(struct ghosts *G, struct pacman *P, ghost *ghost) {
    struct position pacman_pos = pacman_get_position(P);
    struct position ghost_pos = ghost->pos;
    struct position ghost_dir = ghost->dir;

    /* Posizione clonata */
    struct position new = { ghost_pos.i, ghost_pos.j };

    double dis_x = -1;
    double dis_y = -1;

    int dir_x = 0;
    int dir_y = 0;

    /*
     * !ghost_dir.i/j permette di alternare movimenti verticali ad orizzontali
     * per evitare situazioni di stallo.
     */

    if(can_move_offs(G, ghost, LEFT, 0) && !ghost_dir.i) {
        new.i += LEFT;
        dis_x = distance(pacman_pos, new);
        dir_x = LEFT;
        new.i -= LEFT;
    }
    if(can_move_offs(G, ghost, RIGHT, 0) && !ghost_dir.i) {
        new.i += RIGHT;
        double right_distance = distance(pacman_pos, new);
        if(dis_x < 0 || dis_x > right_distance) {
            dis_x = right_distance;
            dir_x = RIGHT;
        }
        new.i -= RIGHT;
    }
    if(can_move_offs(G, ghost, 0, UP) && !ghost_dir.j) {
        new.j += UP;
        dis_y = distance(pacman_pos, new);
        dir_y = UP;
        new.j -= UP;
    }
    if(can_move_offs(G, ghost, 0, DOWN) && !ghost_dir.j) {
        new.j += DOWN;
        double down_distance = distance(pacman_pos, new);
        if(dis_y < 0 || dis_y > down_distance) {
            dis_y = down_distance;
            dir_y = DOWN;
        }
        new.j += DOWN;
    }

    struct position direction = { dis_x >= dis_y ? dir_x : 0, dis_y > dis_x ? dir_y : 0 };
    return direction;
}

#endif


