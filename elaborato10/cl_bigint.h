#ifndef BIGINT
#define BIGINT

typedef signed char digit;

typedef struct bigint {
  digit x;
  struct bigint *next;
	struct bigint *prev;
} bigint;


bigint *mul(bigint *N1, bigint *N2);

#endif
