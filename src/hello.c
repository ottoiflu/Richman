// src/hello.c
#include "hello.h"

void hello_say_hello(char* buffer, size_t buffer_size) {
    if (buffer && buffer_size > 0) {
        strncpy(buffer, "Hello, World!", buffer_size - 1);
        buffer[buffer_size - 1] = '\0'; // 确保字符串结束
    }
}

void hello_say_hello_with_name(char* buffer, size_t buffer_size, const char* name) {
    if (buffer && buffer_size > 0 && name) {
        snprintf(buffer, buffer_size, "Hello, %s!", name);
    }
}

void hello_get_greeting(char* buffer, size_t buffer_size) {
    if (buffer && buffer_size > 0) {
        strncpy(buffer, "Greetings from TDD!", buffer_size - 1);
        buffer[buffer_size - 1] = '\0'; // 确保字符串结束
    }
}

void hello_get_version(char* buffer, size_t buffer_size) {
    if (buffer && buffer_size > 0) {
        snprintf(buffer, buffer_size, "Rich v1.0.0 - 大富翁程序集成测试版");
    }
}

// 全局游戏状态（暂时保留，未来可能使用）
// static GameState g_game_state;

// 游戏功能实现
void game_init(GameState* state) {
    if (!state) return;
    
    // 初始化玩家
    state->player_count = 0;
    for (int i = 0; i < MAX_PLAYERS; i++) {
        state->players[i].name = 0;
        state->players[i].fund = 10000;  // 默认资金
        state->players[i].credit = 0;
        state->players[i].location = 0;
        state->players[i].hospital_days = 0;
        state->players[i].bomb_count = 0;
        state->players[i].barrier_count = 0;
        state->players[i].robot_count = 0;
        state->players[i].god_days = 0;
    }
    
    // 初始化地图
    for (int i = 0; i < MAX_LOCATIONS; i++) {
        state->map[i].owner_index = -1;
        state->map[i].level = 0;
    }
    
    // 初始化炸弹和路障
    state->bomb_count = 0;
    state->barrier_count = 0;
    state->next_player_index = 0;
}

void game_preset_user(GameState* state, const char* users) {
    if (!state || !users) return;
    
    state->player_count = 0;
    for (int i = 0; users[i] && i < MAX_PLAYERS; i++) {
        if (users[i] == 'A' || users[i] == 'Q' || users[i] == 'S' || users[i] == 'J') {
            state->players[state->player_count].name = users[i];
            state->player_count++;
        }
    }
}

void game_preset_fund(GameState* state, char player, int amount) {
    if (!state) return;
    
    for (int i = 0; i < state->player_count; i++) {
        if (state->players[i].name == player) {
            state->players[i].fund = amount;
            break;
        }
    }
}

void game_preset_userloc(GameState* state, char player, int location, int days) {
    if (!state) return;
    
    for (int i = 0; i < state->player_count; i++) {
        if (state->players[i].name == player) {
            state->players[i].location = location;
            state->players[i].hospital_days = days;
            break;
        }
    }
}

void game_preset_nextuser(GameState* state, char player) {
    if (!state) return;
    
    for (int i = 0; i < state->player_count; i++) {
        if (state->players[i].name == player) {
            state->next_player_index = i;
            break;
        }
    }
}

void game_dump(GameState* state, const char* filename) {
    if (!state || !filename) return;
    
    FILE* file = fopen(filename, "w");
    if (!file) return;
    
    // 输出用户信息
    fprintf(file, "user ");
    for (int i = 0; i < state->player_count; i++) {
        fprintf(file, "%c", state->players[i].name);
    }
    fprintf(file, "\n");
    
    // 输出地图信息（只输出有主人的地块）
    for (int i = 0; i < MAX_LOCATIONS; i++) {
        if (state->map[i].owner_index >= 0) {
            fprintf(file, "map[%d] %c %d\n", i, 
                   state->players[state->map[i].owner_index].name,
                   state->map[i].level);
        }
    }
    
    // 输出资金信息
    for (int i = 0; i < state->player_count; i++) {
        fprintf(file, "fund %c %d\n", 
               state->players[i].name, state->players[i].fund);
    }
    
    // 输出点数信息
    for (int i = 0; i < state->player_count; i++) {
        if (state->players[i].credit > 0) {
            fprintf(file, "credit %c %d\n", 
                   state->players[i].name, state->players[i].credit);
        }
    }
    
    // 输出位置信息
    for (int i = 0; i < state->player_count; i++) {
        if (state->players[i].hospital_days > 0) {
            fprintf(file, "userloc %c %d %d\n", 
                   state->players[i].name, state->players[i].location,
                   state->players[i].hospital_days);
        } else {
            fprintf(file, "userloc %c %d\n", 
                   state->players[i].name, state->players[i].location);
        }
    }
    
    // 输出下一个玩家
    if (state->next_player_index >= 0 && state->next_player_index < state->player_count) {
        fprintf(file, "nextuser %c\n", state->players[state->next_player_index].name);
    }
    
    fclose(file);
}