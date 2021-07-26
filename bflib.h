#define WORDSIZE 64
#define M 233
#define T 4
#define LT 8
#define EMPTY {0, 0, 0, 0}
#define LEMPTY {0, 0, 0, 0, 0, 0, 0, 0}
#define printd(C)               \
    for (i = 0; i < T; i++)     \
        printf("%lx \t", C[i]); \
    printf("\n");

typedef unsigned long poly;
poly *copyPoly(poly *A, int len);
poly *polyadd(poly *A, poly *B);
poly *polymult(poly *A, poly *B);
poly *truncate(poly *C, int j);
void reduce(poly *A);