#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "game.h"
#include "display.h"

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

    srand(time(NULL)); // 初始化随机数种子

    init_game(&game);

    // 清除scanf留下的换行符
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    while (1) {
        system("clear");
        draw_map(&game);

        Player *current_player = &game.players[game.current_player];
        printf("%s%s%s> ", get_player_color(current_player->id), current_player->name, COLOR_RESET);

        if (fgets(cmd, sizeof(cmd), stdin) == NULL) {
            continue;
        }
        cmd[strcspn(cmd, "\n")] = 0; // 去除换行符

        if (strcasecmp(cmd, "help") == 0) {
            print_help();
            printf("按回车键继续...");
            while (getchar()!='\n'); // 等待用户按回车
        } else if (strcasecmp(cmd, "quit") == 0) {
            printf("游戏结束，感谢游玩！\n");
            break;
        } else if (strncasecmp(cmd, "roll", 4) == 0) {
            int steps = (rand() % 6) + 1;
            printf("%s掷骰子，点数为：%d\n", current_player->name, steps);
            current_player->position = (current_player->position + steps) % MAP_SIZE;
            printf("%s移动到了位置 %d\n", current_player->name, current_player->position);
            
            // 移动后的事件处理逻辑可以放在这里
            
            game.current_player = (game.current_player + 1) % game.num_players;
            printf("按回车键结束回合...");
            while (getchar()!='\n'); // 等待用户按回车
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
            printf("资产查询 (%s):\n", current_player->name);
            printf("资金: %d 元\n", current_player->money);
            printf("点数: %d 点\n", current_player->points);
            
            printf("地产: ");
            int land_count = 0;
            for (int i = 0; i < MAP_SIZE; i++) {
                if (game.map[i].owner == current_player->id) {
                    printf("%d(Lv%d) ", i, game.map[i].level);
                    land_count++;
                }
            }
            if (land_count == 0) {
                printf("无");
            }
            printf("\n");

            printf("道具:\n");
            printf("  路障: %d个\n", current_player->roadblocks);
            printf("  炸弹: %d个\n", current_player->bombs);
            printf("  机器娃娃: %d个\n", current_player->robots);

            if (current_player->god_of_wealth_turns > 0) {
                printf("财神附身: 剩余 %d 回合\n", current_player->god_of_wealth_turns);
            }

            printf("\n按回车键继续...");
            // 清理输入缓冲区，防止直接跳过
            int temp_char;
            while ((temp_char = getchar()) != '\n' && temp_char != EOF);
            // 等待用户按回车
            while ((temp_char = getchar()) != '\n' && temp_char != EOF);
            
        } else if (strncasecmp(cmd, "step", 4) == 0) {
            // 遥控骰子
            printf("执行遥控骰子命令...\n");
            game.current_player = (game.current_player + 1) % game.num_players;
        } else {
            printf("无效命令，请重新输入。\n");
            printf("按回车键继续...");
            while (getchar()!='\n'); // 等待用户按回车
        }
    }

    return 0;
}

