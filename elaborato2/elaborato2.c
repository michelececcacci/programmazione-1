#include <stdio.h>
#include "quadratic_eq.h"
#include <math.h>

int main() {
    printf("%d ", NUM_OF_ROOTS(0.5,-2.0,1.5)); /* 2 */
    printf("%d ", NUM_OF_ROOTS(0.5,-2.0,2.0)); /* 1 */
    printf("%d\n", NUM_OF_ROOTS(-0.5,-2.0,-3.0));  /* 1 */

    printf("%f ", ROOT1(0.5,-2.0,1.5)); /* 3 */
    printf("%f\n", ROOT2(0.5,-2.0,1.5)); /* 1.0 */
    printf("%+f\n", EXTREME_POINT(0.5, -2.0, 1.5));  /* 2.0 */
    printf("%i\n", MAXIMUM_POINT(0.5, -2.0, 1.5));  /* 0 */
}