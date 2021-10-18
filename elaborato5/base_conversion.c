#include "base_conversion.h"
#include "stdio.h"
#include <math.h>

// works, but in least singificant from most significant
void base_conversion_rc(unsigned int n, unsigned int b) {
    if (n == 0) return; 
    if (n > 0)  
    {
        base_conversion_rc(n / b, b);
        printf("%d", n % b);
    }

}


// not working, prints number backwards
void base_conversion_it(unsigned int n, unsigned int b) {
    int digits;
    int n1 = n;
    for (digits = 0; n1 > 0; digits++ ){
        n1 /= b;
    }
    printf("number of digits in new base: %d\n", digits);

    return;
} 


char convert_to_base(int n){
    char ch;
    switch (n){
        case 0: ch = '0'; break;
        case 1: ch = '1'; break;
        case 2: ch = '2'; break;
        case 3: ch = '3'; break;
        case 4: ch = '4'; break;
        case 5: ch = '5'; break;
        case 6: ch = '6'; break;
        case 7: ch = '7'; break;
        case 8: ch = '8'; break;
        case 9: ch = '9'; break;
        case 10: ch = 'A'; break;
        case 11: ch = 'B'; break;
        case 12: ch = 'C'; break;
        case 13: ch = 'D'; break;
        case 14: ch = 'E'; break;
        case 15: ch = 'F'; break;
    }
    return ch;
}