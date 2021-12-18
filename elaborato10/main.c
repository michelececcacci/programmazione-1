#include <stdio.h>
#include "cl_main.c"
#include "cl_bigint.h"

int main() {
    bigint *n1 = str2bigint("12");
    bigint *n2 = str2bigint("12");
    bigint *res = mul(n1, n2);
    print(res);
    return 0;
}
