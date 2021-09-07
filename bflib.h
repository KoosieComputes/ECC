#define WORDSIZE 64
#define M 233
#define T 4
#define LT 8
#define RPOLY {0x1, 0x400, 0, 0x20000000000}
#define EMPTY {0, 0, 0, 0}
#define LEMPTY {0, 0, 0, 0, 0, 0, 0, 0}
#define ONE {1, 0, 0, 0}
#define printd(C, len)               \
    for (i = 0; i < len; i++)     \
        printf("%lx \t", C[i]); \
    printf("\n");

typedef unsigned long poly;
poly *copyPoly(poly *A, short len, char size);
poly *polyadd(poly *A, poly *B);
poly *polymult(poly *A, poly *B);
poly *ltrmult(poly *A, poly *B);
poly *wordshift(poly *C, short j);
poly *polydivide(poly *A, poly *B);
void reduce(poly *A);
void swapArray(poly *a, poly *b, short n);
int isequal(poly *A, poly *B, short len);

struct ECP {
    poly *x;
    poly *y;
};
void invertPoint(struct ECP point);
struct ECP pointadd(struct ECP P1, struct ECP P2);
struct ECP pointdouble(struct ECP point);

