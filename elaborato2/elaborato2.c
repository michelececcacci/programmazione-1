#include <stdio.h>
#include "quadratic_eq.h"

int main() {
    printf("%d", NUM_OF_ROOTS(1, 2, 3));
    printf("%d", NUM_OF_ROOTS(1, -2, -1));
    printf("\n");
    printf("%f\n", ROOT1(1, -2, -1));
    printf("%f\n", ROOT2(1, -2, -1));
}