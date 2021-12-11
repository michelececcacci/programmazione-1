#include "snake.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Ottiene la parte dello snake all'index dato
 */
static struct body *body_at(struct snake *s, unsigned int index);

/*
 * Effettua un movimento (shift) verso una direzione applicando il warping nei bordi
 */
static struct position shift_pos(struct position pos, enum direction dir, unsigned int rows, unsigned int cols);

static int split_str(char *input, char **output, char *separator);

static unsigned int strtoi(char *input);

struct snake *snake_create(unsigned int rows, unsigned int cols) {
    struct snake *snake = malloc(sizeof(struct snake));
    snake->rows = rows;
    snake->cols = cols;
    snake->length = 1;

    struct body *body = malloc(sizeof(struct body));
    struct position pos;
    pos.i = rand() % rows;
    pos.j = rand() % cols;
    body->pos = pos;
    snake->body = body;

    return snake;
}

void snake_kill(struct snake *s) {
    struct body *current = s->body, *tmp;
    while (current->next != NULL) {
        tmp = current;
        current = current->next;
        free(tmp);
    }
    free(current);
    free(s);
}

struct position snake_head(struct snake *s) {
    return s->body->pos;
}

struct position snake_body(struct snake *s, unsigned int i) {
    return body_at(s, i)->pos;
}

int snake_knotted(struct snake *s) {
    struct body *current = s->body->next;
    while (current != NULL) {
        if ((s->body->pos.i == current->pos.i) && (s->body->pos.j == current->pos.j)) {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

void snake_move(struct snake *s, enum direction dir) {
    snake_increase(s, dir);
    snake_decrease(s, 1);
}

void snake_reverse(struct snake *s) {
    struct body *tmp = NULL;
    struct body *current = s->body;
    while (current != NULL) {
        tmp = current->prev;           /* saving the previous node */
        current->prev = current->next; /* assigning at the previous node the next one */
        current->next = tmp;           /* assigning at the next node the vale of the previous one */
        current = current->prev;       /* the current become the next node (to keep on the loop) */
    }
    if (tmp != NULL) s->body = tmp->prev;
}


void snake_increase(struct snake *s, enum direction dir) {
    struct body *body = malloc(sizeof(struct body));

    body->next = s->body;
    body->prev = NULL;
    body->pos = shift_pos(s->body->pos, dir, s->rows, s->cols);

    s->body->prev = body;
    s->body = body;

    s->length++;
}


void snake_decrease(struct snake *s, unsigned int decrease_len) {
    if (s->length <= decrease_len) return;
    struct body *body = body_at(s, s->length - 1);;
    s->length -= decrease_len;

    unsigned int i;
    for (i = 0; i < decrease_len; i++) {
        body = body->prev;
        free(body->next);
        body->next = NULL;
    }
}


/* Saves the snake into the filename. */
void snake_save(struct snake *s, char *filename) {
    FILE *fp;
    fp = fopen(filename, "w");
    struct body *current = s->body;
    fprintf(fp, "%u %u %u\n", s->length, s->rows, s->cols);
    while (current->next != NULL) {
        fprintf(fp, "%d %d\n", current->pos.i, current->pos.j);
        current = current->next;
    }
    fprintf(fp, "%d %d\n", current->pos.i, current->pos.j);
    fclose(fp);
}

/* Loads the snake from filename */
struct snake *snake_read(char *filename) {
    struct snake *s = malloc(sizeof(struct snake));
    struct body *current = NULL;
    FILE *fp = fopen(filename, "r");

    int line = 0;
    char buffer[255];
    while (fgets(buffer, 255, fp)) {
        char *split[50];
        split_str(buffer, split, " ");
        if (line == 0) {
            s->length = strtoi(split[0]);
            s->rows = strtoi(split[1]);
            s->cols = strtoi(split[2]);
        } else {
            struct body *body = malloc(sizeof(struct body));
            struct position pos;
            pos.i = strtoi(split[0]);
            pos.j = strtoi(split[1]);
            body->pos = pos;
            if (current == NULL) {
                s->body = body;
                current = body;
            } else {
                current->next = body;
                body->prev = current;
                current = current->next;
            }
        }
        line++;
    }
    fclose(fp);
    return s;
}

static struct body *body_at(struct snake *s, unsigned int index) {
    struct body *body = s->body;
    unsigned int i;
    for (i = 0; i < index; i++) {
        body = body->next;
    }
    return body;
}

static struct position shift_pos(struct position pos, enum direction dir, unsigned int rows, unsigned int cols) {
    switch (dir) {
        case LEFT:
            pos.j = (pos.j - 1 + cols) % cols;
            break;
        case RIGHT:
            pos.j = (pos.j + 1 + cols) % cols;
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

static int split_str(char *input, char **output, char *separator) {
    int size = 0, i;
    char *temp;
    temp = strtok(input, separator);
    for (i = 0; temp != NULL; i++) {
        size++;
        output[i] = temp;
        temp = strtok(NULL, separator);
    }
    return size;
}

static unsigned int strtoi(char *input) {
    char *end;
    return strtol(input, &end, 10);
}