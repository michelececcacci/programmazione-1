#include "snake.h" 
#include <stdio.h>


struct snake *snake_create(unsigned int rows, unsigned int cols) {
  return NULL;
} 

void snake_kill(struct snake *s) {	
}

struct position snake_head(struct snake *s) {
	struct position p;
	return p;

}

struct position snake_body(struct snake *s, unsigned int i) {
	struct position p;
	return p;
}

int snake_knotted(struct snake *s) {
	return 0;
}

void snake_move(struct snake *s, enum direction dir) {
}

void snake_reverse(struct snake *s) {
}

void snake_increase(struct snake *s, enum direction dir) {
}

void snake_decrease(struct snake *s, unsigned int decrease_len) {
}


/* Saves the snake into the filename. */
void snake_save(struct snake *s, char *filename) {
    
}

/* Loads the snake from filename */
struct snake *snake_read(char *filename) {
    return NULL;    
}
