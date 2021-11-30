#include "snake.h" 
#include <stdio.h>
#include <stdlib.h>

/*
 * Ottiene la parte dello snake all'index dato
 */
static struct body *body_at(struct snake *s, unsigned int index);

/*
 * Converte la direzione in una position relativa con i e j tra -1 e 1.
 */
static struct position dir_to_relative_pos(enum direction dir);

struct snake *snake_create(unsigned int rows, unsigned int cols) {
    struct snake *snake = malloc(sizeof *snake);
    snake->rows = rows;
    snake->cols = cols;
    snake->length = 1;

    struct body *body = malloc(sizeof *body);
    struct position pos;
    pos.i = rand() % rows;
    pos.j = rand() % cols;
    body->pos = pos;
    snake->body = body;

    return snake;
}

void snake_kill(struct snake *s) {
    free(s);
}

struct position snake_head(struct snake *s) {
	return s->body->pos;
}

struct position snake_body(struct snake *s, unsigned int i) {
    return body_at(s, i)->pos;
}

int snake_knotted(struct snake *s) {
	return 0;
}

void snake_move(struct snake *s, enum direction dir) {
    snake_increase(s, dir);
    snake_decrease(s, 1);
}

void snake_reverse(struct snake *s) {
}

void snake_increase(struct snake *s, enum direction dir) {
    struct body *old_head = s->body;
    struct body *new_head = malloc(sizeof *new_head);

    struct position relative_dir = dir_to_relative_pos(dir);
    struct position pos;
    pos.i = old_head->pos.i + relative_dir.i;
    pos.j = old_head->pos.j + relative_dir.j;
    new_head->pos = pos;

    s->body = new_head;
    new_head->next = old_head;
    old_head->prev = new_head;

    s->length++;
}

void snake_decrease(struct snake *s, unsigned int decrease_len) {
    body_at(s, s->length - decrease_len)->next = NULL;
    s->length -= decrease_len;
}

/* Saves the snake into the filename. */
void snake_save(struct snake *s, char *filename) {
    
}

/* Loads the snake from filename */
struct snake *snake_read(char *filename) {
    return snake_create(10, 10); /* test */
}

static struct body *body_at(struct snake *s, unsigned int index) {
    struct body *body = s->body;
    unsigned int i;
    for(i = 0; i < index; i++) {
        body = body->next;
    }
    return body;
}

static struct position dir_to_relative_pos(enum direction dir) {
    struct position rel;
    rel.i = 0;
    rel.j = 0;

    switch (dir) {
        case LEFT:
            rel.j = -1;
            break;
        case RIGHT:
            rel.j = 1;
            break;
        case UP:
            rel.i = -1;
            break;
        case DOWN:
            rel.i = 1;
            break;
    }
    return rel;
}