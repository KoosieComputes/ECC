#include <NTL/ZZ_pX.h>
#include <NTL/ZZX.h>
#include <NTL/ZZ_limbs.h>
#include <stdio.h>
#include <stdbool.h>
#include "bflib.h"

#define SECURITY_LEVEL 200
using namespace NTL;

struct Domains
{
    poly *b;
    ZZ n;
    ZZ h;
    struct ECP P;
};

struct keypair
{
    ZZ d;
    struct ECP Q;
};

struct ciphertext
{
    struct ECP C1;
    struct ECP C2;
};

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
struct Domains randomEC();
struct ECP MessagePoint(poly *Message, Domains curve);
void initCurve(poly *B);

struct keypair Keygen(Domains EC);
struct ciphertext Encrypt(Domains EC, ECP publicKey, ECP M);
struct ECP Decrypt(Domains EC, ZZ privateKey, ciphertext c);