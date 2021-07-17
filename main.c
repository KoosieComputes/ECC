#include <stdio.h>
#include "bflib.h"

int main(int argc, char const *argv[])
{
    int i;
    poly *pC;
    poly A[] = {0x000000000000020A, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000};
    poly B[] = {0x0000000000003011, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000};
    pC = polymult(A, B);
    unsigned long test;
    // printf("%llx", leftshift(1));
    printd(pC);
    // printd(inflate(A, truncate(A, 2), 2));
    // printd(truncate(A, 3));
    printf("ha!!");
    return 0;
}
