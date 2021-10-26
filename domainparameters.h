#include <NTL/ZZ_pE.h>
#include "bflib.h"
#include "stdio.h"
using namespace NTL;

poly hash(poly x);
poly randnum();
ZZ_pX retModulus();
ZZ_pX InvSqrt(ZZ_pX a, ZZ_pX z0, int N);
ZZ_pX polytoNTL(poly *b);
void initialize();
ZZ AGM(poly *b);
