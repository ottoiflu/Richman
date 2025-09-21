// include/game_types.h - 游戏数据结构定义
#ifndef GAME_TYPES_H
#define GAME_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

// =============================================================================
// Player模块数据结构 - 开发者：张弛
// =============================================================================

// 道具类型定义
typedef enum {
    PROP_NONE,
    PROP_ROADBLOCK, // 路障
    PROP_BOMB,      // 炸弹
    PROP_ROBOT      // 机器娃娃
} PropType;

#define MAX_PROPS 10

// 玩家结构体定义 - 开发者：张弛
typedef struct {
    int id;                     // 玩家编号 (1-4)
    char character[32];         // 玩家角色名 (如: 钱夫人)
    char symbol;                // 地图显示符号 (Q, A, S, J)
    
    // 资产
    int money;                  // 资金
    int points;                 // 点数 (用于购买道具)
    PropType props[MAX_PROPS];  // 道具列表 (最多10个)
    
    // 状态
    int position;               // 当前在地图上的位置 (0-69)
    int is_bankrupt;            // 是否破产 (0: 否, 1: 是)
    int god_of_wealth_turns;    // 财神附身剩余回合数
    int hospital_turns;         // 医院中剩余回合数
    int prison_turns;           // 监狱中剩余回合数
} Player;

// 角色信息结构体 - 开发者：张弛
typedef struct {
    int id;
    char name[32];
    char color[16];
    char symbol; // 地图显示符号
} Character;

// =============================================================================
// 游戏状态结构体 - 待扩展
// =============================================================================

typedef struct {
    Player players[MAX_PLAYERS];
    int player_count;
    int current_player_index;
    int initial_money;          // 初始资金设置 - 开发者：张弛
    // TODO: 添加其他游戏状态（地图、回合等）
} GameState;

// TODO: 添加其他数据结构
// 例如：MapBlock, Property 等

#ifdef __cplusplus
}
#endif

#endif // GAME_TYPES_H