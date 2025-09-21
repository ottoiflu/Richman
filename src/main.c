// src/main.c - Rich 大富翁程序主入口
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hello.h"

// 全局游戏状态
GameState g_game;

void print_usage() {
    printf("Rich - 大富翁程序\n");
    printf("用法:\n");
    printf("  rich testhelloworld    - 运行hello world测试\n");
    printf("  rich help             - 显示帮助信息\n");
    printf("  rich < cmdfile        - 从文件读取命令执行\n");
}

int process_command(const char* cmd_line) {
    char cmd[256], arg1[256], arg2[256], arg3[256];
    int args_count = sscanf(cmd_line, "%s %s %s %s", cmd, arg1, arg2, arg3);
    
    if (args_count < 1) return 0;
    
    if (strcmp(cmd, "preset") == 0 && args_count >= 3) {
        if (strcmp(arg1, "user") == 0) {
            game_preset_user(&g_game, arg2);
        } else if (strcmp(arg1, "fund") == 0 && args_count >= 4) {
            game_preset_fund(&g_game, arg2[0], atoi(arg3));
        } else if (strcmp(arg1, "userloc") == 0 && args_count >= 4) {
            int days = (args_count >= 5) ? atoi(arg3) : 0;
            game_preset_userloc(&g_game, arg2[0], atoi(arg3), days);
        } else if (strcmp(arg1, "nextuser") == 0) {
            game_preset_nextuser(&g_game, arg2[0]);
        }
        return 1;
    } else if (strcmp(cmd, "dump") == 0) {
        game_dump(&g_game, "dump.txt");
        printf("游戏状态已输出到 dump.txt\n");
        return 1;
    }
    
    return 0;
}

int main(int argc, char* argv[]) {
    // 初始化游戏状态
    game_init(&g_game);
    
    // 如果有命令行参数，按原来的方式处理
    if (argc >= 2) {
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
    
    // 如果没有命令行参数，从标准输入读取命令
    char line[1024];
    while (fgets(line, sizeof(line), stdin)) {
        // 移除换行符
        line[strcspn(line, "\n")] = 0;
        
        // 跳过空行和注释行
        if (strlen(line) == 0 || (line[0] == '/' && line[1] == '/')) {
            continue;
        }
        
        // 处理命令
        if (!process_command(line)) {
            // 如果不是游戏命令，可能是单独的dump命令
            if (strcmp(line, "dump") == 0) {
                game_dump(&g_game, "dump.txt");
                printf("游戏状态已输出到 dump.txt\n");
            }
        }
    }
    
    return 0;
}