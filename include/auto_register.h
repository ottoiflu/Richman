// include/auto_register.h - 自动注册宏系统
#ifndef AUTO_REGISTER_H
#define AUTO_REGISTER_H

#ifdef __cplusplus
extern "C" {
#endif

// =============================================================================
// 自动注册宏系统 - 让开发者专注于功能代码
// =============================================================================

// 自动注册命令的宏
// 使用 __attribute__((constructor)) 在程序启动时自动执行注册
#define DEFINE_COMMAND(cmd, desc, handler, module) \
    CommandResult handler(const char* args); \
    __attribute__((constructor)) \
    static void auto_register_##handler(void) { \
        register_command(cmd, desc, handler, module); \
    } \
    CommandResult handler(const char* args)

// 定义模块初始化函数（可选）
#define DEFINE_MODULE_INIT(module_name) \
    __attribute__((constructor)) \
    static void auto_init_##module_name(void) { \
        module_name##_init(); \
    } \
    static void module_name##_init(void)

// 定义静态数据（模块内部使用）
#define MODULE_DATA(type, name, ...) \
    static type name = __VA_ARGS__

// 获取游戏状态的便捷宏
#define GET_GAME_STATE() get_game_state()

// 参数验证宏
#define REQUIRE_ARGS(cmd_name) \
    if (!args || strlen(args) == 0) { \
        show_command_error(cmd_name, "需要参数"); \
        return CMD_ERROR; \
    }

#define VALIDATE_INT_RANGE(value, min, max, error_msg) \
    if (value < min || value > max) { \
        printf("参数错误: %s (范围: %d-%d)\n", error_msg, min, max); \
        return CMD_ERROR; \
    }

// 成功/失败返回的便捷宏
#define SUCCESS_MSG(msg) \
    do { printf(msg "\n"); return CMD_SUCCESS; } while(0)

#define ERROR_MSG(msg) \
    do { printf("错误: " msg "\n"); return CMD_ERROR; } while(0)

#ifdef __cplusplus
}
#endif

#endif // AUTO_REGISTER_H