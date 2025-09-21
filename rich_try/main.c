#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "game.h"

void print_help() {
    printf("命令一览表：\n");
    printf("roll         掷骰子命令，行走1～6步\n");
    printf("sell n       出售房产，n为地图绝对位置\n");
    printf("block n      放置路障，n为前后相对距离（±10步）\n");
    printf("bomb n       放置炸弹，n为前后相对距离（±10步）\n");
    printf("robot        清扫前方10步内障碍\n");
    printf("query        显示自家资产信息\n");
    printf("help         查看命令帮助\n");
    printf("quit         强制退出游戏\n");
    printf("step n       遥控骰子，指定步数\n");
}

int main() {
    char cmd[100];
    Game game;

    init_game(&game);

    while (1) {
        Player *current_player = &game.players[game.current_player];
        printf("%s> ", current_player->name);

        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            continue;
        }
        cmd[strcspn(cmd, "\n")] = 0; // 去除换行符

        if (strcasecmp(cmd, "help") == 0) {
            print_help();
        } else if (strcasecmp(cmd, "quit") == 0) {
            printf("游戏结束，感谢游玩！\n");
            break;
        } else if (strncasecmp(cmd, "roll", 4) == 0) {
            // 掷骰子
            printf("执行掷骰子命令...\n");
            game.current_player = (game.current_player + 1) % game.num_players;
        } else if (strncasecmp(cmd, "sell", 4) == 0) {
            // 出售房产
            printf("执行出售房产命令...\n");
            game.current_player = (game.current_player + 1) % game.num_players;
        } else if (strncasecmp(cmd, "block", 5) == 0) {
            // 放置路障
            printf("执行放置路障命令...\n");
            game.current_player = (game.current_player + 1) % game.num_players;
        } else if (strncasecmp(cmd, "bomb", 4) == 0) {
            // 放置炸弹
            printf("执行放置炸弹命令...\n");
            game.current_player = (game.current_player + 1) % game.num_players;
        } else if (strncasecmp(cmd, "robot", 5) == 0) {
            // 使用机器娃娃
            printf("执行使用机器娃娃命令...\n");
            game.current_player = (game.current_player + 1) % game.num_players;
        } else if (strncasecmp(cmd, "query", 5) == 0) {
            // 查询资产
            printf("执行查询资产命令...\n");
            // 查询不消耗回合，所以不切换玩家
        } else if (strncasecmp(cmd, "step", 4) == 0) {
            // 遥控骰子
            printf("执行遥控骰子命令...\n");
            game.current_player = (game.current_player + 1) % game.num_players;
        } else {
            printf("无效命令，请重新输入。\n");
        }
    }

    return 0;
}
