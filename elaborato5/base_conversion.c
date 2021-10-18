#include "base_conversion.h"
#include "stdio.h"
#include <math.h>

/*
* Procedure per stampare un numero n in base b.
* La base b deve essere compresa tra 2 e 16,
* diversamente le procedure non stampano nulla.
*/

static char convert_to_char(unsigned int n);

// works, but prints a 0 at the beginning
void base_conversion_rc(unsigned int n, unsigned int b) { 
    if (n > b)
        base_conversion_rc(n / b, b); 
    char ch;
    if (n > 9)
        ch = n - 10 + 'A';
    else 
        ch = '0' + n ;
    printf("%c", convert_to_char(n % b));
}


// not working, prints number backwards
void base_conversion_it(unsigned int n, unsigned int b) {
    char ch;
    int num, i, digits = (log(n) /log(b));
    printf("digits: %d\n", digits);
    // should print every digit of the other base in reverse . how?
    for (i = digits; i > 0; i--){
        ch = 0;
        ch = convert_to_char(num);
        printf("%c", ch);
    }
    printf("\n");
}

static char convert_to_char(unsigned int n) {
    if (n > 9)
        return n - 10 + 'A';
    return '0' + n ;
}