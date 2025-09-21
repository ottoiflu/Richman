#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "player.h"
#include "query.h"

#define MAX_PLAYERS 4

Player players[MAX_PLAYERS];
int player_count = 0;
int current_player = 0;

void next_turn() {
    current_player = (current_player + 1) % player_count;
}

void process_command(const char* cmd) {
    if (strcmp(cmd, "query") == 0) {
        query_player(&players[current_player]);
    } else if (strcmp(cmd, "help") == 0) {
        printf("可用命令：query help quit\n");
    } else if (strcmp(cmd, "quit") == 0) {
        printf("游戏结束！\n");
        exit(0);
    } else {
        printf("未知命令，请输入 help 查看可用命令。\n");
    }
}



int main() {
    player_count = init_player_count();
    // 角色选择
    show_character_list();
    for (int i = 0; i < player_count; i++) {
        int id;
        printf("玩家%d选择角色编号：", i + 1);
        scanf("%d", &id);
        choose_player(&players[i], id);
    }
    getchar(); // 清除换行符

    // 主循环
    char cmd[64];
    while (1) {
        printf("\n%s> 待输入命令：", players[current_player].character);
        if (fgets(cmd, sizeof(cmd), stdin) == NULL) break;
        cmd[strcspn(cmd, "\n")] = 0; // 去除换行符
        if (strlen(cmd) == 0) continue;
        process_command(cmd);
        next_turn();
    }
    return 0;
}