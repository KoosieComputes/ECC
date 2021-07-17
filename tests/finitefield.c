#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "../bflib.h"
#define ARRAY(p)                \
    poly actual[T] = EMPTY;     \
    for (int i = 0; i < T; i++) \
        actual[i] = *(p + i);

using ::testing::ElementsAreArray;

// MATCHER_P(PolyEqual, actual, "Polynomials are not equal")
// {
//     if (sizeof(arg) != T)
//         return false;
//     return (arg[0] == actual[0] && arg[1] == actual[1] && arg[2] == actual[2] && arg[3] == actual[3]);
// }

// int polyEqual(poly *actual, poly *expected)
// {
//     if (sizeof(actual) != T)
//         return false;
//     return (expected[0] == actual[0] && expected[1] == actual[1] && expected[2] == actual[2] && expected[3] == actual[3]);
// }

TEST(Multiplication, BasicAssertions)
{
    poly A[] = {0x000000000000020A, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000};
    poly B[] = {0x0000000000003011, 0x0000000000000000, 0x0000000000000000, 0x0000000000000000};

    poly *pointer = polymult(A, B);
    ARRAY(pointer);

    EXPECT_THAT(actual, testing::ElementsAreArray({0xC38554, 0, 0, 0}));
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}