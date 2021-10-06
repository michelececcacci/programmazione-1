#include <stdio.h>
#include <math.h>
int main() {
	unsigned int x;
    printf("Inserire un numero: ");
    scanf("%u", &x);

    unsigned int n = x;
    /* Punto 1 */
    unsigned int reversed = 0;
    for (n = x; n > 0; n /= 10) {
        reversed = reversed * 10 + (n % 10);
	}

    /* Punto 2 */
    int size = 0;
    n = x;
    do {
        size++;
        n /= 10;
    } while (n > 0);

    /* Punto 3 */
    int zeros = 0;
    n = x;
    while (n > 0) {
        if((n % 10)== 0) {
            zeros++;
        }
        n /= 10;
    }


    int compl = (int) (pow(10, size) - x);

    /* Output */
    printf("%d", reversed);
    printf(" %d", compl);
    printf(" %d", zeros);

	printf("\n");
}
