#include "math.h"

#define DELTA(a, b, c) b * b - 4 * a * c
#define NUM_OF_ROOTS(a, b, c) ({double delta = DELTA(a, b, c); delta < 0 ? 0 : delta > 0 ? 2 : 1;})
#define ROOT1(a, b, c) (-b + sqrt(DELTA(a, b, c))) / (2 * a)
#define ROOT2(a, b, c) (-b - sqrt(DELTA(a, b, c))) / (2 * a)