// include/common.h - 统一头文件入口
#ifndef COMMON_H
#define COMMON_H

// 标准C库
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// 基础常量定义（可根据需要调整）
#define MAX_PLAYERS 4
#define MAX_LOCATIONS 70
#define MAX_CMD_LENGTH 256
#define MAX_LINE_LENGTH 1024

// 包含所有模块头文件
#include "game_types.h"      // 数据结构定义
#include "command_processor.h" // 统一命令处理（需要先包含，定义CommandResult）
#include "command_registry.h" // 命令注册系统
#include "auto_register.h"   // 自动注册宏系统
#include "game_state.h"      // 游戏状态管理
#include "game_io.h"         // 输入输出处理
#include "hello.h"           // Hello World功能（TDD基础测试）

#ifdef __cplusplus
}
#endif

#endif // COMMON_H