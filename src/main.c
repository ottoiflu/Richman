#include "player.h"
#include "query.h"

int main() {
    Player p;
    choose_player(&p, 2); // 选择阿土伯
    query_player(&p);     // 显示资产信息
    return 0;
}