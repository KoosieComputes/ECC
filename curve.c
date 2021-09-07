#include <stdio.h>
#include <gmp.h>
#include "bflib.h"

poly a[] = ONE;

void invertPoint(struct ECP point)
{
    point.x = polyadd(point.x, point.y);
}

struct ECP pointadd(struct ECP P1, struct ECP P2)
{
    struct ECP sum;
    printf("not here");
    poly *xsum = polyadd(P1.x, P2.x);
    poly *lam = polydivide(xsum, polyadd(P1.y, P2.y));
    printf("not here");
    sum.x = polyadd(polyadd(polyadd(polymult(lam, lam), lam), xsum), a);
    printf("not here");
    sum.y = polyadd(polymult(lam, polyadd(sum.x, P1.x)), polyadd(sum.x, P1.y));
    printf("not here");
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
