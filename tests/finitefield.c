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
    pointer = polymult(B, C);
    ARRAY(pointer);
    const poly expected3[] = {0xDF7C934A4A, 0x1EFFB19F5F9291, 0x17C7473C2C719613, 0x80F};
    EXPECT_THAT(actual, ElementsAreArray(expected3));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}