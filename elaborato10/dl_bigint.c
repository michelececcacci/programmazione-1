#include <stdio.h>
#include "selector.h"
#ifdef DL_BIGINT
#include <stdlib.h>
#include "dl_bigint.h"
#include "dl_main.c"

static long int value_from_list(bigint *L);
static bigint* first(bigint *L);
static bigint* last(bigint *L);

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
        int n2_digit = (int) n2_current->x;
        n2_current = n2_current->prev;
        while (n1_current != NULL) {
            /* La cifra del primo numero */
            int n1_digit = (int) n1_current->x;
            /* Il nodo attuale */
            bigint *mul = (bigint*) malloc(sizeof(bigint));
            signed char result = (signed char) (n1_digit * n2_digit);
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

    print(first(line1));
    printf("\n");
    print(first(line2));
    printf("\n");

    return NULL;
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

#endif
