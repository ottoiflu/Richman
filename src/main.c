// src/main.c - Rich 大富翁程序主入口
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hello.h"

void print_usage() {
    printf("Rich - 大富翁程序\n");
    printf("用法:\n");
    printf("  rich testhelloworld    - 运行hello world测试\n");
    printf("  rich help             - 显示帮助信息\n");
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }
    
    if (strcmp(argv[1], "testhelloworld") == 0) {
        char buffer[100];
        hello_say_hello(buffer, sizeof(buffer));
        printf("%s\n", buffer);
        return 0;
    }
    else if (strcmp(argv[1], "help") == 0) {
        print_usage();
        return 0;
    }
    else {
        printf("错误: 未知命令 '%s'\n", argv[1]);
        print_usage();
        return 1;
    }
}