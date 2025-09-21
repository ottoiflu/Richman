// include/command_registry.h - 命令注册系统
#ifndef COMMAND_REGISTRY_H
#define COMMAND_REGISTRY_H

#ifdef __cplusplus
extern "C" {
#endif

// 最大注册命令数量
#define MAX_REGISTERED_COMMANDS 50

// 命令处理函数类型
typedef CommandResult (*CommandHandler)(const char* args);

// 命令注册结构体
typedef struct {
    char command[32];           // 命令名称
    char description[128];      // 命令描述
    CommandHandler handler;     // 处理函数
    char module_name[64];       // 模块名称（包含开发者）
    int is_active;             // 是否激活
} CommandRegistration;

// =============================================================================
// 命令注册系统核心接口
// =============================================================================

// 初始化命令注册系统
void command_registry_init(void);

// 注册命令
int register_command(const char* command, const char* description, 
                    CommandHandler handler, const char* module_name);

// 注销命令
int unregister_command(const char* command);

// 查找命令
const CommandRegistration* find_command(const char* command);

// 执行注册的命令
CommandResult execute_registered_command(const char* command, const char* args);

// =============================================================================
// 命令查询接口
// =============================================================================

// 获取所有注册的命令数量
int get_registered_command_count(void);

// 获取所有命令名称（用于测试脚本）
void get_all_command_names(char* buffer, size_t buffer_size);

// 显示所有注册的命令（帮助信息）
void show_registered_commands(void);

// 检查命令是否为游戏命令
int is_game_command(const char* command);

// =============================================================================
// 模块管理接口
// =============================================================================

// 显示所有模块信息
void show_registered_modules(void);

// 按模块显示命令
void show_commands_by_module(const char* module_name);

#ifdef __cplusplus
}
#endif

#endif // COMMAND_REGISTRY_H