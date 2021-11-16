// #include "bflib.h"
#include "domainparameters.h"
#include <string.h>

using namespace NTL;
using namespace std;

char *getMessage()
{
    char *m;
    size_t len = 100;
    m = (char *)malloc(len * sizeof(char));
    printf("Please enter message: ");
    getline(&m, &len, stdin);
    return m;
}

void clearbits(element *r, int diff, int elcount)
{
    int i, j;
    poly zero[] = EMPTY;
    poly ones[] = {0b11111111, 0, 0, 0};
    poly *clear = copyPoly(zero, 4, '0');
    for (i = 0; i < ((32 - diff) + 4 * (elcount - 1) - 1); i++)
    {
        mpn_lshift(clear, clear, WORD_COUNT, 8);
        mpn_xor_n(clear, clear, ones, WORD_COUNT);
    }
    mpn_and_n(*(r + (elcount - 1)), *(r + (elcount - 1)), clear, WORD_COUNT);
}

// pack the message string into an array of elements of degree < 233 - k, such that each element can thus be converted to message points and encrypted.
element *messageToPoly(char *m)
{
    int elementcount = (int)ceil(strlen(m) / 28.0);
    size_t size = sizeof(element) * elementcount;
    element *result = (element *)malloc(size);
    for (int i = 0; i < elementcount; i++)
        memcpy(result + i, m + (i * 28), 32);

    clearbits(result, size - strlen(m), elementcount);

    return result;
}

void printe(element *e, int elcount)
{
    int i, j;
    for (j = 0; j < elcount; j++)
    {
        printf("i:%d\n", j);
        printd(*(e + j), WORD_COUNT);
        printf("\n");
    }
}

// unpack message from array of message points (shift each polynomial right by k to remove the padded bits)
char *polyToMessage(element *M)
{
    char *result = (char *)M;
    return result;
}

void slice(const char *str, char *result, size_t start, size_t end)
{
    strncpy(result, str + start, end - start);
}

int main()
{

    int i, j;
    Domains dp = randomEC();
    poly zero[] = EMPTY;
    // poly x[] = {0xf8f8eb7371fd558b, 0x5fef65bc391f8b36, 0x8313bb2139f1bb75, 0xfac9dfcbac};
    // poly y[] = {0x36716f7e01f81052, 0xbf8a0beff867a7ca, 0x03350678e58528be, 0x1006a08a419};
    // dp.P.x = x;
    // dp.P.y = y;
    // dp.n = conv<ZZ>("6901746346790563787434755862277025555839812737345013555379383634485463");
    // poly b[] = {0x81FE115F7D8F90AD, 0x213B333B20E9CE42, 0x332C7F8C0923BB58, 0x66647EDE6C};
    // dp.b = b;
    initCurve(dp.b);
    keypair k = Keygen(dp);
    char *m = getMessage();
    int elementcount = (int)ceil(strlen(m) / 28.0);
    element *M = messageToPoly(m);
    ciphertext *c = (ciphertext *)malloc(sizeof(ciphertext) * elementcount);
    printf("Ciphertext:\n");
    for (j = 0; j < elementcount; j++)
    {
        ECP section = MessagePoint(*(M + j), dp);
        *(c + j) = Encrypt(dp, k.Q, section);
        printd((*(c + j)).C1.x, WORD_COUNT);
        printd((*(c + j)).C1.y, WORD_COUNT);
        printd((*(c + j)).C2.x, WORD_COUNT);
        printd((*(c + j)).C2.y, WORD_COUNT);
    }

    char *output = (char *)malloc(28 * elementcount);
    for (j = 0; j < elementcount; j++)
    {
        ECP message = Decrypt(dp, k.d, *(c + j));
        poly *neat = copyPoly(zero, WORD_COUNT, '0');
        mpn_rshift(neat, message.x, WORD_COUNT, 8);
        memcpy(output + (j * 28), neat, 28);
    }
    printf("\nDecrypted: %s", output);
    return 0;
    // 1234567890123456789012345678901234567890
}