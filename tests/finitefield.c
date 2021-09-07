#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../bflib.h"
#define ARRAY(p)                \
    for (int i = 0; i < T; i++) \
        actual[i] = *(p + i);

using ::testing::ElementsAreArray;

poly actual[T] = EMPTY;
poly A[] = {0x000000000000020A, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000};
poly B[] = {0x0000000000003011, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000};
poly C[] = {0x0000000004aee4ea, 0x000000a533d70a81, 0x7f870103204f8423, 0x0000000000000000};
poly D[] = {0x000000000007fcc9, 0x002bb5a1dfb406d5, 0x002c18ab23fae0a6, 0x000000675d04bba1};
poly E[] = {0x0002d8605650dd22, 0x0000000000000000, 0x00035fd6089cfa4b, 0x000000000006906a};
poly F[] = {0x4d97f56ce72c46e8, 0x2fd5f586f1a14166, 0xc702c54a7b4e7c65, 0x882d36a52d372aaa};
poly Fsq[] = {0x6F1BED4F0C867BE9, 0x299D75EB6EA0069C, 0x7EA157EF0CF22E78, 0x1BBFDB9689F};
poly x[] = {0xf8f8eb7371fd558b, 0x5fef65bc391f8b36, 0x8313bb2139f1bb75, 0xfac9dfcbac};
poly y[] = {0x36716f7e01f81052, 0xbf8a0beff867a7ca, 0x03350678e58528be, 0x1006a08a419};
poly x2[] = {0x8468364BDC592AAD, 0x7047DC0FD9A5488A, 0xBAC7D9E109A67A1F, 0x845FD61638};
poly y2[] = {0xC39CC7823D734660, 0x765A8A85D776325F, 0xBBA2587C83900984, 0x1B1420774A};

poly G[] = {0x4d97f56ce72c46e8, 0x2fd5f586f1a14166, 0xc702c54a7b4e7c65, 0x882d36a52d372aaa, 0x002c18ab23fae0a6, 0x002bb5a1dfb406d5, 0x7f870103204f8423, 0};

TEST(Addition, AllAddition)
{
    poly *pointer = polyadd(A, B);
    ARRAY(pointer);
    const poly expected1[] = {0x321B, 0, 0, 0};
    EXPECT_THAT(actual, ElementsAreArray(expected1));
    pointer = polyadd(A, C);
    ARRAY(pointer);
    const poly expected2[] = {0x4AEE6E0, 0xA533D70A81, 0x7F870103204F8423, 0};
    EXPECT_THAT(actual, ElementsAreArray(expected2));
    pointer = polyadd(C, D);
    ARRAY(pointer);
    const poly expected3[] = {0x4A91823, 0x2BB504EC630C54, 0x7FAB19A803B56485, 0x675D04BBA1};
    EXPECT_THAT(actual, ElementsAreArray(expected3));
}

TEST(Multiplication, OneWordTests)
{
    poly *pointer = polymult(A, B);
    ARRAY(pointer);
    const poly expected1[] = {0x61C2AA, 0, 0, 0};
    EXPECT_THAT(actual, ElementsAreArray(expected1));
    pointer = polymult(A, C);
    ARRAY(pointer);
    const poly expected2[] = {0x971E33A84, 0x14E045703430A, 0xD340C5FDDEB6F5E, 0xFC};
    EXPECT_THAT(actual, ElementsAreArray(expected2));
}

TEST(Multiplication, BigTests)
{
    poly *pointer = polymult(x, y);
    ARRAY(pointer);
    const poly expected1[] = {0xBA0C7EB352828319, 0x7D4FD91D3E8E5D7D, 0x2ECB17F328C969CB, 0x1C6D6A307};
    EXPECT_THAT(actual, ElementsAreArray(expected1));
    pointer = polymult(F, F);
    ARRAY(pointer);
    const poly expected2[] = {0x6F1BED4F0C867BE9, 0x299D75EB6EA0069C, 0x7EA157EF0CF22E78, 0x1BBFDB9689F};
    EXPECT_THAT(actual, ElementsAreArray(expected2));
}

TEST(Reduction, FourWordTests)
{
    poly *red = copyPoly(F, 8, '0');
    reduce(red);
    ARRAY(red);
    const poly expected1[] = {0x4D97F56CE7685073, 0x2FD5F587E1FB2D66, 0xC702C54A7B4E7C65, 0xA52D372AAA};
    EXPECT_THAT(actual, ElementsAreArray(expected1));
}

TEST(Reduction, SevenWordTests)
{
    poly *red = copyPoly(G, 8, '1');
    reduce(red);
    ARRAY(red);
    const poly expected1[] = {0x18798F1DB7481FF7, 0x46D3EAC40A452B6A, 0xF9FAEF226A9658E8, 0xE32D5F8269};
    EXPECT_THAT(actual, ElementsAreArray(expected1));
}

TEST(Division, FullWordTest)
{
    poly *pointer = polydivide(D, F);
    ARRAY(pointer);
    const poly expected1[] = {0xE212571AF16B2DB, 0x80D8C2E1BFE23793, 0x066BEB93C7BE1B66, 0x119F47BA491};
    EXPECT_THAT(actual, ElementsAreArray(expected1));
    pointer = polydivide(F, Fsq);
    ARRAY(pointer);
    const poly expected2[] = {0x4D97F56CE7685073, 0x2FD5F587E1FB2D66, 0xC702C54A7B4E7C65, 0xA52D372AAA};
    EXPECT_THAT(actual, ElementsAreArray(expected2));
}

TEST(CombinedOperations, circular)
{
    poly *pointer = polydivide(F, polymult(F, F));
    ARRAY(pointer);
    const poly expected1[] = {0x4D97F56CE7685073, 0x2FD5F587E1FB2D66, 0xC702C54A7B4E7C65, 0xA52D372AAA};
    EXPECT_THAT(actual, ElementsAreArray(expected1));
}

TEST(PointDouble, pointP)
{
    struct ECP P;
    P.x = x;
    P.y = y;
    struct ECP twoP = pointdouble(P);
    ARRAY(twoP.x);
    const poly expectedx[] = {0x8468364BDC592AAD, 0x7047DC0FD9A5488A, 0xBAC7D9E109A67A1F, 0x845FD61638};
    EXPECT_THAT(actual, ElementsAreArray(expectedx));
    ARRAY(twoP.y);
    const poly expectedy[] = {0xC39CC7823D734660, 0x765A8A85D776325F, 0xBBA2587C83900984, 0x1B1420774A};
    EXPECT_THAT(actual, ElementsAreArray(expectedy));
}

TEST(PointAdd, pointP)
{
    struct ECP P;
    P.x = x;
    P.y = y;
    struct ECP P2;
    P2.x = x2;
    P2.y = y2;
    struct ECP threeP = pointadd(P, P2);
    ARRAY(threeP.x);
    const poly expectedx[] = {0xC0E3FB6EA0AEF9FF, 0xB9F0158C4D02A85C, 0x11BD753A76364595, 0x80F50A3309};
    EXPECT_THAT(actual, ElementsAreArray(expectedx));
    ARRAY(threeP.y);
    const poly expectedy[] = {0x3DAF76901C9B8743, 0xC27104BD5C42BCBE, 0xEB52675E98E6432C, 0x17A49033F12};
    EXPECT_THAT(actual, ElementsAreArray(expectedy));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}