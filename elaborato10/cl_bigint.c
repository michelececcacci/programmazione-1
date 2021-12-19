#include "selector.h"

#ifdef CL_BIGINT

#include <stdlib.h>
#include "dl_bigint.h"

static void negate(bigint *n);
static bigint *last(bigint *N);
static int exists(bigint *n);
static int head_delete(bigint **N);
static int bigint_delete(bigint *N);
static bigint *bigint_alloc(digit x);
static digit get_sign(bigint *n1, bigint *n2);
static int head_insert(bigint **N, digit x);
static int bigint_insert(bigint *N, digit x);
static int shift(bigint **n, digit x, bigint *tail);
static void remove_leading_zeros(bigint **N);

bigint *mul(bigint *N1, bigint *N2) {
    if (N1 == NULL || N2 == NULL)
        return NULL;
    if (!exists(N1) || !exists(N2))
        return NULL;

    bigint *res = bigint_alloc(0);
    bigint *tail1 = last(N1);
    bigint *tail2 = last(N2);
    bigint *_tailRes = last(res);
    bigint *tailRes = last(res);
    digit sign = get_sign(N1, N2);
    negate(N1);
    negate(N2);

    N1 = tail1;
    do {
        N2 = tail2;
        res = tailRes;
        do {
            digit result = (digit) ((N1->x) * (N2->x));
            res->x += result;
            digit carry = res->x / 10;
            res->x %= 10;
            shift(&res, carry, _tailRes);
            N2 = N2->prev;
        } while (N2 != tail2);

        N1 = N1->prev;
        tailRes = tailRes->prev;
    } while (N1 != tail1);

    remove_leading_zeros(&res);
    res->x *= sign;
    return res;
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
    if (N == NULL) {
        return 1;
    } else {
        bigint *prv = N->prev, *nxt = N->next;
        nxt->prev = prv;
        prv->next = nxt;
        free(N);
        return 0;
    }
}

static int bigint_insert(bigint *N, digit x) {
    if (N == NULL) {
        return 1;
    } else {
        bigint *tmp = bigint_alloc(x), *next = N->next, *prev = N;
        if (tmp != NULL) {
            tmp->prev = prev;
            tmp->next = next;
            prev->next = tmp;
            next->prev = tmp;
        }
        return tmp == NULL;
    }
}

static int head_insert(bigint **N, digit x) {
    if (*N == NULL) return (*N = bigint_alloc(x)) == NULL;
    else if (bigint_insert((*N)->prev, x) == 1) return 1;
    else return (*N = (*N)->prev) == NULL;
}

static int head_delete(bigint **N) {
    if (*N == NULL) {
        return 1;
    } else if (*N == (*N)->next) {
        free(*N);
        *N = NULL;
        return 0;
    } else {
        *N = (*N)->next;
        return bigint_delete((*N)->prev);
    }
}

static void remove_leading_zeros(bigint **N) {
    if (N != NULL && *N != NULL) {
        while ((*N)->x == 0 && *N != (*N)->next)
            head_delete(N);
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

static void negate(bigint *n) {
    if (n->x < 0) n->x *= -1;
}

static digit get_sign(bigint *n1, bigint *n2) {
    if (n1->x * n2->x < 0)
        return -1;
    else
        return 1;
}

static int exists(bigint *n) {
    if (n->x > 9 || n->x < -9) return 0;
    bigint *next;
    for (next = n->next; next != n; next = next->next) {
        if (next->x > 9 || next->x < 0)
            return 0;
    }
    return 1;
}

#endif
