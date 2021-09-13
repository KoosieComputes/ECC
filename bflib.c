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
    poly *C = (poly *)malloc(sizeof(poly) * T);
    mpn_xor_n(C, A, B, T);
    return C;
}

poly *polymult(poly *A, poly *B)
{
    int k, j, i;
    poly *J;
    poly *Bcopy = copyPoly(B, 8, '0');
    poly *C = (poly *)malloc(sizeof(poly) * LT);
    for (i = 0; i < LT; i++)
        C[i] = 0;
    for (k = 0; k < WORDSIZE; k++)
    {
        for (j = 0; j < T; j++)
            if ((*(A + j) >> (k)) % 2 == 1)
                mpn_xor_n(C, C, wordshift(Bcopy, j), LT);
        if (k < (WORDSIZE - 1))
            mpn_lshift(Bcopy, Bcopy, 8, 1);
    }
    reduce(C);
    return C;
}

poly *wordshift(poly *A, short j)
{
    int i;
    poly *TC = (poly *)malloc(sizeof(poly) * LT);

    for (i = 0; i < j; i++)
        TC[i] = 0;
    for (i = j; i < LT; i++)
        TC[i] = *(A + (i - j));
    // for (i = LT - j; i < LT; i++)
    //     TC[i] = 0;
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
    int i;
    poly f[] = RPOLY;
    poly zero[] = EMPTY;
    poly one[] = ONE;
    poly *v = copyPoly(f, 4, '0');
    poly *u = copyPoly(A, 4, '0');
    poly *z1 = copyPoly(B, 4, '0');
    poly *z2 = copyPoly(zero, 4, '0');

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
            mpn_rshift(u, polyadd(u, v), 4, 1);
            z1 = polyadd(z1, z2);
            if (z1[0] % 2 == 0)
                mpn_rshift(z1, z1, 4, 1);
            else
                mpn_rshift(z1, polyadd(z1, f), 4, 1);
        }
    }
    return z1;
}

poly *polysquare(poly *A)
{
    int i, j;
    poly *C = (poly *)malloc(sizeof(poly) * LT);
    for (i = 0; i < LT; i++)
        C[i] = 0;
    unsigned char bytes[8];
    for (i = 0; i < T; i++)
    {
        bytes[0] = A[i];
        bytes[1] = A[i] >> 8;
        bytes[2] = A[i] >> 16;
        bytes[3] = A[i] >> 24;
        bytes[4] = A[i] >> 32;
        bytes[5] = A[i] >> 40;
        bytes[6] = A[i] >> 48;
        bytes[7] = A[i] >> 56;

        C[2 * i] = (MortonTable[bytes[3]] << 48) |
                   (MortonTable[bytes[2]] << 32) |
                   (MortonTable[bytes[1]] << 16) |
                   MortonTable[bytes[0]];
        C[2 * i + 1] = (MortonTable[bytes[7]] << 48) |
                       (MortonTable[bytes[6]] << 32) |
                       (MortonTable[bytes[5]] << 16) |
                       MortonTable[bytes[4]];
    }
    reduce(C);
    return C;
}