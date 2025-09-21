#include "display.h"
#include <stdio.h>

char get_land_symbol(LandType type) {
    switch (type) {
        case START: return 'S';
        case HOSPITAL: return 'H';
        case TOOL: return 'T';
        case GIFT: return 'G';
        case MAGIC: return 'M';
        case PRISON: return 'P';
        case MINE: return '$';
        case EMPTY: return '0';
        default: return ' ';
    }
}

char get_player_symbol(int player_id) {
    switch (player_id) {
        case 0: return 'Q'; // 钱夫人
        case 1: return 'A'; // 阿土伯
        case 2: return 'S'; // 孙小美
        case 3: return 'J'; // 金贝贝
        default: return ' ';
    }
}

const char* get_player_color(int player_id) {
    switch (player_id) {
        case 0: return COLOR_RED;    // 钱夫人
        case 1: return COLOR_GREEN;  // 阿土伯
        case 2: return COLOR_BLUE;   // 孙小美
        case 3: return COLOR_YELLOW; // 金贝贝
        default: return COLOR_RESET;
    }
}

void draw_map(Game *game) {
    char display_map[MAP_SIZE];

    // 1. 初始化地图符号
    for (int i = 0; i < MAP_SIZE; i++) {
        display_map[i] = get_land_symbol(game->map[i].type);
    }

    // 2. 覆盖玩家符号
    for (int i = 0; i < game->num_players; i++) {
        int pos = game->players[i].position;
        char player_symbol[20];
        sprintf(player_symbol, "%s%c%s", get_player_color(game->players[i].id), get_player_symbol(game->players[i].id), COLOR_RESET);
        // 注意：这里直接将带颜色的字符串存入char数组，打印时需要特殊处理
        // 为了简化，我们直接在打印时加颜色
    }

    // 3. 打印地图
    // 上边
    for (int i = 0; i <= 28; i++) {
        char symbol_to_print = get_land_symbol(game->map[i].type);
        int player_on_land = -1;
        for(int p=0; p < game->num_players; ++p) {
            if(game->players[p].position == i) {
                player_on_land = p;
                break;
            }
        }
        if(player_on_land != -1) {
            printf("%s%c%s", get_player_color(player_on_land), get_player_symbol(player_on_land), COLOR_RESET);
        } else {
            printf("%c", symbol_to_print);
        }
    }
    printf("\n");

    // 两侧
    for (int i = 0; i < 6; i++) {
        // 左侧
        char symbol_to_print_left = get_land_symbol(game->map[69 - i].type);
        int player_on_land_left = -1;
        for(int p=0; p < game->num_players; ++p) {
            if(game->players[p].position == (69 - i)) {
                player_on_land_left = p;
                break;
            }
        }
        if(player_on_land_left != -1) {
            printf("%s%c%s", get_player_color(player_on_land_left), get_player_symbol(player_on_land_left), COLOR_RESET);
        } else {
            printf("%c", symbol_to_print_left);
        }

        for (int j = 0; j < 27; j++) {
            printf(" ");
        }

        // 右侧
        char symbol_to_print_right = get_land_symbol(game->map[29 + i].type);
        int player_on_land_right = -1;
        for(int p=0; p < game->num_players; ++p) {
            if(game->players[p].position == (29 + i)) {
                player_on_land_right = p;
                break;
            }
        }
        if(player_on_land_right != -1) {
            printf("%s%c%s", get_player_color(player_on_land_right), get_player_symbol(player_on_land_right), COLOR_RESET);
        } else {
            printf("%c", symbol_to_print_right);
        }
        printf("\n");
    }

    // 下边
    for (int i = 63; i >= 35; i--) {
        char symbol_to_print = get_land_symbol(game->map[i].type);
        int player_on_land = -1;
        for(int p=0; p < game->num_players; ++p) {
            if(game->players[p].position == i) {
                player_on_land = p;
                break;
            }
        }
        if(player_on_land != -1) {
            printf("%s%c%s", get_player_color(player_on_land), get_player_symbol(player_on_land), COLOR_RESET);
        } else {
            printf("%c", symbol_to_print);
        }
    }
    printf("\n");
}
