#include "bflib.h"
#include "stdio.h"
#include <NTL/ZZ_pE.h>

poly hash(poly x)
{
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    x = x ^ (x >> 31);
    return x;
}

poly randnum()
{
    poly randval;
    FILE *fp;
    fp = fopen("/dev/urandom", "r");
    fread(&randval, sizeof(randval), 1, fp);
    fclose(fp);
    return randval;
}

poly *AGM(poly *b)
{
    ZZ_p::init(ZZ(16));
    ZZ_pX B = ;
    ZZ_pX P;
    SetCoeff(P, 233, 1);
    SetCoeff(P, 74, 1);
    SetCoeff(P, 0, 1);
    ZZ_pE::init(P);

    ZZ_pX lambda = 1 + 8 * B
}

struct Domains randomEC()
{
    struct Domains curve;
    poly *b[T];
    int s = 3;
    int v = 41;
    poly S = randnum();
    b[0] = hash(S) & 0x1FFFFFFFFFF;
    for (int i = 1; i < T; i++)
        b[i] = hash(S + i);

    poly *N[T] = AGM(b); //Not a polynomial, actually an integer
}