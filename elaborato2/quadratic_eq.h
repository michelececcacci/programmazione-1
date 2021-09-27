#define DELTA(a, b, c) b * b - 4 * a * c;
#define NUM_OF_ROOTS(a, b, c) ({double delta = DELTA(a, b, c); delta < 0 ? 0 : delta > 0 ? 2 : 1;})