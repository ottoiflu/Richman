#include "roll.h"

int roll_number(){
   int number = rand() % 6 + 1; 
   printf("骰子的点数为: %d\n", number);
   return number;
}