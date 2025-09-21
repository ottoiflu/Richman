// src/game_io.c - 输入输出处理模块实现
#include "common.h"

// 显示使用帮助
void print_usage(void) {
    printf("Rich - 大富翁程序\n");
    printf("用法:\n");
    printf("  rich testhelloworld    - 运行hello world测试\n");
    printf("  rich help             - 显示帮助信息\n");
    printf("  rich < cmdfile        - 从文件读取命令执行\n");
}

// 显示版本信息
void print_version(void) {
    char buffer[256];
    hello_get_version(buffer, sizeof(buffer));
    printf("%s\n", buffer);
}