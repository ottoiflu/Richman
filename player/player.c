#include "player.h"

int roll_number(){
   int number = rand() % 6 + 1; // 生成1到6之间的随机数
   printf("Rolled number: %d\n", number);
   return number;
}