#include "domainparameters.h"
using namespace NTL;
using namespace std;

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
    return B;
}

ZZ_pX InvSqrt(ZZ_pX a, ZZ_pX z0, int N)
{
    ZZ_pX z;
    if (N <= 3)
    {
        z = z0;
    }
    else
    {
        int Np = ceil((N + 1.0) / 2);
        // cout << N << ", Np: " << Np;
        z = InvSqrt(a, z0, Np);
        ZZ_p::init(ZZ(1) << (N + 1));
        // z = (z * 3) / 3;
        // cout << N << "\n";
        ZZ_pX s = 1 - MulMod(a, SqrMod(z, P), P);
        ZZ_p::init((ZZ(1) << (N + 1)) + 1); // Highly illegal
        ZZ_pX s2 = s / 2;
        // cout << "N: " << N << "\n";
        // cout << s2 << "\n";
        ZZ_p::init(ZZ(1) << N);
        z += MulMod(z, s2, P);
        // cout << z << "\n";
    }
    // cout << "\n";
    return z;
}

ZZ_pX Invert(ZZ_pX a, int N)
{
    ZZ_pX z;
    if (N == 1)
    {
        ZZ_p::init(ZZ(4));
        a = (a * 3) / 3;
        ZZ_p::init(ZZ(2));
        z = InvMod(a, P);
    }
    else
    {
        int Np = ceil((N * 1.0) / 2);
        z = Invert(a, Np);
        ZZ_p::init(ZZ(1) << N);
        z += MulMod(z, 1 - MulMod(a, z, P), P);
    }
    return z;
}

void initialize()
{
    // SetCoeff(p, 8);
    // SetCoeff(p, 4);
    // SetCoeff(p, 3);
    // SetCoeff(p, 2);
    // SetCoeff(p, 0);

    // SetCoeff(p, 8);
    // SetCoeff(p, 7, 644);
    // SetCoeff(p, 6, 842);
    // SetCoeff(p, 5, 134);
    // SetCoeff(p, 4, 523);
    // SetCoeff(p, 3, 21);
    // SetCoeff(p, 2, 1019);
    // SetCoeff(p, 1, 562);
    // SetCoeff(p, 0);

    SetCoeff(p, 7);
    SetCoeff(p, 1);
    SetCoeff(p, 0);

    // SetCoeff(p, 233);
    // SetCoeff(p, 74);
    // SetCoeff(p, 0);

    build(P, p);
    ZZ_pE::init(P);
}

ZZ AGM(poly *b)
{
    ZZ_p::init(ZZ(16));
    initialize();
    ZZ_pX B = polytoNTL(b);
    ZZ_pX lambda = 1 + 8 * B;
    int k = 5;
    int N = ceil(FIELD_SIZE / 2.0) + 3;
    while (k <= N)
    {
        // cout << lambda << "\n";
        ZZ_p::init((ZZ(1) << k) + 1); // Highly illegal
        ZZ_pX a = (lambda - 1) / 2;
        // cout << a << "\n";
        ZZ_p::init(ZZ(8));
        ZZ_pX l0 = 1 - a;
        l0 = (l0 * 3) / 3;
        // cout << l0 << "\n";
        // cout << "\n";
        ZZ_p::init((ZZ(1) << k) + 1); // Highly illegal
        ZZ_pX lam2 = (1 + lambda) / 2;
        ZZ_p::init(ZZ(1) << k);
        // cout << ZZ_p::modulus() << "\n";
        // cout << k << "\n";
        ZZ_pX ivs = InvSqrt(lambda, l0, k - 1);
        // cout << "ivs: " << ivs << "\n";
        // cout << "\n";
        ZZ_p::init(ZZ(1) << k);
        lambda = MulMod(ivs, lam2, P);
        // cout << "lam2: " << lam2 << "\n";
        // cout << lambda << "\n";
        k++;
    }
    ZZ_p::init(ZZ(1) << (N - 1));
    lambda = (lambda * 3) / 3;
    cout << lambda << "\n";
    ZZ_p::init((ZZ(1) << (N - 1)) + 1);
    ZZ_pX inv = (1 + lambda) / 2;
    ZZ_p::init(ZZ(1) << (N - 1));
    inv = Invert(inv, N - 1);
    // cout << inv << "\n";
    ZZ_pX tr = MulMod(lambda, inv, P);

    ZZ_p::init((ZZ(1) << 521) - 1);
    ZZ_p t = resultant(p, tr);
    ZZ_p::init(ZZ(1) << (N - 1));
    // t = -t;
    t = (t * 3) / 3;
    cout << t << "\n";
    ZZ T = conv<ZZ>(t);
    if (sqr(T) > (ZZ(1) << (FIELD_SIZE + 2)))
        T -= (ZZ(1) << (N - 1));

    return (ZZ(1) << FIELD_SIZE) + 1 - T;
}

ZZ_pX retModulus()
{
    return p;
}

ZZ AGM2(poly *b)
{
}
// struct Domains randomEC()
// {
//     struct Domains curve;
//     poly b[WORD_COUNT];
//     int s = 3;
//     int v = 41;
//     poly S = randnum();
//     b[0] = hash(S) & 0x1FFFFFFFFFF;
//     for (i = 1; i < WORD_COUNT; i++)
//         b[i] = hash(S + i);

//     ZZ N = AGM(b);
// }