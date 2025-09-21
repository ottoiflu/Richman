#include <stdio.h>

int remote_roll_dice(int remote_value) {
    if (remote_value >= 1 && remote_value <= 6) {
        printf("从遥控器获取骰子点数：%d\n", remote_value);
        return remote_value;
    } else {
        printf("错误：遥控器传入了一个无效的点数：%d\n", remote_value);
        return -1;
    }
}

int main() {
    int dice_roll_from_remote = 4;
    int result = remote_roll_dice(dice_roll_from_remote);
    
    if (result != -1) {
        printf("游戏角色移动 %d 步。\n", result);
    }

    return 0;
}
