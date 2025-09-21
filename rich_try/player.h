#ifndef PLAYER_H
#define PLAYER_H

#define MAX_PLAYERS 4
#define MAX_NAME_LEN 20

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int money;
    int points;
    int position; // 玩家在地图上的位置
    int bombs; // 炸弹数量
    int roadblocks; // 路障数量
    int robots; // 机器娃娃数量
    int god_of_wealth_turns; // 财神附身剩余回合
    // 其他资产、道具等后续补充
} Player;

void init_players(Player players[], int num_players, int init_money);

#endif
