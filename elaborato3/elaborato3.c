#include <stdio.h>
#include <math.h>

int main() {
	unsigned int input;
    printf("Inserire un numero: ");
    scanf("%u", &input);

    int reversed = 0;
	int size = 0;
    int zeros = 0;

	for (int n = input; n != 0; n /= 10) {
        int rem = n % 10;
        reversed = reversed * 10 + rem;
        if(rem == 0) zeros++;
		size++;
	}

    printf("%d", reversed);
    printf(" %d", (int) pow(10, size) - input);
    printf(" %d", zeros);

	printf("\n");
}
