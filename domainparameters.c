#include "bflib.h"
#include "stdio.h"

poly hash(poly x)
{
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    x = x ^ (x >> 31);
    return x;
}

poly rand()
{
    poly randval;
    FILE *fp;
    fp = fopen("/dev/urandom", "r");
    fread(&randval, sizeof(randval), 1, fp);
    fclose(fp);
    return randval;
}

poly *AGM(poly *b)
{
    poly *lambda = 
}

struct Domains randomEC
{
    struct Domains curve;
    poly *b[T];
    int s = 3;
    int v = 41;
    poly S = rand();
    b[0] = hash(S) & 0x1FFFFFFFFFF;
    for (int i = 1; i < T; i++)
        b[i] = hash(S+i);
    
    poly* N[T] = AGM(b); //Not a polynomial, actually an integer

}