// src/test_framework.c
#include "test_framework.h"

// 全局测试统计变量
int test_count = 0;
int test_passed = 0;
int test_failed = 0;

void init_test_framework(void) {
    test_count = 0;
    test_passed = 0;
    test_failed = 0;
    printf("[==========] Running tests.\n");
    printf("[----------] Global test environment set-up.\n");
}

void print_test_results(void) {
    printf("[----------] Global test environment tear-down\n");
    printf("[==========] %d test(s) ran.\n", test_count);
    
    if (test_failed == 0) {
        printf("[  PASSED  ] %d test(s).\n", test_passed);
    } else {
        printf("[  FAILED  ] %d test(s), listed below:\n", test_failed);
        printf("[  PASSED  ] %d test(s).\n", test_passed);
    }
}

int run_all_tests(void) {
    return (test_failed == 0) ? 0 : 1;
}