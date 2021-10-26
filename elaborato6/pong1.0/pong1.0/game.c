#define STUD
#ifdef STUD

#include "game.h"

void setup_game(int height, int width,
	struct position ball_pos, struct position ball_dir,
	struct position pad1_pos, struct position pad2_pos, int pad_len) {
		
}

void move_ball() {
	
}
    
void move_pad1_up(void) {
	
}

void move_pad2_up(void) {
	
}

void move_pad1_down(void) {
	
}

void move_pad2_down(void) {
	
}

unsigned int get_pad1_score(void) {
	return 0;
}

unsigned int get_pad2_score(void) {
	return 0;
}

struct position get_ball_pos(void) {
    struct position p={0,0};
	return p;
}

struct position get_pad1_pos(void) {
	struct position p={0,0};
	return p;
}

struct position get_pad2_pos(void) {
	struct position p={0,0};
	return p;
}

unsigned int get_pad_len(void) {
	return 0;
}

#endif
