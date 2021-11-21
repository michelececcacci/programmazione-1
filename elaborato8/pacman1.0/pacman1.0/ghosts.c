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
#define MIN_2(a, b) (a) < (b) ? (a) : (b)
#define MAX_2(a, b) (a) > (b) ? (a) : (b)
#define MAX_4(a, b, c, d) (MAX_2(MAX_2(a, b), MAX_2(c, d)))

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

/* Ottiene un fantasma da un ID.*/
static ghost *by_id(struct ghosts *G, unsigned int id);

/* Calcola la distanza tra due posizioni. */
static double distance(struct position pos1, struct position pos2);

/* Una probabilità di poco inferiore al 50%. */
static int rand_bool();

/* new version */
static int is_free(struct position pos, struct ghosts *G, struct pacman *P);

static int is_free_other(struct position pos, struct ghosts *G, struct pacman *P);

static int is_in_arena(struct position pos, struct ghosts *G);

/* Create the ghosts data structure */
struct ghosts *ghosts_setup(unsigned int num_ghosts) {
    srand(time(NULL));

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


static struct position closest_position(struct position old_pos, struct ghosts *G, struct pacman *P, struct ghost *ghost);

/* Move the ghost id (according to its status). Returns the new position */
struct position ghosts_move(struct ghosts *G, struct pacman *P, unsigned int id) {
    ghost *ghost = by_id(G, id);
    struct position old_pos = ghost->pos;
    struct position tmp_pos = old_pos;
    struct position pacman_pos = pacman_get_position(P);

    if (ghost->status == NORMAL) {
        /* todo doesn't work properly */
        ghost->pos = closest_position(old_pos, G, P, ghost);
        #ifdef LOGGING
        FILE *fp;
        fp = fopen("normal.log", "a");
        fprintf(fp, "Position y: %d, position x: %d, ghost id: %d\n", ghost->pos.i, ghost->pos.j, ghost->id );
        fclose(fp);
        #endif
    }
    else if (ghost->status == EYES) {
        /* funzionante, legge la posizione suggerita dalla matrice per tornare alla casa dei fantasmi */
        struct position eyes_pos = old_pos;
        char c = G->arena.matrix[ghost->pos.i][ghost->pos.j];
        switch (c) {
            case UP_SYM:
                eyes_pos.i += UP;
                break;
            case DOWN_SYM:
                eyes_pos.i += DOWN;
                break;
            case LEFT_SYM:
                eyes_pos.j += LEFT;
                break;
            case RIGHT_SYM:
                eyes_pos.j += RIGHT;
                break;
        }
        #ifdef LOGGING
        FILE *fp;
        fp = fopen("eyes.log", "a");
        fprintf(fp, "Position y: %d, position x: %d, ghost id: %d, closest position: %c\n", ghost->pos.i, ghost->pos.j, ghost->id, c);
        fclose(fp);
        #endif
        if (is_free(eyes_pos, G, P)) ghost->pos =  eyes_pos;
    }
    else {
        struct position up_pos = old_pos, down_pos = old_pos, left_pos = old_pos, right_pos = old_pos;
        float up_dis = 0,  down_dis  = 0,  left_dis  = 0, right_dis = 0, best_dis;
        up_pos.i += UP;
        down_pos.i += DOWN;
        left_pos.j += LEFT;
        right_pos.j += RIGHT;
        if (is_in_arena(up_pos, G) || !is_free_other(up_pos, G, P)) {
            up_dis = distance(up_pos, pacman_pos);
        }
        else if (is_in_arena(down_pos, G) && is_free_other(down_pos, G, P)) {
            down_dis = distance(down_pos, pacman_pos);
            }
        else if (is_in_arena(left_pos, G)&& is_free_other(left_pos, G, P)) {
            left_dis = distance(left_pos, pacman_pos);
        }
        else if (is_in_arena(right_pos, G) && is_free_other(right_pos, G, P)) {
            right_dis = distance(right_pos, pacman_pos);

        }
        best_dis = MAX_4(up_dis, down_dis, left_dis, right_dis);
    }
    return ghost->pos;
}

static ghost *by_id(struct ghosts *G, unsigned int id) {
    return &G->ghosts[id];
}


static double distance(struct position pos1, struct position pos2) {
    unsigned int distance_x = (pos1.i - pos2.i) * (pos1.i - pos2.i);
    unsigned int distance_y = (pos1.j - pos2.j) * (pos1.j - pos2.j);
    return sqrt(distance_x + distance_y);
}

static int rand_bool() {
    return rand() % 3 == 0;
}

static int is_free(struct position pos, struct ghosts *G, struct pacman *P) {
    int i;
    char mat_val = G->arena.matrix[pos.i][pos.j];
    if (mat_val == XWALL_SYM)  
        return 0;
    for (i = 0; i < G->num_ghosts; i++) {
        if ((pos.i == G->ghosts[i].pos.i) && (pos.j == G->ghosts[i].pos.j)) 
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

static int is_in_arena(struct position pos, struct ghosts *G){
    return (pos.i < G->arena.columns && pos.j < G->arena.rows);
}

static struct position closest_position(struct position old_pos, struct ghosts *G, struct pacman *P, struct ghost *ghost){
        struct position pacman_pos = pacman_get_position(P);
        struct position up_pos = old_pos, down_pos = old_pos, left_pos = old_pos, right_pos = old_pos;
        /* left and right distances do not seem to work , they are always 1000 no matter what.*/
        float left_dis = 1000, right_dis = 1000, up_dis = 1000, down_dis = 1000, best_dis = 1000;
        up_pos.i += UP;
        down_pos.i += DOWN;
        left_pos.j += LEFT;
        right_pos.j += RIGHT;
        if (is_in_arena(up_pos, G) && is_free(up_pos, G, P)) {
            up_dis = distance(up_pos, pacman_pos);
        }
        if (is_in_arena(down_pos, G) && is_free(down_pos, G, P)) {
            down_dis = distance(down_pos, pacman_pos);
        }
        
        if (is_in_arena(left_pos, G) && is_free(left_pos, G, P)) {
            left_dis = distance(left_pos, pacman_pos);
        }
        else if (is_in_arena(right_pos, G) && is_free(right_pos, G, P)) {
            right_dis = distance(right_pos, pacman_pos);
        }
        best_dis = MIN_4(up_dis, down_dis, left_dis, right_dis);
        #ifdef LOGGING
        FILE *fp;
        fp = fopen("closest_position.log", "a");
        fprintf(fp, "up: %f, down: %f, left: %f, right: %f, best: %f\n", up_dis, down_dis, left_dis, right_dis,  best_dis);
        fclose(fp);
        #endif
        if (best_dis == 1000) return old_pos;
        else if (best_dis == right_dis) return right_pos;
        else if (best_dis == up_dis) return up_pos;
        else if (best_dis == down_dis) return down_pos;
        else if (best_dis == left_dis) return left_pos;
}
#endif
