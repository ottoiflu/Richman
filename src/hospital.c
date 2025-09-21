int arrive_hospital(Player* player) {
    if(player->hospital==49)
    {
       printf("玩家%s进入了医院，需要停留在此\n",player->character);
       player->hospital_turns=3;//在监狱里等三天
       while(player->hospital_turns>0)
       {
          printf("%s还需要在医院里待%d天\n",player->character,player->hospital_turns);
          player->hospital_turns--;
       }
       if(player->hospital_turns==0){
         printf("玩家%s离开医院了\n",player->character);
         return 1;
       }
    }
    else
    {
       return 0;
    }
}