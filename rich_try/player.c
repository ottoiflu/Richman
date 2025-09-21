#include "player.h"
#include <stdio.h>
#include <string.h>

static const char *default_names[MAX_PLAYERS] = {"钱夫人", "阿土伯", "孙小美", "金贝贝"};

void init_players(Player players[], int num_players, int init_money) {
    for (int i = 0; i < num_players; i++) {
        players[i].id = i;
        strncpy(players[i].name, default_names[i], MAX_NAME_LEN);
        players[i].money = init_money;
        players[i].points = 0;
        // 其他初始化
    }
}
