#include <stdio.h>
#include "selector.h"
#ifdef DL_BIGINT
#include <stdlib.h>
#include "dl_bigint.h"

static long int value_from_list(bigint *L);
static bigint* last(bigint *L);

bigint *mul(bigint *N1, bigint *N2) {
    bigint *n1_current = last(N1);
    bigint *n2_current = last(N2);
    while (n2_current != NULL) {
        int n2_digit = (int) n2_current->x;
        n2_current = n2_current->prev;
        while (n1_current != NULL) {
            int n1_digit = (int) n1_current->x;
            printf("N1 %d N2 %d\n", n1_digit, n2_digit);
            n1_current = n1_current->prev;
        }
        n1_current = last(N1);
    }
    return NULL;
}

static bigint* last(bigint *L) {
    bigint *current = L;
    while (1) {
        if(current->next == NULL) return current;
        current = current->next;
    }
}

#endif
