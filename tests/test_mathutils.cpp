// tests/test_mathutils.cpp
#include "gtest/gtest.h"
#include "mathutils.h"

TEST(MathUtilsTest, Power) {
    MathUtils utils;
    EXPECT_EQ(utils.power(2, 3), 8);
    EXPECT_EQ(utils.power(5, 2), 25);
    EXPECT_EQ(utils.power(10, 0), 1);
}

TEST(MathUtilsTest, Factorial) {
    MathUtils utils;
    EXPECT_EQ(utils.factorial(0), 1);
    EXPECT_EQ(utils.factorial(1), 1);
    EXPECT_EQ(utils.factorial(5), 120);
}