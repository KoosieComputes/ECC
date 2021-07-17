#define WORDSIZE 64
#define M 233
#define T 4
#define EMPTY                                                                          \
    {                                                                                  \
        0x0000000000000000, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000 \
    }
#define printd(C)               \
    for (i = 0; i < T; i++)     \
        printf("%lx \t", C[i]); \
    printf("\n");

typedef unsigned long poly;
poly *polyadd(poly *A, poly *B);
poly *polymult(poly *A, poly *B);
poly *truncate(poly *C, int j);