#include <stdio.h>
#include <string.h>
#include "player.h"

static int g_initial_money = 10000; // 默认初始资金

typedef struct {
	int id;
	char name[32];
	char color[16];
	char symbol; // 地图显示符号
} Character;

Character character_list[] = {
	{1, "钱夫人", "红色", 'Q'},
	{2, "阿土伯", "绿色", 'A'},
	{3, "孙小美", "蓝色", 'S'},
	{4, "金贝贝", "黄色", 'J'}
};

#define CHARACTER_COUNT (sizeof(character_list)/sizeof(character_list[0]))

void set_initial_money(int money) {
    if (money >= 1000 && money <= 50000) {
        g_initial_money = money;
        printf("初始资金已设置为：%d\n", g_initial_money);
    } else {
        printf("资金范围无效（1000-50000），将使用默认值 %d\n", g_initial_money);
    }
}

void choose_player(Player* player, int player_id) {
	for (int i = 0; i < CHARACTER_COUNT; i++) {
		if (character_list[i].id == player_id) {
			player->id = character_list[i].id;
			strncpy(player->character, character_list[i].name, sizeof(player->character)-1);
			player->character[sizeof(player->character)-1] = '\0';
			player->symbol = character_list[i].symbol;
			player->money = g_initial_money; // 使用设置的初始资金
			player->points = 0;
			player->position = 0;
			player->is_bankrupt = 0;
			player->god_of_wealth_turns = 0;
			player->hospital_turns = 0;
			player->prison_turns = 0;
			for (int j = 0; j < MAX_PROPS; j++) {
				player->props[j] = PROP_NONE;
			}
			printf("已选择角色：%s（%s）\n", character_list[i].name, character_list[i].color);
			return;
		}
	}
	printf("角色编号无效！\n");
}

void show_character_list() {
	printf("请选择2～4位不重复玩家，输入编号即可（1、钱夫人；2、阿土伯；3、孙小美；4、金贝贝）：\n");
	for (int i = 0; i < CHARACTER_COUNT; i++) {
		printf("%d. %s（%s）\n", character_list[i].id, character_list[i].name, character_list[i].color);
	}
}
