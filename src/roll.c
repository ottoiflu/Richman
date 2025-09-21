#include "roll.h"

int roll_number(){
   if(player->prison_turns > 0) {
       printf("你在监狱中，不能掷骰子。\n");
       return 0; 
   }
   else if(player->hospital_turns > 0) {
       printf("你在医院中，不能掷骰子。\n");
       return 0; 
   }
   else{
   int number = rand() % 6 + 1; 
   printf("骰子的点数为: %d\n", number);
   return number;
   }
}