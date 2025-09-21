#ifndef DISPLAY_H
#define DISPLAY_H

// ANSI Color Codes
#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_RESET   "\x1b[0m"

#include "game.h"

void draw_map(Game *game);
const char* get_player_color(int player_id);

#endif
