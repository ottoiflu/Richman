// tests/test_mathutils.c
#include "test_framework.h"
#include "mathutils.h"

TEST(MathUtilsTest, Power) {
    int result1 = mathutils_power(2, 3);
    EXPECT_EQ(8, result1);
    
    int result2 = mathutils_power(5, 2);
    EXPECT_EQ(25, result2);
    
    int result3 = mathutils_power(10, 0);
    EXPECT_EQ(1, result3);
}

TEST(MathUtilsTest, Factorial) {
    int result1 = mathutils_factorial(0);
    EXPECT_EQ(1, result1);
    
    int result2 = mathutils_factorial(1);
    EXPECT_EQ(1, result2);
    
    int result3 = mathutils_factorial(5);
    EXPECT_EQ(120, result3);
}