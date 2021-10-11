#include <stdio.h>
#include "prime.h"

int main() {
    printf("%d\n", succ_prime(0));
    printf("%d\n", succ_prime(0));
    printf("%d\n", succ_prime(0));
    printf("%d\n", succ_prime(1));
    printf("%d\n", succ_prime(0));
    printf("%d\n", succ_prime(0));
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
unsigned short int nth_prime(unsigned short int n) {
    int primes_found = 0;
    int i;
    for (i = 2;; i++) {
        if(is_prime(i)) {
            if(primes_found >= n) break;
            primes_found++;
        }
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
unsigned short int succ_prime(int reset) {
    static int i = -1;
    if(reset) {
        i = 0;
        return 2;
    }
    i++;
    return nth_prime(i);
}

/* Ritorna 1 se m e n sono coprimi, 0 altrimenti. */
unsigned short int co_prime(unsigned short int m,
                            unsigned short int n) {}
