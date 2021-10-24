#include "base_conversion.h"
#include <stdio.h>
#include <math.h>

/*
* Procedure per stampare un numero n in base b.
* La base b deve essere compresa tra 2 e 16,
* diversamente le procedure non stampano nulla.
*/

static int get_n_digit(unsigned int n, unsigned int b, int digit);

/* Tratta le funzioni come se fossero  uno stack, lasciando cosi la chiamata alla funzione che ha cifra di rilevanza piu bassa "aperta
stampandola alla fine. In questo modo viene raggiutnto il risultato richiesto*/
void base_conversion_rc(unsigned int n, unsigned int b) {
    if (2 <= b && b <= 16) {
        if (n >= b) {
            base_conversion_rc(n / b, b);
        }
        printf("%X", n % b);
    }
}

/* Usa un loop per stampare in ordine le cifre in ordine richiesto, che vengono prese con get_n_digit()*/
void base_conversion_it(unsigned int n, unsigned int b) {
    if (n == 0){
        printf("0");
        return;
    }
    if (2 <= b && b <= 16) {
        int num, i, digits = (int) (log(b == 2 ? n : n + 1) / log(b));
        for (i = digits - 1; i >= -1; i--) {
            num = get_n_digit(n, b, i);
            printf("%X", num);
        }
        printf("\n");
    }
}

/* prende la cifra n del numero, usando il metodo delle divisoni successive. Usato nella funzione iterativa*/
static int get_n_digit(unsigned int n, unsigned int b, int digit) {
    int i;
    for (i = 0; i <= digit; i++) {
        n /= b;
    }
    return n % b;
}
