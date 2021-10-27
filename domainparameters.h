#include <NTL/ZZ_pX.h>
#include <NTL/ZZX.h>
#include <stdio.h>
#include <stdbool.h>
#include "bflib.h"

#define SECURITY_LEVEL 200
using namespace NTL;
poly hashfunc(poly x);
poly randnum();
poly *randomB();
ZZX InvSqrt(ZZX a, ZZX z0, int N);
ZZX Invert(ZZX a, int N);
ZZX polytoNTL(poly *b);
void initialize();
void initializeP();
ZZ AGM(poly *b);
ZZX red(ZZX a, ZZ modulus);

struct Domains
{
    poly *b;
    ZZ n;
    ZZ h;
    struct ECP P;
};