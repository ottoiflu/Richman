// include/player.h
#ifndef PLAYER_H
#define PLAYER_H

// 道具类型定义
typedef enum {
    PROP_NONE,
    PROP_ROADBLOCK, // 路障
    PROP_BOMB,      // 炸弹
    PROP_ROBOT      // 机器娃娃
} PropType;

#define MAX_PROPS 10

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

// 函数声明
void set_initial_money(int money);
void choose_player(Player* player, int player_id);
void show_character_list();

#endif // PLAYER_H