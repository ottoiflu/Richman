#ifndef PLAYER_H
#define PLAYER_H

#define MAX_PLAYERS 4
#define MAX_NAME_LEN 20

typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    int money;
    int points;
    // 其他资产、道具等后续补充
} Player;

void init_players(Player players[], int num_players, int init_money);

#endif
