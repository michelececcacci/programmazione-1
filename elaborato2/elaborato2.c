#include <stdio.h>
#include <math.h>

#define DELTA(a, b, c) b * b - 4 * a * c;
#define NUM_OF_ROOTS(a, b, c) ({double delta = DELTA(a, b, c); delta < 0 ? 0 : delta > 0 ? 2 : 1;})

int main() {
    printf("%d", NUM_OF_ROOTS(1, 2, 3));
    printf("%d", NUM_OF_ROOTS(1, -2, -1));
}