#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <gmp.h>
#include "bflib.h"

int isequal(poly *A, poly *B, short len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        if (A[i] != B[i])
            return 0;
    }
    return 1;
}

void swapArray(poly *a, poly *b, short n)
{
    for (int i = 0; i < n; i++)
    {
        poly tmp = a[i];
        a[i] = b[i];
        b[i] = tmp;
    }
}

poly *copyPoly(poly *A, short len, char size)
{
    int i;
    poly *result = (poly *)malloc(sizeof(poly) * len);
    for (i = 0; i < T; i++)
        result[i] = A[i];
    if (size > '0')
    {
        for (i = T; i < len; i++)
            result[i] = A[i];
    }
    else
    {
        for (i = T; i < len; i++)
            result[i] = 0;
    }
    return result;
}

poly *polyadd(poly *A, poly *B)
{
    int i;
    static poly C[T];
    mpn_xor_n(C, A, B, 4);
    return C;
}

poly *polymult(poly *A, poly *B)
{
    int k, j, i;
    poly *pC;
    poly *Bcopy = copyPoly(B, 8, '0');
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

poly *truncate(poly *A, short j)
{
    int i;
    static poly TC[T];

    for (i = 0; i < j; i++)
        TC[i] = 0;
    for (i = j; i < T; i++)
        TC[i] = *(A + i);
    return TC;
}

void reduce(poly *A)
{
    int i;
    poly Temp;

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

poly *polydivide(poly *A, poly *B)
{
    poly f[] = RPOLY;
    poly zero[] = EMPTY;
    poly one[] = ONE;
    poly *v = f;
    poly *u = copyPoly(A, 4, '0');
    poly *z1 = copyPoly(B, 4, '0');
    poly *z2 = zero;

    while (!(isequal(u, one, 4)))
    {
        if (u[0] % 2 == 0)
        {
            mpn_rshift(u, u, 4, 1);
            if (z1[0] % 2 == 0)
                mpn_rshift(z1, z1, 4, 1);
            else
                mpn_rshift(z1, polyadd(z1, f), 4, 1);
        }
        else
        {
            if (mpn_cmp(v, u, 4) > 0)
            {
                swapArray(u, v, 4);
                swapArray(z1, z2, 4);
            }
            mpn_rshift(u, polyadd(u, f), 4, 1);
            z1 = polyadd(z1, z2);
            if (z1[0] % 2 == 0)
                mpn_rshift(z1, z1, 4, 1);
            else
                mpn_rshift(z1, polyadd(z1, f), 4, 1);
        }
    }
    return z1;
}
