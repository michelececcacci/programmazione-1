#define STUD
#ifdef STUD

#include "game.h"

/* since the pad len is the same and doesn't change it is stored in game_table */
struct game_table {
	int width;
	int height;
	int pad_len;
} table;

/* direction is still not implemented */
struct ball_struct {
	struct position pos;
	struct position direction;
} ball;	

struct pad {
	struct position pos;
	int score;
} pad1, pad2;

void setup_game(int height, int width,
	struct position ball_pos, struct position ball_dir,
	struct position pad1_pos, struct position pad2_pos, int pad_len) {	
	table.height = height;
	table.width = width;
	ball.pos =  ball_pos;
	pad1.pos = pad1_pos;	
	pad2.pos = pad2_pos;
	pad1.score = 0;
	pad2.score = 0;
	table.pad_len = pad_len;
}

void move_ball() {
	
}
    
/* the notation has the lowest point as width, height so this works	*/
void move_pad1_up(void) {
	if (pad1.pos.y > 0)
		pad1.pos.y -= 1;	
}

void move_pad2_up(void) {
	if (pad2.pos.y > 0)
		pad2.pos.y -= 1;	
}

void move_pad1_down(void) {
	if (pad1.pos.y < (table.height- table.pad_len + 1))
		pad1.pos.y += 1;	
}

void move_pad2_down(void) {
	if (pad2.pos.y < (table.height- table.pad_len + 1))
		pad2.pos.y += 1;	
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
	return table.pad_len;
}

#endif
