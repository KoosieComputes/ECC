#include <stdio.h>
#include <math.h>
#define WORDSIZE 64
#define M 233
#define T 4
#define EMPTY                                                                          \
    {                                                                                  \
        0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000 \
    }

typedef unsigned long long poly;
poly *polyadd(poly *A, poly *B);
poly *polymult(poly *A, poly *B);
poly *trunc(poly *C, int j);

int main()
{
    poly *pC;
    poly A[] = {0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000025};
    poly B[] = {0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000017};
    pC = polymult(A, B);
    printf("%llu", pC[3]);

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
    int k, j;
    static poly C[T] = EMPTY;

    for (k = 0; k < WORDSIZE; k++)
    {
        for (j = 0; j < T - 1; j++)
            if ((*(A + j) >> k) % 2 == 1)
                polyadd(trunc(C, j), B);
        if (k != WORDSIZE - 1)
            *B << 1;
    }
    return C;
}

poly *trunc(poly *C, int j)
{
    int i;
    static poly TC[T] = EMPTY;

    for (i = T; i >= j; i--)
        TC[i - j] = *(C + i);
    return TC;
}
