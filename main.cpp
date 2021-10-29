// #include "bflib.h"
#include "domainparameters.h"

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

poly **messageToPoly(char *m)
{
    // pack the message string into an array of polynomials of degree < 233 - k, such that each polynomial can thus be converted to message points and encrypted.
}

char *polyToMessage(poly **M)
{
    // unpack message from array of message points (shift each polynomial right by k to remove the padded bits)
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
    printd(origmessage.x, 4);
    printd(origmessage.y, 4);
    printd(message.x, 4);
    printd(message.y, 4);

    return 0;
}