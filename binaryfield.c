#include <stdio.h>
#include <math.h>
#define WORDSIZE 64
#define M 233
#define T 4
#define EMPTY                                                                          \
    {                                                                                  \
        0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000 \
    }
#define printd(C)                     \
    for (i = 0; i < T; i++)           \
        printf("%llx \t", C[i] >> 1); \
    printf("\n");

typedef unsigned long long poly;
poly *polyadd(poly *A, poly *B);
poly *polymult(poly *A, poly *B);
poly *truncate(poly *C, int j);
poly *inflate(poly *C, poly *Ct, int j);
poly *leftshift(poly *C, int pow);

int main()
{
    int i;
    poly *pC;
    poly A[] = {0x000000000000020A, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000};
    poly B[] = {0x0000000000003011, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000};
    pC = polymult(A, B);
    // printf("%llx", leftshift(1));
    printd(pC);
    // printd(inflate(A, truncate(A, 2), 2));
    // printd(truncate(A, 3));
    return 0;
}

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
    int k, j, i;
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
            for (j = 0; j < T; j++)
                *(B + j) <<= 1;
        // *pC <<= 1;
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