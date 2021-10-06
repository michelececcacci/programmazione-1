#include <stdio.h>
#include <math.h>
int main() {
	unsigned int x;
    printf("Inserire un numero: ");
    scanf("%u", &x);

    unsigned int n = x;
    /* Punto 1 */
    unsigned int res1 = 0; /* res1 = reversed */
    for (n = x; n > 0; n /= 10) {
        res1 = res1 * 10 + (n % 10);
	}

    /* Punto 2 */
    int res2 = 0; /* res2 = size */
    n = x;
    do {
        res2++;
        n /= 10;
    } while (n > 0);

    /* Punto 3 */
    int res3 = 0; /* res3 = zeros */
    n = x;
    while (n > 0) {
        if((n % 10)== 0) {
            res3++;
        }
        n /= 10;
    }


    int compl = (int) (pow(10, res2) - x);

    /* Output */
    printf("%d", res1);
    printf(" %d", compl);
    printf(" %d", res3);

	printf("\n");
}
