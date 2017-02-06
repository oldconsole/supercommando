
#include <stdio.h>
#include <stdlib.h>
#include "map.h"

Map *MapCreate(char orientation) {
	Map *map;
	map = (Map *)malloc(sizeof(Map));
	memset(map, 0, sizeof(Map));
	map->orientation = orientation;
	return map;
}

void MapRelease(Map *map) {
	if (map == NULL)
		return;
	while (MapSectionCount(map) > 0)
		MapSectionRemove(map, 0);
	free(map);
}

int MapSectionCount(Map *map) {
	if (map == NULL)
		return 0;
	return map->count;
}

void MapSectionAdd(Map *map, unsigned char *mapData, unsigned char *collisionData) {
	MapSection *section;
	MapSection *sectionLast;
	if (map == NULL || mapData == NULL || collisionData == NULL)
		return;
	if (map->orientation == ORIENT_HORZ) {
		map->width += 256;
		map->height = 256;
	}
	else {
		map->width = 256;
		map->height += 256;
	}
	map->count++;
	section = (MapSection *)malloc(sizeof(MapSection));
	section->mapData = mapData;
	section->collisionData = collisionData;
	section->pNext = NULL;
	if (map->sections == NULL) {
		section->pPrev = NULL;
		map->sections = section;
		return;
	}
	//Add the section to the end.
	sectionLast = map->sections;
	while (sectionLast->pNext)
		sectionLast = sectionLast->pNext;
	sectionLast->pNext = section;
	section->pPrev = sectionLast;
}

void MapSectionRemove(Map *map, int index) {
	MapSection *section;
	if (map == NULL || index < 0 || index >= MapSectionCount(map))
		return;
	section = map->sections;
	while (index-- > 0)
		section = section->pNext;
	if (section->pPrev)
		section->pPrev->pNext = section->pNext;
	else
		map->sections = section->pNext;
	if (section->pNext)
		section->pNext->pPrev = section->pPrev;
	free(section);
	map->count--;
}

int MapGetXY(Map *map, int x, int y) {
	MapSection *section;
	if (map == NULL || x < 0 || x >= map->width || y < 0 || y >= map->height)
		return -1;
	section = map->sections;
	if (map->orientation == ORIENT_HORZ) {
		while (x >= 256) {
			section = section->pNext;
			x -= 256;
		}
	}
	else {
		while (y >= 256) {
			section = section->pNext;
			y -= 256;
		}
	}
	x /= 8;
	y /= 8;
	return (section->mapData[y * 64 + x * 2] | (section->mapData[y * 64 + x * 2 + 1] << 8));
}

unsigned char *MapDataGet(Map *map, int scrollX, int scrollY, char index) {
	MapSection *section;
	int ind = 0;
	int track = 256;
	if (map == NULL)
		return NULL;
	section = map->sections;
	if (map->orientation == ORIENT_HORZ) {
		while (1) {
			if (section == NULL)
				return NULL;		
			if (index == ind && scrollX < track)
				return section->mapData;
			section = section->pNext;
			ind = (ind  == 0) ? 1 : 0;
			track += 256;
		}
	}
	else {
		while (1) {
			if (section == NULL)
				return NULL;		
			if (index == ind && scrollY < track)
				return section->mapData;
			section = section->pNext;
			ind = (ind  == 0) ? 1 : 0;
			track += 256;
		}
	}
	return NULL;
}

unsigned char MapCollisionGetTile(Map *map, int x, int y) {
	MapSection *section;
	if (map == NULL || x < 0 || x >= map->width || y < 0 || y >= map->height)
		return COLLISION_OUTOFBOUNDS;
	section = map->sections;
	if (map->orientation == ORIENT_HORZ) {
		while (x >= 256) {
			section = section->pNext;
			x -= 256;
		}
	}
	else {
		while (y >= 256) {
			section = section->pNext;
			y -= 256;
		}
	}
	x /= 8;
	y /= 8;
	return section->collisionData[(y * 32 + x)];
}

Point *MapCollisionGetPoint(Map *map, int x, int y) {
	MapSection *section;
	static Point pt;
	if (map == NULL || x < 0 || x >= map->width || y < 0 || y >= map->height)
		return NULL;
	section = map->sections;
	if (map->orientation == ORIENT_HORZ) {
		while (x >= 256) {
			section = section->pNext;
			x -= 256;
		}
	}
	else {
		while (y >= 256) {
			section = section->pNext;
			y -= 256;
		}
	}
	x /= 8;
	y /= 8;
	pt.x = map->scrollX + x * 8;
	pt.y = map->scrollY + y * 8;
	return &pt;
}

BOOL MapCanScroll(Map *map, int amount) {
	if (map->orientation == ORIENT_HORZ) {
		if (amount >= 0 && map->scrollX + amount < map->width - 256)
			return TRUE;
		else if (amount < 0 && map->scrollX + amount >= 0)
			return TRUE;
	}
	else {
		if (amount >= 0 && map->scrollY + amount < map->height - 256)
			return TRUE;
		else if (amount < 0 && map->scrollY + amount >= 0)
			return TRUE;
	}
	return FALSE;
}

void MapScroll(Map *map, int amount) {
	if (!MapCanScroll(map, amount))
		return;
	if (map->orientation == ORIENT_HORZ) {
		map->scrollX += amount;
		if (amount > 0)
			map->scrollX2++;
		else
			map->scrollX2--;
	}
	else {
		map->scrollY += amount;
		if (amount > 0)
			map->scrollY2++;
		else
			map->scrollY2--;		
	}
}

void MapScrollPosSet(Map *map, int pos) {
	if (map->orientation == ORIENT_HORZ)
		map->scrollX = pos;
	else
		map->scrollY = pos;
}

void MapSetXY(unsigned char *map, int x, int y, unsigned int tile) {
	map[y * 64 + x * 2] = (unsigned char)(tile & 0xff);
	map[y * 64 + x * 2 + 1] = (unsigned char)((tile & 0x300) >> 8);
}