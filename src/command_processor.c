// src/command_processor.c - 统一命令处理模块（使用命令注册系统）
#include "common.h"

// 基础CLI命令表（保留hello world测试功能）
static char cli_commands[][20] = {"testhelloworld", "help", "version", "list-game-commands", ""};

// 全局命令结构体
static CommandStructure g_cmd_struct;

// =============================================================================
// 命令解析和格式化
// =============================================================================

// 解析命令行输入
void parse_command_line(const char* input, CommandStructure* cmd) {
    if (!input || !cmd) return;
    
    // 初始化结构体
    memset(cmd, 0, sizeof(CommandStructure));
    
    // 解析命令和参数
    sscanf(input, "%31s %63s %d", cmd->instruction, cmd->extra_param, &cmd->parameter);
    
    // 标准化命令格式
    turn_to_standard_case(cmd->instruction);
}

// 标准化命令大小写
void turn_to_standard_case(char* instruction) {
    if (!instruction) return;
    
    // 首字母大写
    if (instruction[0] >= 'a' && instruction[0] <= 'z') {
        instruction[0] -= 32;
    }
    
    // 其余字母小写
    for (int i = 1; instruction[i] != 0; i++) {
        if (instruction[i] >= 'A' && instruction[i] <= 'Z') {
            instruction[i] += 32;
        }
    }
}

// 显示命令错误信息
void show_command_error(const char* cmd, const char* error_msg) {
    if (cmd) {
        printf("错误: %s '%s'\n", error_msg, cmd);
    } else {
        printf("错误: %s\n", error_msg);
    }
}

// 验证命令参数
CommandResult validate_command(const char* cmd, int expected_params, int actual_params) {
    if (expected_params == 0 && actual_params > 1) {
        show_command_error(cmd, "此命令不应有参数");
        return CMD_ERROR;
    }
    if (expected_params > 0 && actual_params < expected_params + 1) {
        show_command_error(cmd, "参数不足");
        return CMD_ERROR;
    }
    return CMD_SUCCESS;
}

// =============================================================================
// CLI命令处理（保留基础功能）
// =============================================================================

CommandResult process_cli_command(int argc, char* argv[]) {
    if (argc < 2) {
        return CMD_SUCCESS; // 进入交互模式
    }
    
    const char* cmd = argv[1];
    
    // 查找CLI命令表
    for (int i = 0; cli_commands[i][0]; i++) {
        if (strcmp(cmd, cli_commands[i]) == 0) {
            switch (i) {
                case 0: // testhelloworld
                    if (validate_command(cmd, 0, argc - 1) == CMD_SUCCESS) {
                        char buffer[100];
                        hello_say_hello(buffer, sizeof(buffer));
                        printf("%s\n", buffer);
                        return CMD_EXIT;
                    }
                    return CMD_ERROR;
                    
                case 1: // help
                    if (validate_command(cmd, 0, argc - 1) == CMD_SUCCESS) {
                        print_usage();
                        printf("\n");
                        show_registered_commands(); // 显示注册的游戏命令
                        return CMD_EXIT;
                    }
                    return CMD_ERROR;
                    
                case 2: // version
                    if (validate_command(cmd, 0, argc - 1) == CMD_SUCCESS) {
                        print_version();
                        return CMD_EXIT;
                    }
                    return CMD_ERROR;
                    
                case 3: // list-game-commands (用于测试脚本)
                    if (validate_command(cmd, 0, argc - 1) == CMD_SUCCESS) {
                        char buffer[1024];
                        get_all_command_names(buffer, sizeof(buffer));
                        printf("%s\n", buffer);
                        return CMD_EXIT;
                    }
                    return CMD_ERROR;
            }
        }
    }
    
    // 未知命令
    show_command_error(cmd, "未知命令");
    print_usage();
    return CMD_ERROR;
}

// =============================================================================
// 游戏命令处理（使用命令注册系统）
// =============================================================================

CommandResult process_game_command(const char* cmd_line) {
    if (!cmd_line) return CMD_ERROR;
    
    parse_command_line(cmd_line, &g_cmd_struct);
    
    // 将首字母大写的命令转换为小写（匹配注册时的格式）
    char lowercase_cmd[32];
    strncpy(lowercase_cmd, g_cmd_struct.instruction, sizeof(lowercase_cmd) - 1);
    lowercase_cmd[sizeof(lowercase_cmd) - 1] = '\0';
    
    // 转换为小写
    for (int i = 0; lowercase_cmd[i]; i++) {
        if (lowercase_cmd[i] >= 'A' && lowercase_cmd[i] <= 'Z') {
            lowercase_cmd[i] += 32;
        }
    }
    
    // 使用命令注册系统执行命令
    CommandResult result = execute_registered_command(lowercase_cmd, g_cmd_struct.extra_param);
    
    if (result == CMD_UNKNOWN) {
        printf("未知游戏命令: %s\n", lowercase_cmd);
        printf("使用 'help' 查看可用命令\n");
    }
    
    return result;
}

// =============================================================================
// 交互模式处理
// =============================================================================

void process_interactive_mode(void) {
    char line[MAX_LINE_LENGTH];
    
    while (fgets(line, sizeof(line), stdin)) {
        // 移除换行符
        line[strcspn(line, "\n")] = 0;
        
        // 跳过空行和注释行
        if (strlen(line) == 0 || (line[0] == '/' && line[1] == '/')) {
            continue;
        }
        
        // 处理特殊命令
        if (strcmp(line, "help") == 0) {
            print_usage();
            printf("\n");
            show_registered_commands();
            continue;
        }
        
        if (strcmp(line, "modules") == 0) {
            show_registered_modules();
            continue;
        }
        
        if (strcmp(line, "exit") == 0 || strcmp(line, "quit") == 0) {
            printf("再见！\n");
            break;
        }
        
        // 处理游戏命令
        CommandResult result = process_game_command(line);
        
        // 可以在这里添加特殊命令处理
        if (result == CMD_UNKNOWN) {
            // 已在 process_game_command 中处理
        }
    }
}