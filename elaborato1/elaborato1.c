/* Tipi usati:
 * int, unsigned int,
 * short int, unsigned short int, * long int, unsigned long int,
 * char, unsigned char,
 * double, long double, float */
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    /* int */
    int int_var = 5092;
    printf("TYPE: %-25s NAME: %-25s VALUE: %-20d MIN: %-20d MAX: %-20d BYTE: %-20ld\n", "int", "int_var", int_var, INT_MIN, INT_MAX, sizeof(int_var));
    unsigned int unsigned_int_var = 4078805;
    printf("TYPE: %-25s NAME: %-25s VALUE: %-20u MIN: %-20u MAX: %-20u BYTE: %-20ld\n", "unsigned int", "unsigned_int_var", unsigned_int_var, 0,  UINT_MAX, sizeof(unsigned_int_var));

    /* short int */
    short int short_int_var = 48;
    printf("TYPE: %-25s NAME: %-25s VALUE: %-20d MIN: %-20hd MAX: %-20hd BYTE: %-20ld\n", "short int", "short_int_var", short_int_var, SHRT_MIN, SHRT_MAX, sizeof(short_int_var));
    unsigned short int unsigned_short_int_var = 8040;
    printf("TYPE: %-25s NAME: %-25s VALUE: %-20d MIN: %-20d MAX: %-20d BYTE: %-20ld\n", "unsigned short int", "unsigned_short_int_var", unsigned_short_int_var, 0, USHRT_MAX, sizeof(unsigned_short_int_var));

    /* long int */
    long int long_int_var = 534008;
    printf("TYPE: %-25s NAME: %-25s VALUE: %-20ld MIN: %-20ld MAX: %-20ld BYTE: %-20ld\n", "long int", "long_int_var", long_int_var, LONG_MIN, LONG_MAX, sizeof(long_int_var));
    unsigned long int unsigned_long_int_var = 4290;
    printf("TYPE: %-25s NAME: %-25s VALUE: %-20lu MIN: %-20d MAX: %-20lu BYTE: %-20ld\n", "unsigned long int", "unsigned_long_int_var", unsigned_long_int_var, 0, ULONG_MAX, sizeof(unsigned_long_int_var));

    /* char */
    char char_var = 'a';
    printf("TYPE: %-25s NAME: %-25s VALUE: %-20d MIN: %-20d MAX: %-20u BYTE: %-20lu\n", "char", "char_var", char_var, CHAR_MIN, CHAR_MAX, sizeof(char_var));
    unsigned char unsigned_char_var = 'x';
    printf("TYPE: %-25s NAME: %-25s VALUE: %-20u MIN: %-20u MAX: %-20u BYTE: %-20lu\n", "unsigned char", "unsigned_char_var", unsigned_char_var, 0, UCHAR_MAX, sizeof(unsigned_char_var));
    signed char signed_char_var = 's';
    printf("TYPE: %-25s NAME: %-25s VALUE: %-20u MIN: %-20d MAX: %-20u BYTE: %-20lu\n", "signed char", "signed_char_var", signed_char_var, SCHAR_MIN, SCHAR_MAX, sizeof(signed_char_var));

    double double_var = 3408.8430;
    printf("TYPE: %-25s NAME: %-25s VALUE: %-20lf MIN: %-20lg MAX: %-20lg BYTE: %-20lu\n", "double", "double_var", double_var, -DBL_MIN, DBL_MAX, sizeof(double_var));
    long double long_double_var = 759494.473;
    printf("TYPE: %-25s NAME: %-25s VALUE: %-20Lg MIN: %-20Lg MAX: %-20Lg BYTE: %-20lu\n", "long double", "long_double_var", long_double_var, -LDBL_MIN, LDBL_MAX, sizeof(long_double_var)); 

    /* float */
    float float_var = 5.394F;
    printf("TYPE: %-25s NAME: %-25s VALUE: %-20g MIN: %-20g MAX: %-20g BYTE: %-20lu\n", "float", "float_var", float_var, -FLT_MIN, FLT_MAX, sizeof(float_var));

    return 0;
}


