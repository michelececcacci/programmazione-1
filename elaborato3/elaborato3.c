#include <stdio.h>
#include <math.h>

int main(void){
	int input, rem;
	int n = input;
	int size = 1;
	while (n != 0){
		printf("%d", n % 10);
		n /= 10;
		size++;
	}
	printf("%d", pow(10, size) - input);

	printf("\n");
}
