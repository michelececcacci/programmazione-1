/* Le variabili nelle macro sono state "protette" tra parentesi. */

/* La macro DELTA ottiene il delta (b^2 - 4ac) da a, b e c */
#define DELTA(a, b, c) ((b) * (b) - 4 * (a) * (c))
/* La macro ROOT ottiene il risultato dell'equazione di secondo grado ((-b +- sqrt(delta)) / 2a)
 * da a, b, c e "sign", che può essere 1 per il risultato maggiore o -1 per quello minore. */
#define ROOT(a, b, c, sign) ((-(b)) + sign * sqrt(DELTA(a, b, c))) / (2 * (a))
/* La macro F(x) calcola il valore della y della funzione ax^2 + bx + c in un punto x*/
#define F(x, a, b, c) (pow(x, 2) * (a) + (x) * (b) + (c))

/* Macro della consegna */
#define NUM_OF_ROOTS(a, b, c) (DELTA(a, b, c) < 0 ? 0 : DELTA(a, b, c) > 0 ? 2 : 1)
#define ROOT1(a, b, c) ((a) > 0 ? ROOT(a, b, c, 1) : ROOT(a, b, c, -1))
#define ROOT2(a, b, c) ((a) > 0 ? ROOT(a, b, c, -1) : ROOT(a, b, c, 1))
#define EXTREME_POINT(a, b, c) (-(b) / (2 * (a)))
/* Se un punto vicino all'estremo ha y maggiore del valore dell'estremo, allora il punto è un minimo */
#define MAXIMUM_POINT(a, b, c)  F(EXTREME_POINT(a, b, c), a, b, c) > F(EXTREME_POINT(a, b, c) + 0.1, a, b, c)
