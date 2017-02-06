
#ifndef _MAP_H_
#define _MAP_H_

#include "util.h"
#include "pt.h"

#define ORIENT_HORZ 0
#define ORIENT_VERT 1

#define COLLISION_EMPTY 0
#define COLLISION_SOLID 1
#define COLLISION_EXIT 2
#define COLLISION_TOPSOLID 3
#define COLLISION_OUTOFBOUNDS 4

typedef struct MapSection_Tag {
	struct MapSection_Tag *pPrev;
	struct MapSection_Tag *pNext;
	unsigned char *mapData;
	unsigned char *collisionData;
}MapSection;

typedef struct Map_Tag {
	MapSection *sections;
	char orientation;
	int width;
	int height;
	int count;
	int scrollX;
	int scrollY;
	int scrollX2;
	int scrollY2;
}Map;

Map *MapCreate(char orientation);
void MapRelease(Map *map);
int MapSectionCount(Map *map);
void MapSectionAdd(Map *map, unsigned char *mapData, unsigned char *collisionData);
void MapSectionRemove(Map *map, int index);
unsigned char *MapDataGet(Map *map, int scrollX, int scrollY, char index);
unsigned char MapCollisionGetTile(Map *map, int x, int y);
Point *MapCollisionGetPoint(Map *map, int x, int y);
BOOL MapCanScroll(Map *map, int amount);
void MapScroll(Map *map, int amount);
void MapScrollPosSet(Map *map, int pos);

int MapGetXY(Map *map, int x, int y);
void MapSetXY(unsigned char *map, int xp, int yp, unsigned int tile);

#endif