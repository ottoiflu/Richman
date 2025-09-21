// include/game_state.h - 游戏状态管理模块
#ifndef GAME_STATE_H
#define GAME_STATE_H

#ifdef __cplusplus
extern "C" {
#endif

// =============================================================================
// 基础游戏状态管理
// =============================================================================
GameState* get_game_state(void);
void game_init(GameState* state);
void game_cleanup(GameState* state);

// =============================================================================
// Player功能接口 - 开发者：张弛
// =============================================================================

// 初始资金管理
void set_initial_money(int money);
int get_initial_money(void);

// 角色选择和初始化
void choose_player(Player* player, int player_id);
void show_character_list(void);
int init_player_count(void);

// 角色信息查询
const Character* get_character_list(void);
int get_character_count(void);
const Character* get_character_by_id(int id);

// 玩家状态查询
void show_player_info(const Player* player);
int is_player_valid(const Player* player);

// =============================================================================
// Player模块命令处理和初始化 - 开发者：张弛
// =============================================================================

// 命令处理函数
CommandResult cmd_set_money(const char* args);
CommandResult cmd_show_characters(const char* args);
CommandResult cmd_choose_player(const char* args);
CommandResult cmd_show_player(const char* args);

// 模块初始化
void player_module_init(void);

#ifdef __cplusplus
}
#endif

#endif // GAME_STATE_H