#include <stdio.h>
#include <limits.h>
#include "prime.h"

static unsigned short int gcd(unsigned short int m, unsigned short int n);

/* Ritorna 1 se n e' primo, 0 altrimenti. */
unsigned short int is_prime(unsigned short int n) {
    /*
     * Vengono iterati i numeri da 2 a metà del numero stesso,
     * se il resto della divisione tra il numero dato e tutti i numeri iterati
     * è diverso da zero (= non è un multiplo), il numero è primo.
     */
    unsigned short int i = 0;
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
    /*
     * Controllo del valore di n per evitare overflow.
     */
    if (n >= USHRT_MAX) return 0;

    /*
     * primes_found determina la quantità di numeri primi incontrati fin'ora.
     */
    unsigned short int primes_found = 0;

    /*
     * Viene eseguito un loop, a partire da 2, la cui unica condizione di uscita
     * è se la quantità di numeri primi incontrati combacia con n (> usato per sicurezza).
     * La quantità aumenta se il numero iterato è primo.
     */
    unsigned short int i;
    for (i = 2;; i++) {
        if (is_prime(i)) {
            if (primes_found >= n) return i;
            primes_found++;
        }
    }
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
    /*
     * i determina il valore della sequenza corrente.
     */
    static unsigned short int i = -1;

    /*
     * Se la sequenza viene resettata, i torna a 0.
     */
    if (reset) {
        i = 0;
        return 2;
    }
    i++;

    /*
     * Viene calcolato il numero primo corrispondente nella sequenza.
     */
    unsigned short int prime = nth_prime(i);

    /*
     * Viene effettuato un reset se il numero primo è 0, ovvero se ha superato il limite di unsigned short int.
     */
    if (prime == 0) i = 0;
    return prime;
}

/* Ritorna 1 se m e n sono coprimi, 0 altrimenti. */
unsigned short int co_prime(unsigned short int m, unsigned short int n) {
    return gcd(m, n) == 1;
}


static unsigned short int gcd(unsigned short int m, unsigned short int n) {
    /*
     * Usa l' algoritmo di Euclide per computare l'mcd. Statica per limitare il suo uso all' interno di prime.c
     */
    int r;
    while ((r = m % n) > 0) {
        m = n;
        n = r;
    }
    return n;
}