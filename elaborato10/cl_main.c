#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "selector.h"
#ifdef CL_BIGINT

#include "cl_bigint.h"

#define C2N(c) ((c)-'0')

static bigint *bigint_alloc(digit x) {
	bigint *tmp = (bigint *)malloc(sizeof(bigint));

	if(tmp != NULL) {
		tmp->x    = x;
		tmp->next = tmp;
		tmp->prev = tmp;
	}
	return tmp;
}

static int bigint_delete(bigint *N) {
	if(N == NULL) {
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
	if(N == NULL) {
		return 1;
	} else {
		bigint *tmp = bigint_alloc(x), *nxt = N->next, *prv = N;
		if(tmp != NULL) {
			tmp->prev = prv;
			tmp->next = nxt;
			prv->next = tmp;
			nxt->prev = tmp;
		}
		return tmp == NULL;
	}
}

static int head_insert(bigint **N, digit x) {
	if(N == NULL)
		return 1;
	else if(*N == NULL)
		return (*N = bigint_alloc(x)) == NULL;
	else if (bigint_insert((*N)->prev,x) == 1)
		return 1;
	else
		return (*N = (*N)->prev) == NULL;
}

static int head_delete(bigint **N) {
	if(N == NULL || *N == NULL) {
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
	if(N != NULL && *N != NULL) {
		while((*N)->x == 0 && *N != (*N)->next)
			head_delete(N);
	}
}


static int well_formed_str(char *s) {
	if(s == NULL || *s == '\0') {
		return 0;
	} else {
		if(*s == '-') s++;
		if(*s == '\0')
			return 0;
		while(*s != '\0') {
			if(!isdigit(*s))
				return 0;
			s++;
		}
		return 1;
	}
}

static bigint *str2bigint_rec(char *s) {
	bigint *N = NULL;

	if(*s != '\0') {
		N = str2bigint_rec(s+1);
		head_insert(&N,C2N(*s));
	}
	return N;
}

static bigint *str2bigint(char *s) {
	bigint *N = NULL;

	if(well_formed_str(s)) {
		int sgn = 1;

		if(s[0]=='-') {
			sgn = -1;
			s++;
		}
		N = str2bigint_rec(s);
		remove_leading_zeros(&N);
		if(N != NULL && sgn == -1)
			N->x = -N->x;
	}

	return N;
}

void print(bigint *N) {
	if(N == NULL) {
		printf("NaN");
	} else {
		bigint *tmp = N;

		do {
			printf("%d",tmp->x);
			tmp = tmp->next;
		} while(tmp != N);
	}
}



static void sprint(char* s, bigint* N) {
	if (N == NULL) {
		sprintf(s, "NaN");
	}
	else {
		int cont = 0;
		bigint *tmp = N;
		do {
			sprintf(s+cont, "%d", tmp->x);
			if (tmp->x < 0) cont++;
			tmp = tmp->next;
			cont++;
		} while(tmp != N);
		sprintf(s + cont, "%c",'\0');
	}
		
	
}




/*int interactive_main() {
	bigint* N1, * N2, * N;
	char V1[255];
	char V2[255];

	scanf("%s%s", V1, V2);

	N1 = str2bigint(V1);
	N2 = str2bigint(V2);

	N = mul(N1, N2);

	print(N); printf("\n");
	bigint_delete(N);
	bigint_delete(N1);
	bigint_delete(N2);
	return 0;
}

*/
#define TEST
#define NTEST 10
int test_main() {
	char V1[NTEST][255] = { "1113" , "999987" , "67839000", "0", "100000000000000000" ,"-1","-3479672927592","-999989999999999999999","-5555","d"};
	char V2[NTEST][255] = { "7618113" , "10287" , "102", "11222199283847563", "78564","123","-999987999909999999","-999989999999999999999","444637","d" };
	char expris[NTEST][255] = { "8478959769" , "10286866269" , "6919578000", "0", "7856400000000000000000","-123","3479631171203698329037047072408","999980000099999999998000020000000000000001" ,"-2469958535","NaN"};
	char actris[255];
	int i, err, errori = 0;

	bigint* N1, * N2, * N;

	for (i = 0; i < NTEST; i++) {
		printf("Test %d: %s*%s=", i, V1[i], V2[i]);
		N1 = str2bigint(V1[i]);
		N2 = str2bigint(V2[i]);
		N = mul(N1, N2);
		print(N);
		sprint(actris, N);
		err = (strcmp(expris[i], actris) == 0 ? 0 : 1);
		if (err) {
			printf(" ERRORE: %s", expris[i]);
			errori++;
		}
		printf("\n");
		bigint_delete(N);
		bigint_delete(N1);
		bigint_delete(N2);
	}


	return errori;
}

int main(int argc, char* argv[]) {

	int errori;
	
#ifdef TEST
	
	errori = test_main();
	printf("\nErrori: %d\n", errori);
#else

	
#endif

#ifdef OUTFILE
	FILE* fp;
	//fclose(fp);
	fp = fopen(argv[2], "a");

	fprintf(fp, "%s\tDL err=%d\t", argv[1], errori);
	fclose(fp);
#endif

	return 0;
}



#endif
