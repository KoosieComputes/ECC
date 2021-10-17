#include "bflib.h"
#include "stdio.h"
#include <NTL/ZZ_pX.h>

using namespace NTL;
using namespace std;

int main(int argc, char const *argv[])
{
    // int i;
    // poly *pC;
    // poly A[] = {0x20A, 0, 0, 0};
    // poly t[] = {0x1, 0x1, 0, 0};
    // poly B[] = {0x3011, 0, 0, 0};
    // poly one[] = {1, 0, 0, 0};
    // poly D[] = {0x000000000007fcc9, 0x002bb5a1dfb406d5, 0x002c18ab23fae0a6, 0x000000675d04bba1};
    // poly C[] = {0x0000000004aee4ea, 0x000000a533d70a81, 0x7f870103204f8423, 0x0000000000000000};
    // poly F[] = {0x4d97f56ce72c46e8, 0x2fd5f586f1a14166, 0xc702c54a7b4e7c65, 0x882d36a52d372aaa};
    // poly pF[] = {0x4D97F56CE7685073, 0x2FD5F587E1FB2D66, 0xC702C54A7B4E7C65, 0xA52D372AAA};
    // poly Fsq[] = {0x6F1BED4F0C867BE9, 0x299D75EB6EA0069C, 0x7EA157EF0CF22E78, 0x1BBFDB9689F};
    // poly G[] = {0x4d97f56ce72c46e8, 0x2fd5f586f1a14166, 0xc702c54a7b4e7c65, 0x882d36a52d372aaa, 0x002c18ab23fae0a6, 0x002bb5a1dfb406d5, 0x7f870103204f8423, 0};
    // poly pG[] = {0xE64B018E47E4F4D6, 0x37E384C1B5C5117E, 0x7B4A876458166687, 0xE32D1FC6E8};
    // poly x[] = {0xf8f8eb7371fd558b, 0x5fef65bc391f8b36, 0x8313bb2139f1bb75, 0xfac9dfcbac};
    // poly y[] = {0x36716f7e01f81052, 0xbf8a0beff867a7ca, 0x03350678e58528be, 0x1006a08a419};
    // poly f[] = RPOLY;

    ZZ_p::init(ZZ(16));
    ZZ_p j;
    cin >> j;
    cout << j;
    return 0;
}
