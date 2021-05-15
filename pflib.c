#include <string.h>
#include <stdlib.h>

int *binAddition(int a, int b)
{
    static int r[2];
    int wordLength = 3; // 64

    int c; // carry bit
    while (b != 0)
    {
        c = (a & b) << 1;
        a = a ^ b;
        b = c;
    }

    c = a >> wordLength;

    r[0] = c;
    r[1] = (c << wordLength) ^ a;
    return r;
}

int *hexToBin(char *hex)
{
    int len = strlen(hex);
    int *r = malloc(len / 2);
    r[0] = len;
    // fill it up

    return r;
}
