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
	ritorna 1 se la palla ha un tocco pieno, se no ritorna 0
 */
static int is_full_touch(struct pad pad);
static int pad2_hitting(struct pad pad);
static int pad1_hitting(struct pad pad);
static int top_hitting(struct pad pad);
static int bottom_hitting(struct pad pad);


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
    pad1.type = LEFT;
    pad1.score = 0;

    pad2.pos = pad2_pos;
    pad2.type = 2;
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
	if (is_full_touch(pad1)){
		ball.direction.x = RIGHT;
	}
	/* se la posizione della palla è compresa tra quella di pad-1, pad e pad+1 allora  é possibile che si tocchi (per pad1)*/ 
	else if (pad1_hitting(pad1)){
		if (top_hitting(pad1)){
			ball.direction.x = RIGHT;
			ball.direction.x = UP;
		}
		if (bottom_hitting(pad1)){
			ball.direction.x = RIGHT;
			ball.direction.y = DOWN;
		}
	}

	if (is_full_touch(pad2)){
	/* se tocca l' angolo superiore */
		ball.direction.x = LEFT;
	}
	else if (pad2_hitting(pad2)){
		if (bottom_hitting(pad2)) {
			ball.direction.x = LEFT;
			ball.direction.y = DOWN;
		if (top_hitting(pad2)){
			ball.direction.x = LEFT;
			ball.direction.y = UP;
		}
	}
	}

	/* Viene aggiornata la posizione della palla in base alla sua direzione */
	ball.pos.x += ball.direction.x;
	ball.pos.y += ball.direction.y;
}

void move_pad1_up(void) {
	if (pad1.pos.y > 0 && !pad1_hitting(pad1) && !top_hitting(pad1))
		pad1.pos.y--;
}

void move_pad2_up(void) {
	if (pad2.pos.y > 0 )
		pad2.pos.y--;
}

void move_pad1_down(void) {
	if ((pad1.pos.y < table.height - table.pad_length + 1) )
		pad1.pos.y++;
}

void move_pad2_down(void) {
	if ((pad2.pos.y < table.height - table.pad_length + 1) )
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

static int is_full_touch(struct pad pad) {
	return ball.pos.x + pad.type == pad.pos.x && ball.pos.y >= pad.pos.y - 1 && ball.pos.y <= pad.pos.y + table.pad_length + 1;
}

static int pad1_hitting(struct pad pad){
	return (ball.pos.x  == pad.pos.x || ball.pos.x  == pad.pos.x +1 || ball.pos.x  == pad.pos.x -1);
}

static int pad2_hitting(struct pad pad){
	return (ball.pos.x == pad.pos.x -2 || ball.pos.x == pad.pos.x - 1 || ball.pos.x == pad.pos.x); 
	/* todo mettere +-1 */
}

static int top_hitting(struct pad pad){
	return (ball.pos.y == pad.pos.y - 1);
}
static int bottom_hitting(struct pad pad){
	return (ball.pos.y == pad.pos.y +table.pad_length - 1);
}

#endif
