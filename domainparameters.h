#include <NTL/ZZ_pX.h>
#include <NTL/ZZX.h>
#include "bflib.h"
#include "stdio.h"
using namespace NTL;

poly hash(poly x);
poly randnum();
ZZX InvSqrt(ZZX a, ZZX z0, int N);
ZZX Invert(ZZX a, int N);
ZZX polytoNTL(poly *b);
void initialize();
void initializeP();
ZZ AGM(poly *b);
ZZX red(ZZX a, ZZ modulus);
