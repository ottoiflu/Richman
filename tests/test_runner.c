// tests/test_runner.c
#include "test_framework.h"

// 声明所有测试函数
extern void run_CalculatorTest_Add(void);
extern void run_CalculatorTest_Subtract(void);
extern void run_MathUtilsTest_Power(void);
extern void run_MathUtilsTest_Factorial(void);
extern void run_HelloTest_SayHello(void);
extern void run_HelloTest_SayHelloWithName(void);
extern void run_HelloTest_GetGreeting(void);

int main(void) {
    init_test_framework();
    
    // 运行Calculator测试
    printf("[----------] 2 tests from CalculatorTest\n");
    RUN_TEST(CalculatorTest, Add);
    RUN_TEST(CalculatorTest, Subtract);
    printf("[----------] 2 tests from CalculatorTest (%d ms total)\n\n", 0);
    
    // 运行MathUtils测试
    printf("[----------] 2 tests from MathUtilsTest\n");
    RUN_TEST(MathUtilsTest, Power);
    RUN_TEST(MathUtilsTest, Factorial);
    printf("[----------] 2 tests from MathUtilsTest (%d ms total)\n\n", 0);
    
    // 运行Hello测试
    printf("[----------] 3 tests from HelloTest\n");
    RUN_TEST(HelloTest, SayHello);
    RUN_TEST(HelloTest, SayHelloWithName);
    RUN_TEST(HelloTest, GetGreeting);
    printf("[----------] 3 tests from HelloTest (%d ms total)\n\n", 0);
    
    print_test_results();
    return run_all_tests();
}