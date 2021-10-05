#include <stdio.h>
#include <math.h>

int main() {
	unsigned int input;
    printf("Inserire un numero: ");
    scanf("%u", &input);

    /* Punto 3 */
    int zeros = 0;
    unsigned int n = input;
    while (n > 0) {
        if(n % 10 == 0) zeros++;
        n /= 10;
    }

    /* Punto 1 */
    unsigned int reversed = 0;
    for (n = input; n > 0; n /= 10) {
        reversed = reversed * 10 + (n % 10);
	}

    /* Punto 2 */
    int size = 0;
    n = input;
    do {
        size++;
        n /= 10;
    } while (n > 0);

    int compl = (int) (pow(10, size) - input);

    /* Output */
    printf("%d", reversed);
    printf(" %d", compl);
    printf(" %d", zeros);

	printf("\n");
}
