#include <stdio.h>
#include "prime.h"

int main() {
    printf("%d", is_prime(4));
    printf("%d", is_prime(5));
    printf("%d", is_prime(7));
    return 0;
}

/* Ritorna 1 se n e' primo, 0 altrimenti. */
unsigned short int is_prime(unsigned short int n) {
    int i = 0;
    for (i = 2; i <= n / 2; i++) {
        if (n % i == 0) {
            return 0;
        }
    }
    return 1;
}

/*
 * Ritorna l'n-esimo primo, contando a partire da 0.
 *
 * Se il numero e' troppo grande per essere rappresentato
 * con un unsigned short int, ritorna 0.
 */
// TODO NON CAPISCO PERCHE MA CODEBOARD PRENDE 0 COME INPUT
unsigned short int nth_prime(unsigned short int n) {
    int i = 0;
    while (i < n) {
        if (is_prime(i))
            i++;
    }
    return i;
}

/* Ritorna la successione di numeri primi.
 * La prima chiamata ritorna 2, la seconda 3, ecc.
 * 
 * Se il parametro reset e' diverso da 0, allora la
 * successione viene resettata e la funzione ritorna 2. 
 * Diversamente, la funzione ritorna il primo successivo
 * a quello ritornato alla chiamata precedente.
 *
 * Se il primo successivo e' troppo grande per essere
 * rappresentato con un unsigned short int, la funzione
 * ritorna 0 e la seccessione viene resettata.
 */
unsigned short int succ_prime(int reset) {}

/* Ritorna 1 se m e n sono coprimi, 0 altrimenti. */
unsigned short int co_prime(unsigned short int m,
                            unsigned short int n) {}
