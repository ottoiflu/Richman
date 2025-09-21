#include "game.h"
#include <stdio.h>

void init_game(Game *game) {
    printf("请输入玩家人数（2-4）：");
    scanf("%d", &game->num_players);
    if (game->num_players < 2 || game->num_players > 4) {
        game->num_players = 2;
        printf("人数非法，默认2人。\n");
    }
    printf("请输入初始资金（1000-50000，默认10000）：");
    scanf("%d", &game->init_money);
    if (game->init_money < 1000 || game->init_money > 50000) {
        game->init_money = 10000;
        printf("资金非法，默认10000元。\n");
    }
    init_players(game->players, game->num_players, game->init_money);
    init_map(game->map);
    game->current_player = 0;
    printf("游戏初始化完成！\n");
}
