#define WORDSIZE 64
#define M 233
#define T 4
#define LT 8
#define RPOLY {0x1, 0x400, 0, 0x20000000000}
#define EMPTY {0, 0, 0, 0}
#define LEMPTY {0, 0, 0, 0, 0, 0, 0, 0}
#define printd(C, len)               \
    for (i = 0; i < len; i++)     \
        printf("%lx \t", C[i]); \
    printf("\n");

typedef unsigned long poly;
poly *copyPoly(poly *A, short len, char size);
poly *polyadd(poly *A, poly *B);
poly *polymult(poly *A, poly *B);
poly *truncate(poly *C, int j);
poly *polydivide(poly *A, poly *B);
void reduce(poly *A);
int isequal(poly *A, poly *B, short len);