#include "selector.h"
#ifdef CL_BIGINT
#include <stdlib.h>
#include "cl_bigint.h"


#define SGN(N) (N == NULL ? 0 : ((N)->x < 0 ? -1 : 1))

static bigint* first(bigint *L);

static bigint* last(bigint *L, bigint *head_node);

static bigint *mul_digit(bigint *N, digit x, bigint *tail); 

static bigint *mul_digit_pos(bigint *N, digit x, bigint *tail) ;

static void add_zeros(bigint *N, unsigned int n, bigint *tail); 

static int tail_insert(bigint **N, digit x, bigint *tail);

static bigint *sum_pos(bigint *N1, bigint *N2, bigint *tail1, bigint *tail2);

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
		if (N->next != NULL)
			N->next->prev = N->prev;
		if (N->prev != NULL)
			N->prev->next = N->next;
		free(N);
		return 0;
	}
}

static int head_insert(bigint** N, digit x) {
	if (N == NULL) {
		return 1;
	}
	else if (*N == NULL) {
		return (*N = bigint_alloc(x)) == NULL;
	}
	else {
		bigint* tmp = bigint_alloc(x);

		if (tmp != NULL) {
			tmp->next = *N;
			(*N)->prev = tmp;
			*N = tmp;
		}
		return tmp == NULL;
	}
}

static int head_delete(bigint** N) {
	if (N == NULL || *N == NULL) {
		return 1;
	}
	else {
		bigint* tmp = *N;

		*N = (*N)->next;
		return bigint_delete(tmp);
	}
}

static void remove_leading_zeros(bigint** N) {
	if (N != NULL) {
		while (*N != NULL && (*N)->x == 0 && (*N)->next != NULL)
			head_delete(N);
	}
}

bigint *mul(bigint *N1, bigint *N2) {
    int sgn1 = SGN(N1), sgn2 = SGN(N2), n = 0, tail2 = last(N2, N2), tail1 = last(N1, N1);
    if (!sgn1 || !sgn2) return NULL;
    bigint *tmp = last(N2, tail2), *N = bigint_alloc(0);
    while (tmp != NULL) {
        bigint *a, *b;
        a = mul_digit(N1, tmp->x, tail1);
        add_zeros(a, n++, tail1);
        b = sum_pos(N, a, tail1, tail2);
        delete(&N);
        delete(&a);
        N = b;
        tmp = tmp->prev;
    }
    if (sgn1 != sgn2) negate(N);
    return N;
}

static bigint* first(bigint *L) {
    while (L->prev) {
        L  = L->prev; 
    }
    return L;
}

static bigint* last(bigint *L, bigint *head_node) {
    while (L->next != head_node){
        L = L->next;
    }
    return L;
}

static bigint *mul_digit(bigint *N, digit x, bigint *tail) {
    if (!N || x > 9 || x < -9)  {
        return NULL;
    }
    else if (!x) {
        return bigint_alloc(0);
    }
    else {
        N->x = abs(N->x);
        bigint* X = mul_digit_pos(N, abs(x), tail);
        return X;
    } 
}

static bigint *mul_digit_pos(bigint *N, digit x, bigint *tail) {
    bigint *X= NULL;
    int val = 0, car = 0; 
    N = tail;
    while (N != NULL || car != 0){
        val = (N ? N->x : 0) * x + car;
        car = val / 10;
        val = val % 10;
        head_insert(&X, val);
        N = N ? N->prev : NULL;
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

static bigint *sum_pos(bigint *N1, bigint *N2, bigint *tail1, bigint *tail2) {
    bigint *N = NULL;
    if (SGN(N1) > 0 && SGN(N2) > 0) {
        int val = 0, car = 0;;
        N1 = last(N1, tail1);
        N2 = last(N2, tail2);
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

static void negate(bigint *N){
    if (N) 
        N->x *= -1;
}
#endif