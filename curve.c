#include "bflib.h"

poly a[] = ONE;
poly b[] = {0x81fe115f7d8f90ad, 0x213b333b20e9ce42, 0x332c7f8c0923bb58, 0x66647ede6c};

void invertPoint(struct ECP point)
{
    point.x = polyadd(point.x, point.y);
}

struct ECP pointadd(struct ECP P1, struct ECP P2)
{
    struct ECP sum;
    poly *xsum = polyadd(P1.x, P2.x);
    poly *lam = polydivide(xsum, polyadd(P1.y, P2.y));
    sum.x = polyadd(polyadd(polyadd(polymult(lam, lam), lam), xsum), a);
    sum.y = polyadd(polymult(lam, polyadd(sum.x, P1.x)), polyadd(sum.x, P1.y));
    return sum;
}

struct ECP pointdouble(struct ECP point)
{
    struct ECP doubling;
    poly *lam = polyadd(point.x, polydivide(point.x, point.y));
    doubling.x = polyadd(polyadd(polymult(lam, lam), lam), a);
    doubling.y = polyadd(polyadd(polymult(point.x, point.x), polymult(doubling.x, lam)), doubling.x);
    return doubling;
}

struct ECP pointmult(struct ECP point, poly *k)
{
    int i, j;
    char first = 0x0;
    struct ECP product;
    poly one[] = ONE;
    poly zero[] = EMPTY;
    poly *Temp = copyPoly(zero, 4, '0');
    poly *X1 = copyPoly(point.x, 4, '0');
    poly *Z1 = copyPoly(one, 4, '0');
    poly *Z2 = polysquare(point.x);
    poly *X2 = polyadd(polysquare(Z2), b);
    // poly *shifter = (poly *)malloc(sizeof(poly) * T);

    for (i = T - 1; i >= 0; i--)
    {
        for (j = WORDSIZE - 1; j >= 0; j--)
        {
            // mpn_rshift(shifter, k, 4, j);
            // printd(shifter, 4);
            // printf("%d\n", j);
            if (first < 1)
            {
                if ((k[i] >> j) % 2 == 1)
                {
                    first += 1;
                }
                continue;
            }
            if ((k[i] >> j) % 2 == 1)
            {
                Temp = copyPoly(Z1, 4, '0');
                Z1 = polysquare(polyadd(polymult(X1, Z2), polymult(X2, Z1)));
                X1 = polyadd(polymult(point.x, Z1), polymult(polymult(X1, X2), polymult(Temp, Z2)));
                Temp = copyPoly(X2, 4, '0');
                X2 = polyadd(polysquare(polysquare(X2)), polymult(b, polysquare(polysquare(Z2))));
                Z2 = polymult(polysquare(Temp), polysquare(Z2));
            }
            else
            {
                Temp = copyPoly(Z2, 4, '0');
                Z2 = polysquare(polyadd(polymult(X1, Z2), polymult(X2, Z1)));
                X2 = polyadd(polymult(point.x, Z2), polymult(polymult(X1, X2), polymult(Temp, Z1)));
                Temp = copyPoly(X1, 4, '0');
                X1 = polyadd(polysquare(polysquare(X1)), polymult(b, polysquare(polysquare(Z1))));
                Z1 = polymult(polysquare(Temp), polysquare(Z1));
            }
        }
    }

    product.x = polydivide(Z1, X1);
    product.y = polyadd(polymult(polymult(polyadd(point.x, product.x), polyadd(polymult(polyadd(X1, polymult(point.x, Z1)), polyadd(X2, polymult(point.x, Z2))), polymult(polyadd(polysquare(point.x), point.y), polymult(Z1, Z2)))), polydivide(polymult(polymult(point.x, Z1), Z2), one)), point.y);

    return product;
}