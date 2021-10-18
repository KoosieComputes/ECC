#include "bflib.h"
#include "stdio.h"
#include <NTL/ZZ_pX.h>

using namespace NTL;
int i;

ZZ_pX p;
ZZ_pXModulus P;

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

ZZ_pX polytoNTL(poly *b)
{
    ZZ_pX B;
    int j;
    for (i = 0; i < WORD_COUNT; i++)
    {
        for (j = 0; j < WORD_SIZE; j++)
            if ((b[i] >> j) % 2 == 1)
                SetCoeff(B, (i + 1) * (j + 1) - 1);
    }
}

ZZ_pX InvSqrt(ZZ_pX a, ZZ_pX z0, int N)
{
    ZZ_pX z;
    if (N <= 2)
        z = z0;
    else
    {
        int Np = ceil((N + 1) / 2);
        z = InvSqrt(a, z0, Np);
        ZZ_p::init(ZZ(2) << (N + 1));
        ZZ_pX s = 1 - MulMod(a, SqrMod(z, P), P);
        ZZ_p::init(ZZ(2) << N);
        z += MulMod(z, s, P) / 2;
    }
    return z;
}

ZZ AGM(poly *b)
{
    ZZ_p::init(ZZ(16));
    initialize();
    ZZ_pX B = polytoNTL(b);
    ZZ_pX lambda = 1 + 8 * B;
    int k = 4;
    while (k < ceil(FIELD_SIZE / 2.0) + 3)
    {
        ZZ_p::init(ZZ(16));
        ZZ_pX a = (lambda - 1) / 8;
        ZZ_p::init(ZZ(8));
        ZZ_pX l0 = 1 - 4 * a;

        ZZ_p::init(ZZ(2) << k);
        lambda = MulMod(InvSqrt(lambda, l0, k), ((1 + lambda) / 2), P);
        k++;
    }
    ZZ_p::init(ZZ(2) << (k - 2));
    ZZ t = conv<ZZ>(NormMod(MulMod(2 * lambda, InvMod(1 + lambda, P), P), P));
    if (sqr(t) > (ZZ(2) << (FIELD_SIZE + 1)))
        t -= (ZZ(2) << (k - 2));

    return (ZZ(2) << (FIELD_SIZE - 1)) + 1 - t;
}

struct Domains randomEC()
{
    struct Domains curve;
    poly b[WORD_COUNT];
    int s = 3;
    int v = 41;
    poly S = randnum();
    b[0] = hash(S) & 0x1FFFFFFFFFF;
    for (i = 1; i < WORD_COUNT; i++)
        b[i] = hash(S + i);

    ZZ N = AGM(b); // Not a polynomial, actually an integer
}

void initialize()
{
    SetCoeff(p, 233);
    SetCoeff(p, 74);
    SetCoeff(p, 0);
    build(P, p);
}