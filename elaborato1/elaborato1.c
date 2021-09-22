/* Tipi usati:
 * int, unsigned int,
 * short int, unsigned short int,
 * long int, unsigned long int,
 * long long, unsigned long long,
 * char, unsigned char,
 * double, long double, float */
#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    /* int */
    int int_var = 5092;
    printf("TYPE: int NAME: int_var VALUE: %d MIN: %d, MAX: %d BYTE: %lu\n", int_var, INT_MIN, INT_MAX, sizeof(int_var));
    unsigned int unsigned_int_var = 4078805;
    printf("TYPE: unsigned int NAME: unsigned_int_var VALUE: %u MIN: %u, MAX: %u BYTE: %lu\n", unsigned_int_var, 0, INT_MAX, sizeof(int_var));

    /* short int */
    short int short_int_var = 48;
    printf("TYPE: short int NAME: short_int_var VALUE: %d MIN: %d, MAX: %d BYTE: %lu\n", short_int_var, SHRT_MIN, SHRT_MAX, sizeof(short_int_var));
    unsigned short int unsigned_short_int_var = 8040;
    printf("TYPE: unsigned int NAME: unsigned_short_int_var VALUE: %hu MIN: %d, MAX: %d BYTE: %lu\n", unsigned_short_int_var, 0, USHRT_MAX, sizeof(unsigned_short_int_var));

    /* long int */
    long int long_int_var = 50000;
    printf("TYPE: long int NAME: long_int_var VALUE: %ld MIN: %ld, MAX: %ld BYTE: %lu\n", long_int_var, LONG_MIN, LONG_MAX, sizeof(int_var));
    unsigned long int unsigned_long_int_var = 4794290;
    printf("TYPE: unsigned long int NAME: long_int_var VALUE: %lu MIN: %d, MAX: %lu BYTE: %lu\n", unsigned_long_int_var, 0, ULONG_MAX, sizeof(unsigned_long_int_var));

    /* long long */
    long long long_long_var = 5045009102;
    printf("TYPE: long long NAME: long_long_var VALUE: %lld MIN: %lld, MAX: %lld BYTE: %lu\n", long_long_var, LLONG_MIN, LLONG_MAX, sizeof(long_long_var));
    unsigned long long unsigned_long_long_var = 908190120402919;
    printf("TYPE: unsigned long long NAME: unsigned_long_long_var VALUE: %llu MIN: %d, MAX: %llu BYTE: %lu\n", unsigned_long_long_var, 0, ULLONG_MAX, sizeof(unsigned_long_long_var));

    /* char */
    char char_var = 'a';
    printf("TYPE: char NAME: char_var VALUE: %d MIN: %d, MAX: %d BYTE: %lu\n", char_var, CHAR_MIN, CHAR_MAX, sizeof(char_var));
    unsigned char unsigned_char_var = 'x';
    printf("TYPE: unsigned char NAME: unsigned_char_var VALUE: %d MIN: %d, MAX: %d BYTE: %lu\n", unsigned_char_var, 0, UCHAR_MAX, sizeof(unsigned_char_var));

    /* double */
    double double_var = 3408.8430;
    printf("TYPE: double NAME: double_var VALUE: %f MIN: %f, MAX: %f BYTE: %lu\n", double_var, DBL_MIN, DBL_MAX, sizeof(double_var));
    long double long_double_var = 759494.473;
    printf("TYPE: long double NAME: long_double_var VALUE: %Lf MIN: %Lf, MAX: %Lf BYTE: %lu\n", long_double_var, LDBL_MIN, LDBL_MAX, sizeof(long_double_var));

    /* float */
    float float_var = 5.394F;
    printf("TYPE: float NAME: float_var VALUE: %f MIN: %f, MAX: %f BYTE: %lu\n", float_var, FLT_MIN, FLT_MAX, sizeof(float_var));

    return 0;
}
