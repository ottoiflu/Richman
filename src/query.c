#include <stdio.h>
#include "player.h"
#include "query.h"

void query_player(const Player* player) {
	printf("玩家资产信息：\n");
	printf("编号：%d\n", player->id);
	printf("角色：%s\n", player->character);
	printf("资金：%d\n", player->money);
	printf("当前位置：%d\n", player->position);
	printf("地产数量：%d\n", player->properties);
	printf("状态：%s\n", player->is_bankrupt ? "破产" : "正常");
}
