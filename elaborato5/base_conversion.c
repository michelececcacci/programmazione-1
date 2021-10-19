#include "base_conversion.h"
#include "stdio.h"
#include <math.h>

/*
* Procedure per stampare un numero n in base b.
* La base b deve essere compresa tra 2 e 16,
* diversamente le procedure non stampano nulla.
*/

static unsigned char convert_to_char(unsigned int n);
static unsigned int get_n_digit(unsigned int n, unsigned int b, unsigned int digit);

void base_conversion_rc(unsigned int n, unsigned int b) {
    if (n > b) {
        base_conversion_rc(n / b, b);
    }
    unsigned char ch = n > 9 ? n - 10 + 'A' : '0' + n;
    printf("%c", convert_to_char(n % b));
}


// should work
void base_conversion_it(unsigned int n, unsigned int b) {
    unsigned char ch;
    unsigned int num, i, digits = (int) (log(n) / log(b));
    printf("digits: %d\n", digits);
    for (i = digits; i >= 0; i--) {
        num = get_n_digit(n, b, i);
        ch = convert_to_char(num);
        printf("%c", ch);
    }
    printf("\n");
}

static unsigned char convert_to_char(unsigned int n) {
    if (n > 9) return n - 10 + 'A';
    return '0' + n;
}

static unsigned int get_n_digit(unsigned int n, unsigned int b, unsigned int digit) {
    int i;
    for (i = 0; i <= digit; i++) {
        n /= b;
    }
    return n % b;
}
