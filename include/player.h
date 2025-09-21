#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int id;               // 玩家编号
    char character[32];        // 玩家角色
    int money;            // 玩家资金
    int position;         // 玩家当前位置
    int properties;       // 玩家拥有的地产数量
    int is_bankrupt;      // 是否破产（1为破产，0为正常）
} Player;



#endif // PLAYER_H