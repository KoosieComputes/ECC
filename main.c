#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// #include "pflib.h"

int *binAddition(int a, int b);
int *hexToBin(char *hex);

int main(int argc, char const *argv[])
{
    printf("Ha!\n");
    char *n = "2e0e3af30245500956866d1fc2cc795c456ff8a49488e018b82e006bc6824cd1c3d4182460a2fc4f0f2bd49fd09897626c0bbae4bb0fefdd4692e5f67cc573e42426f5e509337e59cc74ef9caf5bd75fd0b26e5567705f4067f9e6ed5e0e692413c2609d5dc19644f7eb107391b5920cd209075b0a99ec4712993945530e4e6005aeda496d5ec8f2c9c5f9b006054c5a6f92a54a0709815a218fbb0dcc6cd0c2";
    int *bs = hexToBin(n);
    printf("first 8 bits: %d\n", *(bs));

    free(bs);
    return 0;
}

// ---------------------------------------------------------

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
