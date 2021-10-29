#define STUD
#ifdef STUD

#include "game.h"

#define LEFT -1
#define RIGHT 1
#define UP   -1
#define DOWN  1

/*
 * La tavola da gioco
 */
static struct table {
	int width;
	int height;
    int pad_length;
} table;

/*
 * La palla
 */
static struct ball {
	struct position pos;
	struct position direction;
	struct position initial_pos;
} ball;	

/*
 * Le racchette/pad
 */
static struct pad {
	struct position pos;
    int type; /* LEFT o RIGHT */
	int score;
} pad1, pad2;

/*
 * Riporta la palla alla sua posizione iniziale
 */
static void reset_ball(void);

/*
 * Ritorna 1 se la palla interseca un pad, altrimenti 0
 */
static int is_pad_hit(struct pad pad);

/*
 * Ritorna 1 se la palla colpisce il bordo superiore del pad, altrimenti 0
 * Si basa solo sulla coordinata Y, è necessario chiamare is_pad_hit prima
 */
static int is_top_corner_hit(struct pad pad);

/**
 * Ritorna 1 se la palla colpisce il bordo superiore del pad, altrimenti 0
 * Si basa solo sulla coordinata Y, è necessario chiamare is_pad_hit prima
 */
static int is_bottom_corner_hit(struct pad pad);

void setup_game(int height, int width,
	struct position ball_pos, struct position ball_dir,
	struct position pad1_pos, struct position pad2_pos, int pad_len) {
	table.height = height;
	table.width = width;
    table.pad_length = pad_len;

	ball.pos =  ball_pos;
    ball.direction = ball_dir;
    ball.initial_pos = ball_pos;

    pad1.pos = pad1_pos;
    pad2.type = LEFT;
    pad1.score = 0;

    pad2.pos = pad2_pos;
    pad2.type = RIGHT;
    pad2.score = 0;
}

void move_ball() {
	/* Se la palla colpisce le pareti a destra e a sinistra, un punto viene segnato */
	if (ball.pos.x <= 0) {
		pad2.score++;
		reset_ball();
		return;
	} else if (ball.pos.x > (table.width -2)) {
		pad1.score++;
		reset_ball();
		return;
	}

    /* Se la palla colpisce le pareti in basso ed in alto, la sua direzione verticale viene invertita */
    if (ball.pos.y <= 0) {
        ball.direction.y = DOWN;
    } else if (ball.pos.y >= table.height) {
        ball.direction.y = UP;
    }

    /* Se la palla colpisce una racchetta, la sua direzione orizzontale viene invertita */
    if(is_pad_hit(pad1)) {
        ball.direction.x = RIGHT;
        if(is_top_corner_hit(pad1)) {
            ball.direction.y = UP;
        } else if(is_bottom_corner_hit(pad1)) {
            ball.direction.y = DOWN;
        }
    } else if(is_pad_hit(pad2)) {
        ball.direction.x = LEFT;
        if(is_top_corner_hit(pad2)) {
            ball.direction.y = UP;
        } else if(is_bottom_corner_hit(pad2)) {
            ball.direction.y = DOWN;
        }
    }

	/* Viene aggiornata la posizione della palla in base alla sua direzione */
	ball.pos.x += ball.direction.x;
	ball.pos.y += ball.direction.y;
}

void move_pad1_up(void) {
	if (pad1.pos.y > 0)
		pad1.pos.y--;
}

void move_pad2_up(void) {
	if (pad2.pos.y > 0)
		pad2.pos.y--;
}

void move_pad1_down(void) {
	if (pad1.pos.y < (table.height - table.pad_length + 1))
		pad1.pos.y++;
}

void move_pad2_down(void) {
	if (pad2.pos.y < (table.height - table.pad_length + 1))
		pad2.pos.y++;
}

unsigned int get_pad1_score(void) {
	return pad1.score;
}

unsigned int get_pad2_score(void) {
	return pad2.score;
}

struct position get_ball_pos(void) {
	return ball.pos;
}

struct position get_pad1_pos(void) {
	return pad1.pos;
}

struct position get_pad2_pos(void) {
	return pad2.pos;
}

unsigned int get_pad_len(void) {
	return table.pad_length;
}

static void reset_ball(void) {
	ball.pos = ball.initial_pos;
}

static int is_pad_hit(struct pad pad) {
    return ball.pos.x + pad.type == pad.pos.x && ball.pos.y >= pad.pos.y - 1 && ball.pos.y <= pad.pos.y + table.pad_length + 1;
}

static int is_top_corner_hit(struct pad pad) {
    return ball.pos.y == pad.pos.y - 1;
}

static int is_bottom_corner_hit(struct pad pad) {
    return ball.pos.y == pad.pos.y + table.pad_length + 1;
}

#endif

