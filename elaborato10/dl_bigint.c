#include <stdio.h>
#include "selector.h"
#ifdef DL_BIGINT
#include <stdlib.h>
#include "dl_bigint.h"

void reverse_doubly(bigint *L);
static long int value_from_list(bigint * L);

bigint *mul(bigint *N1, bigint *N2) {
	reverse_doubly(N1);
	reverse_doubly(N2);
}

void reverse_doubly(bigint *L) {
	struct bigint *tmp = NULL, *current = L;
	while (current !=  NULL) {
		tmp = current->prev;	
		current->prev = current->next;
		current->next = tmp;
		current = current->prev;
	}
	if (tmp != NULL) L = tmp->prev;
}


#endif
