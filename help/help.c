void print_help_message(){
printf("欢迎进入命令提示界面\n");
printf("可用命令有：\n");
printf("1. roll -    通过掷骰子来前进\n");
printf("2. help -    显示帮助信息\n");
printf("3. quit -    强制退出程序\n"); 
printf("4. query -   查询当前玩家的信息\n");
printf("5. step n -  指定前几步数（开发者测试）\n");
printf("6. sell n -  出售自己的房产，n为地图上绝对位置");
printf("7. block n - 将路障放在距离当前位置前后10步任何位置。正数为前方，负数为后方\n");
printf("8. bomb n -  将炸弹放在距离当前位置前后10步任何位置。正数为前方，负数为后方\n");
printf("9. robot -   清除前方10步以内任何道具\n");
printf("请输入命令：\n");
}