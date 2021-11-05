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
    getline(&m, &len, stdin);
    return m;
}

// pack the message string into an array of elements of degree < 233 - k, such that each element can thus be converted to message points and encrypted.
element *messageToPoly(char *m)
{
    int elementcount = (int)ceil(strlen(m) / 32);
    element *result = (element *)malloc(sizeof(element) * elementcount);
    for (int i = 0; i < elementcount; i++)
        memcpy(result[i], m + ((i + 1) * 28), 32);

    return result;
}

void printe(element *e, int elcount)
{
    poly *p = (poly *)e;
    for (int i = 0; i < elcount; i++)
    {
        printf("i:%d, ", i);
        printf("elcount:%d\n", elcount);
        for (int j = 0; j < WORD_COUNT; j++)
            printf("%lx \t", *(p + (i * WORD_COUNT) + j));
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
    int i;
    Domains dp = randomEC();
    initCurve(dp.b);
    keypair k = Keygen(dp);
    ECP origmessage = pointdouble(dp.P);
    ciphertext c = Encrypt(dp, k.Q, origmessage);
    ECP message = Decrypt(dp, k.d, c);
    printf("Original message:\n");
    printd(origmessage.x, WORD_COUNT);
    printd(origmessage.y, WORD_COUNT);
    printf("Ciphertext:\n");
    printd(c.C1.x, WORD_COUNT);
    printd(c.C1.y, WORD_COUNT);
    printd(c.C2.x, WORD_COUNT);
    printd(c.C2.y, WORD_COUNT);
    printf("Decrypted:\n");
    printd(message.x, WORD_COUNT);
    printd(message.y, WORD_COUNT);
    // int i;
    // Domains dp = randomEC();
    // initCurve(dp.b);
    // keypair k = Keygen(dp);
    // char *m = getMessage();
    // int elementcount = (int)ceil(strlen(m) / 32.0);
    // element *M = messageToPoly(m);
    // printf("elementcount: %d\n", elementcount);
    // ciphertext *c = (ciphertext *)malloc(sizeof(ciphertext) * elementcount);
    // printf("but this fails\n");
    // ECP section;
    // for (i = 0; i < elementcount; i++)
    // {
    //     printf("but this fails\n");
    //     printd((poly *)M[i], 4);
    //     printf("but this fails\n");
    //     section = MessagePoint((poly *)M[i], dp);
    //     printf("but this fails\n");
    //     c[i] = Encrypt(dp, k.Q, section);
    // }
    // printf("but this fails\n");
    // element *output = (element *)malloc(sizeof(element) * elementcount);
    // for (i = 0; i < elementcount; i++)
    // {
    //     ECP message = Decrypt(dp, k.d, c[i]);
    //     memcpy(output[i], message.x, 32);
    //     printf("but this fails\n");
    // }
    // char *decrypted = (char *)output;
    // printf("but this fails\n");
    // printf("%s", decrypted);
    return 0;
    // 1234567890123456789012345678901234567890
}