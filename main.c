#include <stdio.h>
#include <gmp.h>
#include "bflib.h"

int main(int argc, char const *argv[])
{
    int i;
    poly *pC;
    poly A[] = {0x20A, 0, 0, 0};
    poly B[] = {0x3011, 0, 0, 0};
    poly C[] = {0x0000000004aee4ea, 0x000000a533d70a81, 0x7f870103204f8423, 0x0000000000000000};
    pC = polymult(B, C);
    poly *Acopy = copyPoly(A, 4);
    // mpn_rshift(pC, pC, 4, 1);
    // printd(pC);
    printd(Acopy);
    return 0;
}
