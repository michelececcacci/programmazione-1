#include <stdio.h>
#include "selector.h"
#ifdef DL_BIGINT
#include <stdlib.h>
#include "dl_bigint.h"
#include "dl_main.c"

#define SGN(N) (N == NULL ? 0 : ((N)->x < 0 ? -1 : 1))

static bigint* first(bigint *L);

static bigint* last(bigint *L);

static bigint *mul_digit(bigint *N, digit x);

static bigint *mul_digit_pos(bigint *N, digit x);

static void add_zeros(bigint *N, unsigned int n);

static int tail_insert(bigint **N, digit x);

static bigint *sum_pos(bigint *N1, bigint *N2);

static void delete(bigint **N);

bigint *mul(bigint *N1, bigint *N2) {
    int sgn1 = SGN(N1), sgn2 = SGN(N2), n = 0;
    // todo relook at this statement
    if (!sgn1  || !sgn2)
        return NULL;
    bigint *tmp = last(N2), *N = bigint_alloc(0);
    while (tmp != NULL) {
        bigint *a, *b;
        a = mul_digit(N1, tmp->x);
        add_zeros(a,n++);
        b = sum_pos(N, a);
        delete(&N);
        delete(&a);
        N = b;
        tmp = tmp->prev;
    }
}

static bigint* first(bigint *L) {
    while (L->prev) {
        L  = L->prev; 
    }
    return L;
}

static bigint* last(bigint *L) {
    while (L->next){
        L = L->next;
    }
    return L;
}

static bigint *mul_digit(bigint *N, digit x) {
    // could be wrong
    if (!N || x > 9 || x < -9)  {
        return NULL;
    }
    else if (!x) {
        return bigint_alloc(0);
    }
    else {
        int sgn_n = SGN(N);
        bigint* X = mul_digit_pos(N, x);
        // todo  mul_digit_pos
        // define signs
        return X;
    } 
}

static bigint *mul_digit_pos(bigint *N, digit x) {
    bigint *X= NULL;
    int val = 0, car = 0; 
    N = last(N);
    while (N || car){
        val = (N ? N->x : 0) * x + car;
        N = N ? N->prev : NULL;
    }
    return X;
}

static void add_zeros(bigint *N, unsigned int n) {
    if (N && N->x) {
        int i;
        for (i = 0; i < n; i++)
            tail_insert(&N, 0);
    }

}

static int tail_insert(bigint **N, digit x) {
    if (!N)
        return 1;
    else if (!(*N)) {
        return head_insert(N, x);
    }
    else {
        bigint *tmp = last(*N);
        tmp->next = bigint_alloc(x);
        if (tmp->next)
            tmp->next->prev = tmp;
        return tmp->next != NULL;
    }
}

static bigint *sum_pos(bigint *N1, bigint *N2) {
    bigint *N = NULL;
    if (SGN(N1) > 0 && SGN(N2) > 0) {
        int val = 0, car = 0;;
        N1 = last(N1);
        N2 = last(N2);
        while (N1 || N2 || car) {
            val = (N1 ? N1->x : 0) + (N2 ? N2->x : 0) + car;
            car = val / 10;
            val = val % 10;
            head_insert(&N, val);
            N1 = N1 ? N1->prev : NULL;
            N2 = N2 ? N2->prev : NULL;
        }
    }
    return N;
}

static void delete(bigint **N){
if (N) {
        while (*N) {
            head_delete(N);
        }
    }
}
#endif
