// include/command_processor.h - 统一命令处理模块
#ifndef COMMAND_PROCESSOR_H
#define COMMAND_PROCESSOR_H

#ifdef __cplusplus
extern "C" {
#endif

// 命令结构体，参考terminal.c设计
typedef struct {
    char instruction[32];
    int parameter;
    char extra_param[64];
} CommandStructure;

// 命令处理结果
typedef enum {
    CMD_SUCCESS = 0,
    CMD_ERROR = -1,
    CMD_UNKNOWN = -2,
    CMD_EXIT = 1
} CommandResult;

// 统一的命令处理接口
CommandResult process_cli_command(int argc, char* argv[]);
CommandResult process_game_command(const char* cmd_line);
void process_interactive_mode(void);

// 内部辅助函数
void parse_command_line(const char* input, CommandStructure* cmd);
CommandResult validate_command(const char* cmd, int expected_params, int actual_params);
void show_command_error(const char* cmd, const char* error_msg);
void turn_to_standard_case(char* instruction);

#ifdef __cplusplus
}
#endif

#endif // COMMAND_PROCESSOR_H