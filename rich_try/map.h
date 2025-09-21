#ifndef MAP_H
#define MAP_H

#define MAP_SIZE 70

typedef enum {
    START, EMPTY, TOOL, GIFT, MAGIC, HOSPITAL, PRISON, MINE
} LandType;

typedef struct {
    int id;
    LandType type;
    int owner; // -1表示无主
    int level; // 房屋等级
    int price;
    int points; // 矿地点数
} Land;

void init_map(Land map[]);

#endif
