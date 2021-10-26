#include <NTL/ZZ_pX.h>
#include <NTL/ZZX.h>
#include "bflib.h"
#include "stdio.h"
using namespace NTL;

poly hash(poly x);
poly randnum();
// ZZ_pX retModulus();
ZZ_pX InvSqrt(ZZ_pX a, ZZ_pX z0, int N);
ZZX InvSqrt2(ZZX a, ZZX z0, int N);
ZZ_pX Invert(ZZ_pX a, int N);
ZZX Invert2(ZZX a, int N);
ZZ_pX polytoNTL(poly *b);
ZZX polytoNTL2(poly *b);
void initialize();
void initialize2();
ZZ AGM(poly *b);
ZZ AGM2(poly *b);
ZZX red(ZZX a, ZZ modulus);
