int arrive_prison(Player* player) {
    if(player->position==49)
    {
       printf("玩家%s进入了监狱，需要停留在此\n",player->character);
       player->prison_turns=3;//在监狱里等三天
       while(player->prison_turns>0)
       {
          printf("玩家%s还需要在监狱里待%d天\n",player->character,player->prison_turns);
          player->prison_turns--;
       }
        if(player->prision_turns==0){
         printf("玩家%s离开监狱了\n",player->character);
         return 1;
       }
    }
    else
    {
       return 0;
    }
}