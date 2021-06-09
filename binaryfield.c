#include <stdio.h>
#include <math.h>
#define WORDSIZE 64
#define M 233
#define T 4
#define EMPTY                                                                          \
    {                                                                                  \
        0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000 \
    }
#define printd(C)           \
    for (i = 0; i < T; i++) \
        printf("%llx \t", C[i]);

typedef unsigned long long poly;
poly *polyadd(poly *A, poly *B);
poly *polymult(poly *A, poly *B);
poly *truncate(poly *C, int j);
poly *inflate(poly *C, poly *Ct, int j);

int main()
{
    int i;
    poly *pC;
    poly A[] = {0x0000000000000001, 0x0000000000000002, 0x0000000000000004, 0x0000000000000006};
    poly B[] = {0x0000000000000000, 0x0000000000000001, 0x0000000000000002, 0x0000000000000005};
    // pC = polymult(A, B);
    // printd(B);
    printd(inflate(A, truncate(A, 2), 2));
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
    static poly C[T] = EMPTY;
    pC = C;

    for (k = 0; k < WORDSIZE; k++)
    {
        for (j = 0; j < T; j++)
            if ((*(A + j) >> k) % 2 == 1)
                pC = inflate(pC, polyadd(truncate(pC, j), B), j);
        if (k != WORDSIZE - 1)
            for (j = 0; j < T; j++)
                *(B + j) <<= 1;
    }
    return pC;
}

poly *truncate(poly *C, int j)
{
    int i;
    static poly TC[T] = EMPTY;

    for (i = 0; i < T - j; i++)
        TC[i + j] = *(C + i);
    return TC;
}

poly *inflate(poly *C, poly *Ct, int j)
{
    int i;
    static poly IC[T] = EMPTY;

    for (i = 0; i < j; i++)
        IC[i] = Ct[(T)-j + i];
    for (i = j; i < T; i++)
        IC[i] = C[i];
    return (IC);
}
