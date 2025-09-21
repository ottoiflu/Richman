// src/game_state.c - 游戏状态管理模块实现
#include "common.h"

// =============================================================================
// 全局变量和状态管理
// =============================================================================
static GameState g_game_state;

// =============================================================================
// Player模块实现 - 开发者：张弛
// =============================================================================

// 角色列表定义 - 开发者：张弛
static Character character_list[] = {
    {1, "钱夫人", "红色", 'Q'},
    {2, "阿土伯", "绿色", 'A'},
    {3, "孙小美", "蓝色", 'S'},
    {4, "金贝贝", "黄色", 'J'}
};

#define CHARACTER_COUNT (sizeof(character_list)/sizeof(character_list[0]))

// =============================================================================
// 基础游戏状态管理
// =============================================================================

GameState* get_game_state(void) {
    return &g_game_state;
}

void game_init(GameState* state) {
    if (!state) return;
    
    // 初始化游戏状态
    state->player_count = 0;
    state->current_player_index = 0;
    state->initial_money = 10000;  // 默认初始资金 - 开发者：张弛
    
    // 初始化所有玩家
    for (int i = 0; i < MAX_PLAYERS; i++) {
        Player* player = &state->players[i];
        player->id = 0;
        memset(player->character, 0, sizeof(player->character));
        player->symbol = 0;
        player->money = 0;
        player->points = 0;
        player->position = 0;
        player->is_bankrupt = 0;
        player->god_of_wealth_turns = 0;
        player->hospital_turns = 0;
        player->prison_turns = 0;
        
        // 初始化道具
        for (int j = 0; j < MAX_PROPS; j++) {
            player->props[j] = PROP_NONE;
        }
    }
}

void game_cleanup(GameState* state) {
    if (!state) return;
    // TODO: 添加清理逻辑（如果需要）
}

// =============================================================================
// Player功能实现 - 开发者：张弛
// =============================================================================

void set_initial_money(int money) {
    GameState* state = get_game_state();
    if (money >= 1000 && money <= 50000) {
        state->initial_money = money;
        printf("初始资金已设置为：%d\n", state->initial_money);
    } else {
        printf("资金范围无效（1000-50000），将使用默认值 %d\n", state->initial_money);
    }
}

int get_initial_money(void) {
    return get_game_state()->initial_money;
}

void choose_player(Player* player, int player_id) {
    if (!player) return;
    
    for (int i = 0; i < CHARACTER_COUNT; i++) {
        if (character_list[i].id == player_id) {
            player->id = character_list[i].id;
            strncpy(player->character, character_list[i].name, sizeof(player->character)-1);
            player->character[sizeof(player->character)-1] = '\0';
            player->symbol = character_list[i].symbol;
            player->money = get_initial_money(); // 使用设置的初始资金
            player->points = 0;
            player->position = 0;
            player->is_bankrupt = 0;
            player->god_of_wealth_turns = 0;
            player->hospital_turns = 0;
            player->prison_turns = 0;
            for (int j = 0; j < MAX_PROPS; j++) {
                player->props[j] = PROP_NONE;
            }
            printf("已选择角色：%s（%s）\n", character_list[i].name, character_list[i].color);
            return;
        }
    }
    printf("角色编号无效！\n");
}

void show_character_list(void) {
    printf("请选择2～4位不重复玩家，输入编号即可（1、钱夫人；2、阿土伯；3、孙小美；4、金贝贝）：\n");
    for (int i = 0; i < CHARACTER_COUNT; i++) {
        printf("%d. %s（%s）\n", character_list[i].id, character_list[i].name, character_list[i].color);
    }
}

int init_player_count(void) {
    int count = 0;
    printf("请输入玩家数量（2-4）：");
    if (scanf("%d", &count) != 1) {
        printf("输入无效，退出。\n");
        exit(1);
    }
    if (count < 2 || count > 4) {
        printf("玩家数量无效，退出。\n");
        exit(1);
    }
    getchar(); // 清除换行符
    return count;
}

// =============================================================================
// Player查询功能 - 开发者：张弛
// =============================================================================

const Character* get_character_list(void) {
    return character_list;
}

int get_character_count(void) {
    return CHARACTER_COUNT;
}

const Character* get_character_by_id(int id) {
    for (int i = 0; i < CHARACTER_COUNT; i++) {
        if (character_list[i].id == id) {
            return &character_list[i];
        }
    }
    return NULL;
}

void show_player_info(const Player* player) {
    if (!player || player->id == 0) {
        printf("玩家信息无效\n");
        return;
    }
    
    printf("=== 玩家信息 ===\n");
    printf("角色：%s (%c)\n", player->character, player->symbol);
    printf("资金：%d\n", player->money);
    printf("点数：%d\n", player->points);
    printf("位置：%d\n", player->position);
    printf("状态：%s\n", player->is_bankrupt ? "破产" : "正常");
    
    if (player->god_of_wealth_turns > 0) {
        printf("财神附身：剩余 %d 回合\n", player->god_of_wealth_turns);
    }
    if (player->hospital_turns > 0) {
        printf("住院中：剩余 %d 回合\n", player->hospital_turns);
    }
    if (player->prison_turns > 0) {
        printf("监狱中：剩余 %d 回合\n", player->prison_turns);
    }
    
    // 显示道具
    int prop_count = 0;
    for (int i = 0; i < MAX_PROPS; i++) {
        if (player->props[i] != PROP_NONE) {
            prop_count++;
        }
    }
    printf("道具数量：%d\n", prop_count);
}

int is_player_valid(const Player* player) {
    return player && player->id >= 1 && player->id <= 4;
}

// =============================================================================
// Player模块命令处理函数 - 开发者：张弛
// =============================================================================

CommandResult cmd_set_money(const char* args) {
    if (!args || strlen(args) == 0) {
        show_command_error("set_money", "需要指定金额参数");
        return CMD_ERROR;
    }
    int money = atoi(args);
    set_initial_money(money);
    return CMD_SUCCESS;
}

CommandResult cmd_show_characters(const char* args) {
    show_character_list();
    return CMD_SUCCESS;
}

CommandResult cmd_choose_player(const char* args) {
    if (!args || strlen(args) == 0) {
        show_command_error("choose_player", "需要指定角色编号参数");
        return CMD_ERROR;
    }
    int player_id = atoi(args);
    GameState* state = get_game_state();
    
    if (state->player_count >= MAX_PLAYERS) {
        printf("玩家数量已达上限\n");
        return CMD_ERROR;
    }
    
    choose_player(&state->players[state->player_count], player_id);
    state->player_count++;
    return CMD_SUCCESS;
}

CommandResult cmd_show_player(const char* args) {
    GameState* state = get_game_state();
    
    if (!args || strlen(args) == 0) {
        // 显示所有玩家信息
        if (state->player_count == 0) {
            printf("暂无玩家\n");
            return CMD_SUCCESS;
        }
        for (int i = 0; i < state->player_count; i++) {
            printf("=== 玩家 %d ===\n", i + 1);
            show_player_info(&state->players[i]);
            printf("\n");
        }
    } else {
        // 显示指定玩家信息
        int player_index = atoi(args) - 1;
        if (player_index < 0 || player_index >= state->player_count) {
            printf("玩家编号无效\n");
            return CMD_ERROR;
        }
        show_player_info(&state->players[player_index]);
    }
    return CMD_SUCCESS;
}

// =============================================================================
// Player模块初始化和注册 - 开发者：张弛
// =============================================================================

void player_module_init(void) {
    // 注册Player模块的所有命令
    register_command("set_money", "设置初始资金", cmd_set_money, "Player-张弛");
    register_command("show_characters", "显示角色列表", cmd_show_characters, "Player-张弛");
    register_command("choose_player", "选择玩家角色", cmd_choose_player, "Player-张弛");
    register_command("show_player", "显示玩家信息", cmd_show_player, "Player-张弛");
}