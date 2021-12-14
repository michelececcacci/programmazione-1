#include <stdio.h>
#include "selector.h"
#ifdef DL_BIGINT
#include <stdlib.h>
#include "dl_bigint.h"
#include "dl_main.c"

static long int value_from_list(bigint *L);
static bigint* first(bigint *L);
static bigint* last(bigint *L);
static bigint* sum(bigint *N1, bigint *N12);

bigint *mul(bigint *N1, bigint *N2) {
    /* I risultati delle linee delle moltiplicazioni in colonna */
    bigint *line1 = (bigint*) malloc(sizeof(bigint));
    bigint *line2 = (bigint*) malloc(sizeof(bigint));
    /* I numeri dalla fine all'inizio */
    bigint *n1_current = last(N1);
    bigint *n2_current = last(N2);

    int i;
    for (i = 0; n2_current != NULL; i++) {
        /* La cifra del secondo numero */
        digit n2_digit = n2_current->x;
        n2_current = n2_current->prev;
        while (n1_current != NULL) {
            /* La cifra del primo numero */
            digit n1_digit = n1_current->x;
            /* Il nodo attuale */
            bigint *mul = (bigint*) malloc(sizeof(bigint));
            digit result = (digit) (n1_digit * n2_digit);
            bigint *res = i == 0 ? line1 : line2;

            res->x = result;
            res->prev = mul;
            mul->next = res;

            if(i == 0) {
                line1 = mul;
            } else {
                line2 = mul;
            }

            n1_current = n1_current->prev;
        }
        n1_current = last(N1);
    }

    /* La seconda linea è *10 */
    bigint *final_zero = (bigint*) malloc(sizeof(bigint));
    final_zero->x = 0;
    line2 = last(line2);
    final_zero->prev = line2;
    line2->next = final_zero;

    printf("L1 ");
    print(first(line1));
    printf("\n");
    printf("L1 ");
    print(first(line2));
    printf("\n");

    return sum(line1, line2);
}

static bigint* first(bigint *L) {
    bigint *current = L;
    while (1) {
        if(current->prev == NULL) return current;
        current = current->prev;
    }
}

static bigint* last(bigint *L) {
    bigint *current = L;
    while (1) {
        if(current->next == NULL) return current;
        current = current->next;
    }
}

static bigint* sum(bigint *N1, bigint *N2) {
    bigint *result = (bigint*) malloc(sizeof (bigint));
    N1 = last(N1);
    printf("a ");
    print(N1);
    printf("\n");
    N2 = last(N2);
    while (N2 != NULL) {
        digit n2_digit = N2->x;
        while (N1 != NULL) {
            digit n1_digit = N1->x;
            bigint *sum = (bigint*) malloc(sizeof(bigint));
            sum->x = (digit) (n1_digit + n2_digit);
            printf("%d + %d\n", n1_digit, n2_digit);
            result->prev = sum;
            sum->next = result;
            result = sum;
            N1 = N1->prev;
        }
        N2 = N2->prev;
    }
    return result;
}

#endif
