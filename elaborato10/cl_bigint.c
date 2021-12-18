#include "selector.h"
#ifdef CL_BIGINT
#include <stdlib.h>
#include "cl_bigint.h"


#define SGN(N) (N == NULL ? 0 : ((N)->x < 0 ? -1 : 1))


static bigint* last(bigint *L, bigint *head_node);

static bigint *mul_digit(bigint *N, digit x, bigint *head,bigint *tail);

static bigint *mul_digit_pos(bigint *N, digit x);

static void add_zeros(bigint *N, unsigned int n, bigint *tail); 

static int tail_insert(bigint **N, digit x, bigint *tail);

static bigint *sum_pos(bigint *N1, bigint *N2);

static void delete(bigint **N);

static void negate(bigint *N);

static bigint* bigint_alloc(digit x) {
	bigint* tmp = (bigint*)malloc(sizeof(bigint));

	if (tmp != NULL) {
		tmp->x = x;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	return tmp;
}

static int bigint_delete(bigint* N) {
	if (N == NULL) {
		return 1;
	}
    else {
        bigint *prv = N->prev, *nxt = N->next;
        nxt->prev = prv;
        prv->next = nxt;
        free(N);
        return 0;
    }
}

static int bigint_insert(bigint *N, digit x){
    if (N == NULL){
        return 1;
    }
    else {
        bigint *tmp = bigint_alloc(x), *nxt = N->next, *prv = N;
        if (tmp != NULL) {
            tmp->prev = prv;
            tmp->next = nxt;
            prv->next = tmp;
            nxt->prev = tmp;
        }
        return tmp == NULL;
    }
}

static int head_insert(bigint** N, digit x) {
    if (N == NULL)
        return 1;
    else if (*N == NULL) 
        return ((*N = bigint_alloc(x)) == NULL);
    else if(bigint_insert((*N)->prev, x) == 1)
        return 1;
    else 
        return ((*N = (*N)->prev) == NULL);
}

static int head_delete(bigint** N) {
	if (N == NULL || *N == NULL) {
		return 1;
	}
    else if (*N == (*N)->next) {
        free(*N);
        *N = NULL;
        return 0;
    } else {
        *N = (*N)->next;
        return bigint_delete((*N)->prev);
    }
}

static void remove_leading_zeros(bigint** N) {
	if (N != NULL && *N != NULL) {
        while ((*N)->x == 0 && *N !=(*N)->next)
            head_delete(N);
    }
}

bigint *mul(bigint *N1, bigint *N2) {
    int sgn1 = SGN(N1), sgn2 = SGN(N2), n = 0;
    bigint  *n1_head = N1, *n2_head = N2, *tail2 = last(N2, n2_head), *tail1 = last(N1, N1);
    if (!sgn1 || !sgn2) return NULL;
    bigint *tmp = last(N2, tail2), *N = bigint_alloc(0);
    while (tmp != n2_head){ 
        bigint *a, *b;
        a = mul_digit(N1, tmp->x, n1_head, tail1);
        add_zeros(a, n++, tail1);
        b = sum_pos(N, a);
        delete(&N);
        delete(&a);
        N = b;
        tmp = tmp->prev;
    } 
    if (sgn1 != sgn2) negate(N);
    return N;
}

static bigint* last(bigint *L, bigint *head_node) {
    while (L->next != head_node && L->next){
        L = L->next;
    }
    return L;
}

static bigint *mul_digit(bigint *N, digit x, bigint *head,bigint *tail) {
    if (!N || x > 9 || x < -9)  {
        return NULL;
    }
    else if (!x) {
        return bigint_alloc(0);
    }
    else {
        N->x = abs(N->x);
        bigint* X = mul_digit_pos(N, abs(x));
        return X;
    } 
}

static bigint *mul_digit_pos(bigint *N, digit x) {
    bigint *X = NULL;
    int val = 0, car = 0; 
    bigint *head = N;
    N = N->prev;
    while ((N != NULL) || car != 0){
        val = (N ? N->x : 0) * x + car;
        car = val / 10;
        val = val % 10;
        head_insert(&X, val);
        N = N != NULL && N != head ? N->prev: NULL;
    }
    return X;
}

static void add_zeros(bigint *N, unsigned int n, bigint *tail) {
    if (N && N->x) {
        int i;
        for (i = 0; i < n; i++)
            tail_insert(&N, 0, tail);
    }
}

static int tail_insert(bigint **N, digit x, bigint *tail) {
    if (!N)
        return 1;
    else if (!(*N)) {
        return head_insert(N, x);
    }
    else {
        bigint *tmp = tail;
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
        bigint *head1 = N1,  *head2 = N2;
        N1 = N1->prev;
        N2 = N2->prev;
        while (N1 || N2 || car) {
            val = (N1 ? N1->x : 0) + (N2 ? N2->x : 0) + car;
            car = val / 10;
            val = val % 10;
            head_insert(&N, val);
            N1 = N1 != NULL && N1 != head1 ? N1->prev: NULL;
            N1 = N1 != NULL && N1 != head2 ? N1->prev: NULL;
        }
    }
    return N;
}

static void delete(bigint **N){
if (*N && N) {
        while ((*N)->next) {
            head_delete(N);
        }
    }
}

static void negate(bigint *N){
    if (N) 
        N->x *= -1;
}
#endif
