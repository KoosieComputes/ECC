#include <stdio.h>
#include <math.h>
#include <gmp.h>
#include "bflib.h"

poly *polyadd(poly *A, poly *B)
{
    int i;
    static poly C[T];

    for (i = 0; i < T; i++)
        C[i] = *(A + i) ^ *(B + i);
    return C;
}

poly *polymult(poly *A, poly *B)
{
    int k, j, i, r;
    poly *pC;
    static poly C[T];
    for (i = 0; i < T; i++)
        C[i] = 0;
    pC = C;

    for (k = 0; k < WORDSIZE; k++)
    {
        for (j = 0; j < T; j++)
            if ((*(A + j) >> (k - 1)) % 2 == 1)
                pC = polyadd(truncate(pC, j), B);
        if (k < (WORDSIZE - 1))
            r = mpn_lshift(B, B, 4, 1);
    }
    return pC;
}

poly *truncate(poly *C, int j)
{
    int i;
    static poly TC[T];

    for (i = 0; i < j; i++)
        TC[i] = 0;
    for (i = j; i < T; i++)
        TC[i] = *(C + i);
    return TC;
}

// poly *leftshift(poly *C, int pow)
// {
//     int j;
//     poly test = 0x8000000000000000;
//     test <<= pow;
//     return test;
// }