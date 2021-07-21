#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include "bflib.h"

poly *copyPoly(poly *A, int len)
{
    int i;
    poly *result = (poly *)malloc(sizeof(poly) * len);
    for (i = 0; i < T; i++)
        result[i] = A[i];
    for (i = T; i < len; i++)
        result[i] = 0;

    return result;
}

poly *polyadd(poly *A, poly *B)
{
    int i;
    static poly C[T];

    // for (i = 0; i < T; i++)
    //     C[i] = *(A + i) ^ *(B + i);
    mpn_xor_n(C, A, B, 4);
    return C;
}

poly *polymult(poly *A, poly *B)
{
    int k, j, i;
    poly *pC;
    poly *Bcopy = copyPoly(B, 8);
    static poly C[] = LEMPTY;
    pC = C;

    // mpn_add_n(pC, truncate(pC, j), B, 4);
    for (k = 0; k < WORDSIZE; k++)
    {
        for (j = 0; j < T; j++)
            if ((*(A + j) >> (k)) % 2 == 1)
                pC = polyadd(truncate(pC, j), Bcopy);
        if (k < (WORDSIZE - 1))
            mpn_lshift(Bcopy, Bcopy, 8, 1);
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

void reduce(poly *A)
{
    int i, Temp;

    for (i = 7; i > 3; i--)
    {
        Temp = A[i];
        A[i - 2] = A[i - 2] ^ (Temp >> 31);
        A[i - 3] = A[i - 3] ^ (Temp << 33) ^ (Temp >> 41);
        A[i - 4] = A[i - 4] ^ (Temp << 23);
    }
    Temp = A[3] >> 41;
    A[0] = A[0] ^ Temp;
    A[1] = A[1] ^ (Temp << 10);
    A[3] = A[3] & 0x1FFFFFFFFFF;
}

// poly *leftshift(poly *C, int pow)
// {
//     int j;
//     poly test = 0x8000000000000000;
//     test <<= pow;
//     return test;
// }