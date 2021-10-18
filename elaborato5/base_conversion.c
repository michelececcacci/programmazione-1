#include "base_conversion.h"
#include "stdio.h"
#include <math.h>

/*
* Procedure per stampare un numero n in base b.
* La base b deve essere compresa tra 2 e 16,
* diversamente le procedure non stampano nulla.
*/

int main() {
    base_conversion_it(123456, 12);
    base_conversion_rc(123456, 12);
    return 0;
}

static char convert_to_char(unsigned int n);

// works, but in least singificant from most significant
void base_conversion_rc(unsigned int n, unsigned int b) {
    if (n == 0) return;
    if (n > 0) {
        base_conversion_rc(n / b, b);
        printf("%c", convert_to_char(n % b));
    }
}


// not working, prints number backwards
void base_conversion_it(unsigned int n, unsigned int b) {
    int digits;
    for (digits = 0; n > 0; digits++) {
        n /= b;
        printf("%c", convert_to_char(n % b));
    }
    printf("\n");
}

static char convert_to_char(unsigned int n) {
    switch (n) {
        case 0:
            return '0';
        case 1:
            return '1';
        case 2:
            return '2';
        case 3:
            return '3';
        case 4:
            return '4';
        case 5:
            return '5';
        case 6:
            return '6';
        case 7:
            return '7';
        case 8:
            return '8';
        case 9:
            return '9';
        case 10:
            return 'A';
        case 11:
            return 'B';
        case 12:
            return 'C';
        case 13:
            return 'D';
        case 14:
            return 'E';
        case 15:
            return 'F';
    }
}