#include "base_conversion.h"
#include "stdio.h"
#include <math.h>

/*
* Procedure per stampare un numero n in base b.
* La base b deve essere compresa tra 2 e 16,
* diversamente le procedure non stampano nulla.
*/

static unsigned char convert_to_char(unsigned int n);
static int get_n_digit(unsigned int n, unsigned int b, int digit);

void base_conversion_rc(unsigned int n, unsigned int b) {
    if (2 <= b && b <= 16) {
        if (n >= b) {
            base_conversion_rc(n / b, b);
        }
        unsigned char ch = n % b > 9 ? n % b  - 10 + 'A' : '0' + n % b;
        printf("%c", ch);
    }
}

void base_conversion_it(unsigned int n, unsigned int b) {
    if (2 <= b && b <= 16) {
        int num, i, digits = (int) (log(b == 2 ? n : n + 1) / log(b));
        for (i = digits - 1; i >= -1; i--) {
            num = get_n_digit(n, b, i);
            printf("%c", convert_to_char(num));
        }
        printf("\n");
    }
}

static unsigned char convert_to_char(unsigned int n) {
    if (n > 9) return n - 10 + 'A';
    return '0' + n;
}

static int get_n_digit(unsigned int n, unsigned int b, int digit) {
    int i;
    for (i = 0; i <= digit; i++) {
        n /= b;
    }
    return n % b;
}
