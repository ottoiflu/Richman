#include "map.h"

void init_map(Land map[]) {
    for (int i = 0; i < MAP_SIZE; i++) {
        map[i].id = i;
        map[i].owner = -1;
        map[i].level = 0;
        map[i].price = 0;
        map[i].points = 0;
        map[i].type = EMPTY; // 默认为空地
    }

    // 地段1: 0-27
    map[0].type = START;
    map[14].type = HOSPITAL;
    map[28].type = TOOL;

    for (int i = 1; i <= 13; i++) { map[i].price = 200; }
    for (int i = 15; i <= 27; i++) { map[i].price = 200; }

    // 地段2: 29-34
    for (int i = 29; i <= 34; i++) { map[i].price = 500; }

    // 地段3: 35-62
    map[35].type = PRISON;
    map[49].type = MAGIC;
    map[63].type = GIFT;

    for (int i = 36; i <= 48; i++) { map[i].price = 300; }
    for (int i = 50; i <= 62; i++) { map[i].price = 300; }

    // 矿地: 64-69
    map[64].type = MINE; map[64].points = 20;
    map[65].type = MINE; map[65].points = 80;
    map[66].type = MINE; map[66].points = 100;
    map[67].type = MINE; map[67].points = 40;
    map[68].type = MINE; map[68].points = 80;
    map[69].type = MINE; map[69].points = 60;
}
