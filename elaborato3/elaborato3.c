/*NB: test x=0*/


#include <stdio.h>
#include <stdlib.h> 
#include <math.h>


int main() {
	unsigned int x;
	unsigned int res1=0, res2=0, res3=0;

    //INPUT: x must be the input value, do not overwrite it 
	printf("Enter a positive integer: "); scanf("%u", &x);
    //calculate here
    unsigned int n = x;
    /* Punto 1 */
    /* res1 = reversed */
    for (n = x; n > 0; n /= 10) {
        res1 = res1 * 10 + (n % 10);
	}

    /* Punto 2 */
    int size= 0; /* res2 = reversed*/
    n = x;
    do {
        size++;
        n /= 10;
    } while (n > 0);

    /* Punto 3 */
    /* res3 = zeros */
    n = x;
    if (x > 0)
    {
        while (n > 0) 
        {
            if((n % 10)== 0) 
            {
                res3++;
            }
            n /= 10;
        }
    }
    else 
        res3 = 1;

    res2 = (int) (pow(10, size) - x);

    //do NOT add code after this point
    //OUTPUT
	printf("Actual result:\n");
	printf("%u %u %u\n", res1, res2, res3);
    
    //DON'T REMOVE from submittion
    #ifdef EVAL
        eval(x,res1, res2, res3);
    #endif
	return 0;
}