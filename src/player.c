#include <stdio.h>
#include <string.h>
#include "player.h"


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

void choose_player(Player* player, int player_id) {
	for (int i = 0; i < CHARACTER_COUNT; i++) {
		if (character_list[i].id == player_id) {
			player->id = character_list[i].id;
			strncpy(player->character, character_list[i].name, sizeof(player->character)-1);
			player->character[sizeof(player->character)-1] = '\0';
			player->money = 10000; // 默认初始资金
			player->position = 0;
			player->properties = 0;
			player->is_bankrupt = 0;
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
