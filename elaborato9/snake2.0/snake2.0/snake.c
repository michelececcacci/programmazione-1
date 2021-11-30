#include "snake.h" 
#include <stdio.h>
#include <stdlib.h>

/*
 * Ottiene la parte dello snake all'index dato
 */
static struct body *body_at(struct snake *s, unsigned int index);

/*
 * Effettua un movimento (shift) verso una direzione applicando il warping nei bordi
 */
static struct position shift_pos(struct position pos, enum direction dir, unsigned int rows, unsigned int cols);

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
    struct body *head = s->body;
    struct body *body = head->next;
    unsigned int i;
    for(i = 0; i < s->length; i++) {
        if(head->pos.i == body->pos.i && head->pos.j == body->pos.j) {
            return 1;
        }
        body = body->next;
    }
	return 0;
}

void snake_move(struct snake *s, enum direction dir) {
    snake_increase(s, dir);
    snake_decrease(s, 1);
}

void snake_reverse(struct snake *s) {
    printf("\n\nTEST l=%d\n", s->length);
    struct body *body = s->body; /* body_at(s, s->length - 1); */
    unsigned int i;
    for(i = 0; i < s->length - 1; i++) {
        printf("%d ", i);
        if(body == NULL) break;
        struct body *old_next = body->next;
        if(old_next == NULL) continue;
        printf("pos=[%d, %d]\n", body->pos.i, body->pos.j);
        body->next = body->prev;
        body->prev = old_next;
        body = old_next;
    }
}

void snake_increase(struct snake *s, enum direction dir) {
    struct body *old_head = s->body;
    struct body *new_head = malloc(sizeof *new_head);

    struct position pos;
    pos.i = old_head->pos.i;
    pos.j = old_head->pos.j;
    pos = shift_pos(pos, dir, s->rows, s->cols);
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

static struct position shift_pos(struct position pos, enum direction dir, unsigned int rows, unsigned int cols) {
    switch (dir) {
        case LEFT:
            pos.j = (pos.j - 1 +  cols) % cols;
            break;
        case RIGHT:
            pos.j = (pos.j + 1 +  cols) % cols;
            break;
        case UP:
            pos.i = (pos.i - 1 + rows) % rows;
            break;
        case DOWN:
            pos.i = (pos.i + 1 + rows) % rows;
            break;
    }
    return pos;
}