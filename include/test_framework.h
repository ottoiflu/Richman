// include/test_framework.h
#ifndef TEST_FRAMEWORK_H
#define TEST_FRAMEWORK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// 全局测试统计
extern int test_count;
extern int test_passed;
extern int test_failed;

// 测试宏定义
#define TEST(suite_name, test_name) \
    void test_##suite_name##_##test_name(void); \
    void run_##suite_name##_##test_name(void) { \
        test_count++; \
        printf("[ RUN      ] %s.%s\n", #suite_name, #test_name); \
        test_##suite_name##_##test_name(); \
        printf("[       OK ] %s.%s\n", #suite_name, #test_name); \
        test_passed++; \
    } \
    void test_##suite_name##_##test_name(void)

// 断言宏
#define EXPECT_EQ(expected, actual) \
    do { \
        if ((expected) != (actual)) { \
            printf("[  FAILED  ] Expected: %d, Actual: %d\n", (expected), (actual)); \
            test_failed++; \
            test_count--; \
            test_passed--; \
            return; \
        } \
    } while(0)

#define EXPECT_STREQ(expected, actual) \
    do { \
        if (strcmp((expected), (actual)) != 0) { \
            printf("[  FAILED  ] Expected: \"%s\", Actual: \"%s\"\n", (expected), (actual)); \
            test_failed++; \
            test_count--; \
            test_passed--; \
            return; \
        } \
    } while(0)

// 测试框架函数
void init_test_framework(void);
void print_test_results(void);
int run_all_tests(void);

// 测试运行宏
#define RUN_TEST(suite_name, test_name) run_##suite_name##_##test_name()

#ifdef __cplusplus
}
#endif

#endif /* TEST_FRAMEWORK_H */