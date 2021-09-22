/* tipi usati: char, int, short int, long int, unsigned int, unsigned int, unsigned short int,
unsigned short int, unsgined long int, float double, long int, float double, long double, string, charunsigned short int, unsgined long int, float double, 
long int, float double, long double, string, char*/
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main(void){
    /* INT FINITI */
    int int_var = 5;
    printf("TYPE: int NAME: int_var VALUE: %d MIN: %d, MAX: %d BYTE: %d\n", int_var, INT_MIN, INT_MAX, sizeof(int_var));
    unsigned int unsigned_int_var = 4005;
    printf("TYPE: unsigned int NAME: unsigned_int_var VALUE: %u MIN: %u, MAX: %u BYTE: %d\n", unsigned_int_var, 0, INT_MAX, sizeof(int_var));
    short int short_int_var = 483;
    printf("TYPE: short int NAME: short_int_var VALUE: %d MIN: %d, MAX: %d BYTE: %d\n", short_int_var, SHRT_MIN, SHRT_MAX, sizeof(short_int_var));
    unsigned short int unsigned_short_int_var = 8040;
    printf("TYPE: unsigned int NAME: unsigned_short_int_var VALUE: %hu MIN: %hu, MAX: %hu BYTE: %d\n", unsigned_short_int_var, 0, USHRT_MAX, sizeof(unsigned_short_int_var));
    long int long_int_var = 50000;
    printf("TYPE: long int NAME: long_int_var VALUE: %ld MIN: %+ld, MAX: %+ld BYTE: %d\n", long_int_var, LONG_MIN, LONG_MIN, sizeof(int_var));
    unsigned long int unsigned_long_int_var = 4794290;
    printf("TYPE: long int NAME: long_int_var VALUE: %lu MIN: %lu, MAX: %lu BYTE: %lu\n", unsigned_long_int_var, 0, ULONG_MAX, sizeof(unsigned_long_int_var));
    /* CHAR */
    char char_var = 'a';
    printf("TYPE:  char NAME: char_var VALUE: %d MIN: %d, MAX: %d BYTE: %d\n", char_var, CHAR_MIN, CHAR_MAX, sizeof(char_var)); // IMPORTANTE CHIEDERE SE VOGLIONO VALORE CARATTERE O NUMERICO
    unsigned char unsigned_char_var = 'x';
    printf("TYPE: unsigned char NAME: unsigned_char_var VALUE: %d MIN: %d, MAX: %d BYTE: %d\n", unsigned_char_var, 0, UCHAR_MAX, sizeof(unsigned_char_var));
    /* FLOAT */
    double double_var = 3408.8430;
    printf("TYPE: double  NAME: double_var VALUE: %f MIN: %f, MAX: %f BYTE: %d\n", double_var, DBL_MIN, DBL_MAX, sizeof(double_var));
    long double long_double_var = 759494.473;
    printf("TYPE: long double NAME: long_double_var VALUE: %lf MIN: %d, MAX: %lf BYTE: %d\n", long_double_var, LDBL_MIN, LDBL_MAX, sizeof(long_double_var));
    float float_var = 5.394; 
    printf("TYPE: float NAME: float_var VALUE: %f MIN: %f, MAX: %f BYTE: %d\n", float_var, FLT_MIN, FLT_MAX, sizeof(float_var));

    return 0;
}