
#include <stdio.h>
#include "snes.h"
#include "util.h"
#include "map.h"
#include "bull.h"

#define MAX_FREE 48

#define BULLET_FRIEND_FRAME0 92
#define BULLET_FRIEND_FRAME1 124
#define BULLET_FOE_FRAME0 93
#define BULLET_FOE_FRAME1 125

#define BULLET_SPEED 15

#define BULLET_OFFSET 7

static Bullet *g_bulletsUsed = NULL;
static Bullet *g_bulletsFree = NULL;
static BOOL g_render = TRUE;
static int g_offset = 0;
static char g_frame = BULLET_FRIEND_FRAME0;
static int g_mapOldScrollX = 0;
static int g_mapOldScrollY = 0;

void BulletManagerInit() {
	Bullet *bullet;
	int i;
	for (i = 0; i < MAX_FREE; i++) {
		bullet = (Bullet *)malloc(sizeof(Bullet));
		memset(bullet, 0, sizeof(Bullet));
		if (g_bulletsFree == NULL) {
			bullet->pNext = NULL;
			bullet->pPrev = NULL;
			g_bulletsFree = bullet;
		}
		else {
			bullet->pNext = g_bulletsFree;
			bullet->pPrev = NULL;
			g_bulletsFree->pPrev = bullet;
			g_bulletsFree = bullet;
		}
	}
}

void BulletManagerRelease() {
	Bullet *bullet;
	Bullet *bulletTemp;
	bullet = g_bulletsUsed;
	while (bullet) {
		bulletTemp = bullet->pNext;
		free(bullet);
		bullet = bulletTemp;
	}
	g_bulletsUsed = NULL;
	bullet = g_bulletsFree;
	while (bullet) {
		bulletTemp = bullet->pNext;
		free(bullet);
		bullet = bulletTemp;
	}
	g_bulletsFree = NULL;
}

void BulletManagerAdd(int startX, int startY, int stepX, int stepY, int type) {
	Bullet *bullet;	
	Bullet *bulletTemp;
	if (g_bulletsFree == NULL)
		return;
	g_bulletsFree->x = startX;
	g_bulletsFree->y = startY;
	g_bulletsFree->stepX = stepX;
	g_bulletsFree->stepY = stepY;
	g_bulletsFree->type = type;
	if (type == BULLET_TYPE_FRIEND)
		g_bulletsFree->frame = BULLET_FRIEND_FRAME0;
	else
		g_bulletsFree->frame = BULLET_FOE_FRAME0;
	bulletTemp = g_bulletsFree;
	if (g_bulletsFree->pNext)
		g_bulletsFree->pNext->pPrev = NULL;
	g_bulletsFree = g_bulletsFree->pNext;
	if (g_bulletsUsed) {
		bulletTemp->pNext = g_bulletsUsed;
		g_bulletsUsed->pPrev = bulletTemp;
	}
	else {
		bulletTemp->pNext = NULL;
	}
	g_bulletsUsed = bulletTemp;
}

void BulletManagerRenderFriend() {
	Bullet *bullet;
	bullet = g_bulletsUsed;
	if (g_render == FALSE) {
		g_render = TRUE;
		return;
	}
	while (bullet) {
		if (bullet->type != BULLET_TYPE_FRIEND) {
			bullet = bullet->pNext;
			continue;
		}
		setsprite(SpriteAlloc(), bullet->x, bullet->y, g_frame, 31, 0, 0);
		bullet = bullet->pNext;
	}
	g_offset = (g_offset == BULLET_OFFSET) ? 0 : BULLET_OFFSET;	
	g_render = FALSE;
	g_frame = (g_frame == BULLET_FRIEND_FRAME0) ? BULLET_FRIEND_FRAME1 : BULLET_FRIEND_FRAME0;
}

void BulletManagerRenderFoe() {
	Bullet *bullet;
	bullet = g_bulletsUsed;
	while (bullet) {
		if (bullet->type != BULLET_TYPE_FOE) {
			bullet = bullet->pNext;
			continue;
		}
		setsprite(SpriteAlloc(), bullet->x, bullet->y, bullet->frame, 31, 0, 0);
		bullet->frame = (bullet->frame == BULLET_FOE_FRAME0) ? BULLET_FOE_FRAME1 : BULLET_FOE_FRAME0;
		bullet = bullet->pNext;
	}
}

void BulletManagerUpdate(struct Map_Tag *map) {
	Bullet *bullet;
	Bullet *bulletTemp;
	bullet = g_bulletsUsed;
	while (bullet) {
		if (bullet->type == BULLET_TYPE_FRIEND) {
			bullet->x += bullet->stepX * BULLET_SPEED + bullet->stepX * g_offset;
			bullet->y += bullet->stepY * BULLET_SPEED + bullet->stepY * g_offset;
		}
		else {
			bullet->x += bullet->stepX;
			bullet->y += bullet->stepY;
		}
		bullet->x -= map->scrollX - g_mapOldScrollX;
		bullet->y -= map->scrollY - g_mapOldScrollY;
		if (bullet->x <= 0 || bullet->x >= 248 || bullet->y <= 0 || bullet->y >= 248) {
			bulletTemp = bullet->pNext;
			BulletManagerRemove(bullet);
			bullet = bulletTemp;
			continue;
		}
		bullet = bullet->pNext;
	}
	g_mapOldScrollX = map->scrollX;
	g_mapOldScrollY = map->scrollY;	
}

Bullet *BulletManagerBullets() {
	return g_bulletsUsed;
}

void BulletManagerRemove(Bullet *bullet) {
	if (bullet == NULL)
		return;
	if (bullet->pNext)
		bullet->pNext->pPrev = bullet->pPrev;
	if (bullet->pPrev)
		bullet->pPrev->pNext = bullet->pNext;
	else
		g_bulletsUsed = bullet->pNext;
	bullet->pPrev = NULL;
	bullet->pNext = NULL;
	if (g_bulletsFree) {
		bullet->pNext = g_bulletsFree;				
		g_bulletsFree->pPrev = bullet;
	}
	g_bulletsFree = bullet;	
}