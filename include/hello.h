// include/hello.h
#ifndef HELLO_H
#define HELLO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

// 问候功能函数声明
// 注意：C语言中我们使用字符数组而不是std::string
void hello_say_hello(char* buffer, size_t buffer_size);
void hello_say_hello_with_name(char* buffer, size_t buffer_size, const char* name);
void hello_get_greeting(char* buffer, size_t buffer_size);

// 版本信息功能函数声明 - 新功能示例
void hello_get_version(char* buffer, size_t buffer_size);

// 大富翁游戏数据结构和函数声明
#define MAX_PLAYERS 4
#define MAX_LOCATIONS 70

typedef struct {
    char name;              // A, Q, S, J
    int fund;              // 资金
    int credit;            // 点数
    int location;          // 位置
    int hospital_days;     // 住院天数
    int bomb_count;        // 炸弹数量
    int barrier_count;     // 路障数量
    int robot_count;       // 机器人数量
    int god_days;          // 财神天数
} Player;

typedef struct {
    int owner_index;       // 拥有者索引 (-1表示无主)
    int level;            // 等级
} MapBlock;

typedef struct {
    Player players[MAX_PLAYERS];
    int player_count;
    MapBlock map[MAX_LOCATIONS];
    int bomb_locations[10];
    int bomb_count;
    int barrier_locations[10];
    int barrier_count;
    int next_player_index;
} GameState;

// 游戏功能函数声明
void game_init(GameState* state);
void game_preset_user(GameState* state, const char* users);
void game_preset_fund(GameState* state, char player, int amount);
void game_preset_userloc(GameState* state, char player, int location, int days);
void game_preset_nextuser(GameState* state, char player);
void game_dump(GameState* state, const char* filename);

#ifdef __cplusplus
}
#endif

#endif /* HELLO_H */