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
    /* togli il commento per caricare da read
    e ricorda di togliere il commento in knotted
    struct snake *s = snake_read("test.txt");
    return s;*/
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
            /* togli il commento per salvare
            snake_save(s, "test.txt");*/
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
    /*printf("\n\nTEST l=%d\n", s->length);*/
    struct body *body = s->body; /* body_at(s, s->length - 1); */
    unsigned int i;
    for(i = 0; i < s->length - 1; i++) {
        /*printf("%d ", i);*/
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
    FILE *fp;    
    fp = fopen(filename, "w");
    struct body *current = s->body;
    fprintf(fp, "%u %u %u\n", s->length, s->rows, s->cols);
    unsigned int i;
    for (i = 0; i < s->length; i++){
        fprintf(fp, "%d %d\n", current->pos.i, current->pos.j);
        current = current->next;
    }
    fclose(fp);
}

/* Loads the snake from filename */
struct snake *snake_read(char *filename) {
    struct snake *s = malloc(sizeof *s);
    struct body *current = NULL;
    FILE *fp = fopen(filename, "r");

    int line = 0;
    char buffer[255];
    while(fgets(buffer, 255, fp)) {
        char *split[50];
        split_str(buffer, split, " ");
        if(line == 0) {
            s->length = strtoi(split[0]);
            s->rows = strtoi(split[1]);
            s->cols = strtoi(split[2]);
        } else {
            struct body *body = malloc(sizeof *body);
            struct position pos;
            pos.i = strtoi(split[0]);
            pos.j = strtoi(split[1]);
            body->pos = pos;
            if(current == NULL) {
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

static int split_str(char *input, char **output, char *separator) {
    int size = 0;
    char *temp;
    temp = strtok(input, separator);

    for(int i = 0; temp != NULL; i++) {
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