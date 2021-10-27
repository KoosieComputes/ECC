#include "domainparameters.h"
using namespace NTL;
using namespace std;

int i;
ZZ_pX p;
ZZ_pXModulus P;
ZZX p2;
poly b[WORD_COUNT];

poly hashfunc(poly x)
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

ZZ AGM(poly *b)
{
    initialize();
    ZZX B = polytoNTL(b);
    ZZX lambda = 1 + 8 * B;
    ZZ modulus;
    int k = 5;
    int N = ceil(FIELD_SIZE / 2.0) + 3;
    while (k <= N)
    {
        modulus = ZZ(1) << k;
        ZZX a = (lambda - 1) / 2;
        ZZX z0 = red(1 - a, ZZ(8));
        ZZX lam2 = (1 + lambda) / 2;
        ZZX ivs = InvSqrt(lambda, z0, k - 1);
        lambda = MulMod(ivs, lam2, p2);
        lambda = red(lambda, ZZ(1) << k);
        k++;
    }
    lambda = red(lambda, ZZ(1) << (N - 1));
    ZZX inv = Invert((1 + lambda) / 2, N - 1);
    ZZX tr = MulMod(lambda, inv, p2);
    tr = red(tr, ZZ(1) << (N - 1));
    ZZ t = resultant(p2, tr);
    t = -t % (ZZ(1) << (N - 1));
    cout << t << "\n";
    if (sqr(t) > (ZZ(1) << (FIELD_SIZE + 2)))
        t -= (ZZ(1) << (N - 1));

    return (ZZ(1) << FIELD_SIZE) + 1 - t;
}

ZZX Invert(ZZX a, int N)
{
    ZZX z;
    if (N == 1)
    {
        ZZ_p::init(ZZ(2));
        initializeP();
        ZZ_pX inv = conv<ZZ_pX>(red(a, ZZ(2)));
        ZZ_pX temp = InvMod(inv, P);
        z = conv<ZZX>(temp);
    }
    else
    {
        int Np = ceil((N * 1.0) / 2);
        z = Invert(a, Np);
        z += MulMod(z, 1 - MulMod(a, z, p2), p2);
        z = red(z, ZZ(1) << N);
    }
    return z;
}

ZZX InvSqrt(ZZX a, ZZX z0, int N)
{
    ZZX z;
    if (N <= 3)
    {
        z = z0;
    }
    else
    {
        int Np = ceil((N + 1.0) / 2);
        z = InvSqrt(a, z0, Np);
        ZZX sqr = MulMod(z, z, p2);
        ZZX s = 1 - MulMod(a, sqr, p2);
        s = red(s, ZZ(1) << (N + 1));
        s /= 2;
        z += MulMod(z, s, p2);
        z = red(z, ZZ(1) << N);
    }
    return z;
}

ZZX red(ZZX a, ZZ modulus)
{
    ZZX r;
    for (i = 0; i <= deg(a); i++)
        SetCoeff(r, i, a[i] % modulus);

    return r;
}

void initialize()
{
    SetCoeff(p2, 233);
    SetCoeff(p2, 74);
    SetCoeff(p2, 0);
}

void initializeP()
{
    SetCoeff(p, 233);
    SetCoeff(p, 74);
    SetCoeff(p, 0);

    build(P, p);
}

ZZX polytoNTL(poly *b)
{
    ZZX B;
    int j;
    for (i = 0; i < WORD_COUNT; i++)
    {
        for (j = 0; j < WORD_SIZE; j++)
            if ((b[i] >> j) % 2 == 1)
                SetCoeff(B, (i * 64) + j);
    }
    return B;
}

poly *randomB()
{
    poly S = randnum();
    b[0] = hashfunc(S) & 0x1FFFFFFFFFF;
    for (i = 1; i < WORD_COUNT; i++)
        b[i] = hashfunc(S + i);

    return b;
}

bool suitablePrime(ZZ p)
{
    bool vunerable = false;
    for (i = 1; i <= 20; i++)
    {
        if (divide(p, power((ZZ(1) << 233), i) - 1) == 1)
        {
            vunerable = true;
            break;
        }
    }
    return vunerable;
}

struct Domains randomEC()
{
    struct Domains curve;
    struct ECP generator, solution;
    bool flags = true;
    bool vunerable = false;
    poly *B;
    ZZ prime, N;
    while (flags)
    {
        B = randomB();
        while (polytrace(B) == 1) // y^2 + y = b (trace needs to be 0 for a solution)
            B = randomB();
        N = AGM(B);
        if (divide(N, 2) == 1) // Cofactor needs to be 2 for Message representation on point.
        {
            prime = N / 2;
            if (ProbPrime(prime, 20)) // Negligible probability for false positives 4^(-20)
                if (suitablePrime(prime))
                    goto selected;
        }
    }
selected:
    curve.h = 2;
    curve.n = prime;
    curve.b = B;
    poly x[] = {1, 0, 0, 0};
    solution.x = x;
    solution.y = polysolve(B);
    generator = pointdouble(solution); // Doubling will not be point at infinity
    curve.P = generator;
    return curve;
}