// src/command_registry.c - 命令注册系统实现
#include "common.h"

// =============================================================================
// 全局注册表
// =============================================================================
static CommandRegistration g_command_registry[MAX_REGISTERED_COMMANDS];
static int g_registered_count = 0;
static int g_registry_initialized = 0;

// =============================================================================
// 命令注册系统核心实现
// =============================================================================

void command_registry_init(void) {
    if (g_registry_initialized) return;
    
    // 清空注册表
    for (int i = 0; i < MAX_REGISTERED_COMMANDS; i++) {
        memset(&g_command_registry[i], 0, sizeof(CommandRegistration));
    }
    
    g_registered_count = 0;
    g_registry_initialized = 1;
    
    // printf("命令注册系统已初始化\n"); // 静默初始化
}

int register_command(const char* command, const char* description, 
                    CommandHandler handler, const char* module_name) {
    if (!g_registry_initialized) {
        command_registry_init();
    }
    
    if (!command || !description || !handler || !module_name) {
        printf("注册命令失败：参数无效\n");
        return 0;
    }
    
    if (g_registered_count >= MAX_REGISTERED_COMMANDS) {
        printf("注册命令失败：已达到最大命令数量限制\n");
        return 0;
    }
    
    // 检查命令是否已存在
    if (find_command(command) != NULL) {
        printf("注册命令失败：命令 '%s' 已存在\n", command);
        return 0;
    }
    
    // 注册新命令
    CommandRegistration* reg = &g_command_registry[g_registered_count];
    strncpy(reg->command, command, sizeof(reg->command) - 1);
    strncpy(reg->description, description, sizeof(reg->description) - 1);
    strncpy(reg->module_name, module_name, sizeof(reg->module_name) - 1);
    reg->handler = handler;
    reg->is_active = 1;
    
    g_registered_count++;
    // printf("已注册命令：%s [%s]\n", command, module_name); // 静默注册
    return 1;
}

int unregister_command(const char* command) {
    if (!command) return 0;
    
    for (int i = 0; i < g_registered_count; i++) {
        if (strcmp(g_command_registry[i].command, command) == 0) {
            g_command_registry[i].is_active = 0;
            printf("已注销命令：%s\n", command);
            return 1;
        }
    }
    return 0;
}

const CommandRegistration* find_command(const char* command) {
    if (!command) return NULL;
    
    for (int i = 0; i < g_registered_count; i++) {
        if (g_command_registry[i].is_active && 
            strcmp(g_command_registry[i].command, command) == 0) {
            return &g_command_registry[i];
        }
    }
    return NULL;
}

CommandResult execute_registered_command(const char* command, const char* args) {
    if (!command) return CMD_ERROR;
    
    const CommandRegistration* reg = find_command(command);
    if (!reg) {
        return CMD_UNKNOWN;
    }
    
    // 执行命令处理函数
    return reg->handler(args);
}

// =============================================================================
// 命令查询接口实现
// =============================================================================

int get_registered_command_count(void) {
    int count = 0;
    for (int i = 0; i < g_registered_count; i++) {
        if (g_command_registry[i].is_active) {
            count++;
        }
    }
    return count;
}

void get_all_command_names(char* buffer, size_t buffer_size) {
    if (!buffer || buffer_size == 0) return;
    
    buffer[0] = '\0';
    int first = 1;
    
    for (int i = 0; i < g_registered_count; i++) {
        if (g_command_registry[i].is_active) {
            if (!first) {
                strncat(buffer, "|", buffer_size - strlen(buffer) - 1);
            }
            strncat(buffer, g_command_registry[i].command, buffer_size - strlen(buffer) - 1);
            first = 0;
        }
    }
}

void show_registered_commands(void) {
    printf("=== 已注册的游戏命令 ===\n");
    if (get_registered_command_count() == 0) {
        printf("暂无注册的命令\n");
        return;
    }
    
    for (int i = 0; i < g_registered_count; i++) {
        if (g_command_registry[i].is_active) {
            printf("%-15s - %s [%s]\n", 
                   g_command_registry[i].command,
                   g_command_registry[i].description,
                   g_command_registry[i].module_name);
        }
    }
}

int is_game_command(const char* command) {
    return find_command(command) != NULL;
}

// =============================================================================
// 模块管理接口实现
// =============================================================================

void show_registered_modules(void) {
    printf("=== 已注册的模块 ===\n");
    
    // 统计每个模块的命令数量
    char modules[MAX_REGISTERED_COMMANDS][64];
    int module_counts[MAX_REGISTERED_COMMANDS];
    int module_count = 0;
    
    for (int i = 0; i < g_registered_count; i++) {
        if (!g_command_registry[i].is_active) continue;
        
        // 查找模块是否已存在
        int found = -1;
        for (int j = 0; j < module_count; j++) {
            if (strcmp(modules[j], g_command_registry[i].module_name) == 0) {
                found = j;
                break;
            }
        }
        
        if (found >= 0) {
            module_counts[found]++;
        } else {
            strcpy(modules[module_count], g_command_registry[i].module_name);
            module_counts[module_count] = 1;
            module_count++;
        }
    }
    
    for (int i = 0; i < module_count; i++) {
        printf("%-20s - %d 个命令\n", modules[i], module_counts[i]);
    }
}

void show_commands_by_module(const char* module_name) {
    if (!module_name) return;
    
    printf("=== 模块 '%s' 的命令 ===\n", module_name);
    int found = 0;
    
    for (int i = 0; i < g_registered_count; i++) {
        if (g_command_registry[i].is_active && 
            strcmp(g_command_registry[i].module_name, module_name) == 0) {
            printf("%-15s - %s\n", 
                   g_command_registry[i].command,
                   g_command_registry[i].description);
            found = 1;
        }
    }
    
    if (!found) {
        printf("该模块没有注册的命令\n");
    }
}