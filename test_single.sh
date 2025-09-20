#!/bin/bash

# 单模块测试脚本
# 用法: ./test_single.sh <module_name>

if [ $# -eq 0 ]; then
    echo "用法: $0 <module_name>"
    echo "可用模块: calculator, mathutils, hello"
    exit 1
fi

MODULE=$1
mkdir -p bin

echo "=== 测试 $MODULE 模块 ==="

case $MODULE in
    calculator)
        echo "编译Calculator模块测试..."
        # 创建临时测试运行器
        cat > temp_test_runner.c << 'EOF'
#include "test_framework.h"

extern void run_CalculatorTest_Add(void);
extern void run_CalculatorTest_Subtract(void);

int main(void) {
    init_test_framework();
    
    printf("[----------] 2 tests from CalculatorTest\n");
    RUN_TEST(CalculatorTest, Add);
    RUN_TEST(CalculatorTest, Subtract);
    printf("[----------] 2 tests from CalculatorTest (0 ms total)\n\n");
    
    print_test_results();
    return run_all_tests();
}
EOF
        
        gcc -std=c99 -g -Wall -I./include -o bin/test_single \
            src/calculator.c src/test_framework.c tests/test_calculator.c temp_test_runner.c -lm
        ;;
        
    mathutils)
        echo "编译MathUtils模块测试..."
        cat > temp_test_runner.c << 'EOF'
#include "test_framework.h"

extern void run_MathUtilsTest_Power(void);
extern void run_MathUtilsTest_Factorial(void);

int main(void) {
    init_test_framework();
    
    printf("[----------] 2 tests from MathUtilsTest\n");
    RUN_TEST(MathUtilsTest, Power);
    RUN_TEST(MathUtilsTest, Factorial);
    printf("[----------] 2 tests from MathUtilsTest (0 ms total)\n\n");
    
    print_test_results();
    return run_all_tests();
}
EOF
        
        gcc -std=c99 -g -Wall -I./include -o bin/test_single \
            src/mathutils.c src/test_framework.c tests/test_mathutils.c temp_test_runner.c -lm
        ;;
        
    hello)
        echo "编译Hello模块测试..."
        cat > temp_test_runner.c << 'EOF'
#include "test_framework.h"

extern void run_HelloTest_SayHello(void);
extern void run_HelloTest_SayHelloWithName(void);
extern void run_HelloTest_GetGreeting(void);

int main(void) {
    init_test_framework();
    
    printf("[----------] 3 tests from HelloTest\n");
    RUN_TEST(HelloTest, SayHello);
    RUN_TEST(HelloTest, SayHelloWithName);
    RUN_TEST(HelloTest, GetGreeting);
    printf("[----------] 3 tests from HelloTest (0 ms total)\n\n");
    
    print_test_results();
    return run_all_tests();
}
EOF
        
        gcc -std=c99 -g -Wall -I./include -o bin/test_single \
            src/hello.c src/test_framework.c tests/test_hello.c temp_test_runner.c -lm
        ;;
        
    *)
        echo "错误: 未知模块 '$MODULE'"
        echo "可用模块: calculator, mathutils, hello"
        exit 1
        ;;
esac

# 检查编译是否成功
if [ $? -eq 0 ] && [ -f bin/test_single ]; then
    echo "运行测试..."
    ./bin/test_single
    TEST_RESULT=$?
    
    # 清理临时文件
    rm -f temp_test_runner.c bin/test_single
    
    if [ $TEST_RESULT -eq 0 ]; then
        echo -e "\n✅ $MODULE 模块测试通过！"
    else
        echo -e "\n❌ $MODULE 模块测试失败！"
        exit 1
    fi
else
    echo "❌ 编译失败！"
    rm -f temp_test_runner.c
    exit 1
fi