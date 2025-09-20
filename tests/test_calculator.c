// tests/test_calculator.c
#include "test_framework.h"
#include "calculator.h"

TEST(CalculatorTest, Add) {
    int result = calculator_add(2, 3);
    EXPECT_EQ(5, result);
}

TEST(CalculatorTest, Subtract) {
    int result1 = calculator_subtract(5, 3);
    EXPECT_EQ(2, result1);
    
    int result2 = calculator_subtract(10, 7);
    EXPECT_EQ(3, result2);
}