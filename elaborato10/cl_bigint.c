#include "selector.h"

#ifdef CL_BIGINT

#include <stdlib.h>
#include "dl_bigint.h"

/* Verifica se n è un numero valido */
static int is_valid(bigint *n);
/* Alloca ed inizializza un bigint */
static bigint *bigint_alloc(digit x);
/* Dealloca e rimuove un bigint */
static int bigint_delete(bigint *N);
/* Rimuove la testa del bigint */
static int head_delete(bigint **N);
/* Inserisce una cifra al bigint */
static int bigint_insert(bigint *N, digit x);
/* Inserisce una cifra in testa al bigint */
static int head_insert(bigint **N, digit x);
/* Rimuove gli zeri in eccesso */
static void remove_zeros(bigint **N);
/* Ottiene l'ultima cifra del bigint */
static bigint *last(bigint *N);
/* Effettua uno shift nel bigint */
static int shift(bigint **n, digit x, bigint *tail);
/* Inverte il segno del bigint */
static void reverse_sign(bigint *n);
/* Ottiene il segno relativo ai bigint */
static digit get_sign(bigint *n1, bigint *n2);

bigint *mul(bigint *N1, bigint *N2) {
    if (N1 == NULL || N2 == NULL)
        return NULL;
    if (!is_valid(N1) || !is_valid(N2))
        return NULL;

    bigint *tail1 = last(N1);
    bigint *tail2 = last(N2);
    bigint *rem = bigint_alloc(0);
    bigint *rem_tail_1 = last(rem);
    bigint *rem_tail_2 = last(rem);
    digit sign = get_sign(N1, N2);
    reverse_sign(N1);
    reverse_sign(N2);

    N1 = tail1;
    do {
        N2 = tail2;
        rem = rem_tail_2;
        do {
            digit result = (digit) ((N1->x) * (N2->x));
            rem->x += result;
            digit carry = rem->x / 10;
            rem->x %= 10;
            shift(&rem, carry, rem_tail_1);
            N2 = N2->prev;
        } while (N2 != tail2);

        N1 = N1->prev;
        rem_tail_2 = rem_tail_2->prev;
    } while (N1 != tail1);

    remove_zeros(&rem);
    rem->x *= sign;
    return rem;
}

static int is_valid(bigint *n) {
    if (n->x > 9 || n->x < -9) return 0;
    bigint *next;
    for (next = n->next; next != n; next = next->next) {
        if (next->x > 9 || next->x < 0) return 0;
    }
    return 1;
}

static bigint *bigint_alloc(digit x) {
    bigint *tmp = (bigint *) malloc(sizeof(bigint));

    if (tmp != NULL) {
        tmp->x = x;
        tmp->next = tmp;
        tmp->prev = tmp;
    }
    return tmp;
}

static int bigint_delete(bigint *N) {
    if (N == NULL) return 1;
    bigint *prev = N->prev, *next = N->next;
    next->prev = prev;
    prev->next = next;
    free(N);
    return 0;
}

static int head_delete(bigint **N) {
    if (*N == NULL) return 1;
    if (*N == (*N)->next) {
        free(*N);
        *N = NULL;
        return 0;
    }
    *N = (*N)->next;
    return bigint_delete((*N)->prev);
}

static int bigint_insert(bigint *N, digit x) {
    if (N == NULL) return 1;

    bigint *tmp = bigint_alloc(x), *next = N->next, *prev = N;
    if (tmp != NULL) {
        tmp->prev = prev;
        tmp->next = next;
        prev->next = tmp;
        next->prev = tmp;
    }
    return tmp == NULL;
}

static int head_insert(bigint **N, digit x) {
    if (*N == NULL) {
        *N = bigint_alloc(x);
        return *N == NULL;
    }
    else if (bigint_insert((*N)->prev, x) == 1) {
        return 1;
    }
    else {
        *N = (*N)->prev;
        return *N == NULL;
    }
}

static void remove_zeros(bigint **N) {
    if (N != NULL && *N != NULL) {
        while ((*N)->x == 0 && *N != (*N)->next) {
            head_delete(N);
        }
    }
}

static bigint *last(bigint *N) {
    return N->prev;
}

static int shift(bigint **n, digit x, bigint *tail) {
    if ((*n)->prev == tail) {
        return head_insert(n, x);
    }
    *n = (*n)->prev;
    (*n)->x += x;
    return 1;
}

static void reverse_sign(bigint *n) {
    if (n->x < 0) n->x *= -1;
}

static digit get_sign(bigint *n1, bigint *n2) {
    return n1->x * n2->x < 0 ? -1 : 1;
}

#endif
