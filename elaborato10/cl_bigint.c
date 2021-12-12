#include "selector.h"
#ifdef CL_BIGINT
#include <stdlib.h>
#include "cl_bigint.h"



static void reverse_circular(struct bigint *L);

bigint *mul(bigint *N1, bigint *N2) {
	return NULL;
}
static void reverse_circular(struct bigint *L) {
	struct bigint *tmp = NULL, *current = L;
	while (current !=  L) {
		tmp = current->prev;	
		current->prev = current->next;
		current->next = tmp;
		current = current->prev;
	}
	if (tmp != NULL) L = tmp->prev;
}

#endif