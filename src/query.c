#include <stdio.h>
#include "player.h"
#include "query.h"

void query_player(const Player* player) {
    printf("玩家资产信息：\n");
    printf("编号：%d\n", player->id);
    printf("角色：%s\n", player->character);
    printf("符号：%c\n", player->symbol);
    printf("资金：%d\n", player->money);
    printf("点数：%d\n", player->points);
    printf("当前位置：%d\n", player->position);
    printf("破产状态：%s\n", player->is_bankrupt ? "破产" : "正常");
    printf("财神附身剩余回合：%d\n", player->god_of_wealth_turns);
    printf("医院剩余回合：%d\n", player->hospital_turns);
    printf("监狱剩余回合：%d\n", player->prison_turns);
    printf("道具：");
    int has_prop = 0;
    for (int i = 0; i < MAX_PROPS; i++) {
        switch (player->props[i]) {
            case PROP_ROADBLOCK: printf("#(路障) "); has_prop = 1; break;
            case PROP_BOMB: printf("@(炸弹) "); has_prop = 1; break;
            case PROP_ROBOT: printf("机器人 "); has_prop = 1; break;
            default: break;
        }
    }
    if (!has_prop) printf("无");
    printf("\n");
}
