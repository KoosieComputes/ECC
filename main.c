#include <stdio.h>
#include <gmp.h>
#include "bflib.h"

int main(int argc, char const *argv[])
{
    int i;
    poly *pC;
    poly A[] = {0x20A, 0, 0, 0};
    poly B[] = {0x3011, 0, 0, 0};
    poly C[] = {0x0000000004aee4ea, 0x000000a533d70a81, 0x7f870103204f8423, 0x0000000000000000};
    poly F[] = {0x4d97f56ce72c46e8, 0x2fd5f586f1a14166, 0xc702c54a7b4e7c65, 0x882d36a52d372aaa};
    poly pF[] = {0x4D97F56CE7A46BDE, 0x2FD5F587E1FB2D66, 0xC702C54A7B4E7C65, 0xA52D372AAA};
    poly G[] = {0x4d97f56ce72c46e8, 0x2fd5f586f1a14166, 0xc702c54a7b4e7c65, 0x882d36a52d372aaa, 0x002c18ab23fae0a6, 0x002bb5a1dfb406d5, 0x7f870103204f8423, 0};
    poly pG[] = {0xE64B018E47E4F4D6, 0x37E384C1B5C5117E, 0x7B4A876458166687, 0xE32D1FC6E8};
    // reduce(G);
    // printd(G, 4);
    poly *large = copyPoly(F, 8, '0');
    printd(large, 8);
    // printd(pC);
    return 0;
}
