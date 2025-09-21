#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "map.h"

typedef struct {
    Player players[MAX_PLAYERS];
    int num_players;
    int init_money;
    Land map[MAP_SIZE];
    int current_player;
} Game;

void init_game(Game *game);

#endif
