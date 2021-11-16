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

#define MIN_4(a, b, c, d) (MIN_2(MIN_2(a, b), MIN_2(c, d)))
#define MIN_2(a, b) (a) > (b) ? (a) : (b)

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

static ghost *by_id(struct ghosts *G, unsigned int id);

static int can_move_hor(struct arena arena, ghost *ghost, int direction);

static int can_move_vert(struct arena arena, ghost *ghost, int direction);

static float distance(struct position pos1, struct position pos2);

static struct position closest_direction(struct arena arena, struct pacman *P, ghost *ghost);

/* Create the ghosts data structure */
struct ghosts *ghosts_setup(unsigned int num_ghosts) {
    struct ghosts *ghosts = malloc(sizeof(struct ghosts) + sizeof(ghost) * num_ghosts);
    ghosts->num_ghosts = num_ghosts;

    unsigned int i;
    for (i = 0; i < num_ghosts; i++) {
        struct position pos = {0, 0};
        ghost ghost = {i, NORMAL, pos};
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
        struct position direction = closest_direction(G->arena, P, ghost);
        ghost->pos.i += direction.i;
        ghost->pos.j += direction.j;
        /* should try to find the move that brings the ghost closest to pacman */
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
    for (i = 0; i < G->num_ghosts; i++) {
        if (G->ghosts[i].id == id) return &G->ghosts[i];
    }
    return NULL;
}

static int can_move_hor(struct arena arena, ghost *ghost, int direction) {
    return arena.matrix[ghost->pos.i + direction][ghost->pos.j] == XWALL_SYM;
}

static int can_move_vert(struct arena arena, ghost *ghost, int direction) {
    return arena.matrix[ghost->pos.i][ghost->pos.j + direction] == XWALL_SYM;
}

static float distance(struct position pos1, struct position pos2) {
    float distance_x = (float) ((pos1.i - pos2.i) * (pos1.i - pos2.i));
    float distance_y = (float) ((pos1.j - pos2.j) * (pos1.j - pos2.j));
    return sqrtf(distance_x + distance_y);
}

static struct position closest_direction(struct arena arena, struct pacman *P, ghost *ghost) {
    struct position pacman_pos = pacman_get_position(P);
    struct position ghost_pos = ghost->pos;

    struct position new = { ghost_pos.i, ghost_pos.j };

    float dis_x = 0;
    float dis_y = 0;

    int dir_x = 0;
    int dir_y = 0;

    if(can_move_hor(arena, ghost, LEFT)) {
        new.i += LEFT;
        dis_x = distance(pacman_pos, new);
        dir_x = LEFT;
        new.i -= LEFT;
    }
    if(can_move_hor(arena, ghost, RIGHT)) {
        new.i += RIGHT;
        float right_distance = distance(pacman_pos, new);
        if(dis_x > right_distance) {
            dis_x = right_distance;
            dir_x = RIGHT;
        }
        new.i -= RIGHT;
    }
    if(can_move_vert(arena, ghost, UP)) {
        new.j += UP;
        dis_y = distance(pacman_pos, new);
        dir_y = UP;
        new.j -= UP;
    }
    if(can_move_vert(arena, ghost, DOWN)) {
        new.j += DOWN;
        float down_distance = distance(pacman_pos, new);
        if(dis_y > down_distance) {
            dis_y = down_distance;
            dir_y = DOWN;
        }
        new.j += DOWN;
    }

    struct position direction = { dir_x, dir_y };
    return direction;
}

#endif


