
#include <stdio.h>
#include "snes.h"
#include "util.h"
#include "spr.h"
#include "exp.h"

#define MAX_FREE 32

#define EXPLOSION_FRAME0 0
#define EXPLOSION_FRAME1 1
#define EXPLOSION_FRAME2 2
#define EXPLOSION_FRAME3 3

typedef struct Explosion_Tag {
	struct Explosion_Tag *pNext;
	struct Explosion_Tag *pPrev;
	int x;
	int y;
	int stepX;
	int stepY;
	char frame;
}Explosion;

static Explosion *g_explosionsUsed = NULL;
static Explosion *g_explosionsFree = NULL;

static Sprite g_explosionSprites[] = {
	//EXPLOSION_FRAME0
	{130, 0, 0, 0, 0},
	{131, 0, 0, 8, 0},
	{162, 0, 0, 0, 8},
	{163, 0, 0, 8, 8},
	//EXPLOSION_FRAME1
	{132, 0, 0, 0, 0},
	{133, 0, 0, 8, 0},
	{164, 0, 0, 0, 8},
	{165, 0, 0, 8, 8},
	//EXPLOSION_FRAME2
	{134, 0, 0, 0, 0},
	{135, 0, 0, 8, 0},
	{166, 0, 0, 0, 8},
	{167, 0, 0, 8, 8},
	//EXPLOSION_FRAME3
	{136, 0, 0, 0, 0},
	{137, 0, 0, 8, 0},
	{168, 0, 0, 0, 8},
	{169, 0, 0, 8, 8}
};

void ExplosionManagerInit() {
	Explosion *explosion;
	int i;
	for (i = 0; i < MAX_FREE; i++) {
		explosion = (Explosion *)malloc(sizeof(Explosion));
		memset(explosion, 0, sizeof(Explosion));
		if (g_explosionsFree == NULL) {
			explosion->pNext = NULL;
			explosion->pPrev = NULL;
			g_explosionsFree = explosion;
		}
		else {
			explosion->pNext = g_explosionsFree;
			explosion->pPrev = NULL;
			g_explosionsFree->pPrev = explosion;
			g_explosionsFree = explosion;
		}
	}
}

void ExplosionManagerRelease() {
	Explosion *explosion;
	Explosion *explosionTemp;
	explosion = g_explosionsUsed;
	while (explosion) {
		explosionTemp = explosion->pNext;
		free(explosion);
		explosion = explosionTemp;
	}
	g_explosionsUsed = NULL;
	explosion = g_explosionsFree;
	while (explosion) {
		explosionTemp = explosion->pNext;
		free(explosion);
		explosion = explosionTemp;
	}
	g_explosionsFree = NULL;
}

void ExplosionManagerAdd(int startX, int startY, int stepX, int stepY) {
	Explosion *explosion;	
	Explosion *explosionTemp;
	if (g_explosionsFree == NULL)
		return;
	g_explosionsFree->x = startX;
	g_explosionsFree->y = startY;
	g_explosionsFree->stepX = stepX;
	g_explosionsFree->stepY = stepY;
	g_explosionsFree->frame = -1;
	explosionTemp = g_explosionsFree;
	if (g_explosionsFree->pNext)
		g_explosionsFree->pNext->pPrev = NULL;
	g_explosionsFree = g_explosionsFree->pNext;	
	if (g_explosionsUsed) {
		explosionTemp->pNext = g_explosionsUsed;
		g_explosionsUsed->pPrev = explosionTemp;
	}
	else {
		explosionTemp->pNext = NULL;
	}
	g_explosionsUsed = explosionTemp;
}

void ExplosionManagerUpdate() {
	Explosion *explosion;
	Explosion *explosionTemp;
	explosion = g_explosionsUsed;
	while (explosion) {
		explosion->x += explosion->stepX;
		explosion->y += explosion->stepY;
		if (explosion->frame == EXPLOSION_FRAME3 || 
			explosion->x <= 0 || 
			explosion->x >= 248 || 
			explosion->y <= 0 || 
			explosion->y >= 248) {
			explosionTemp = explosion->pNext;				
			if (explosion->pNext)
				explosion->pNext->pPrev = explosion->pPrev;
			if (explosion->pPrev)
				explosion->pPrev->pNext = explosion->pNext;
			else
				g_explosionsUsed = explosion->pNext;
			explosion->pPrev = NULL;
			explosion->pNext = NULL;
			if (g_explosionsFree) {
				explosion->pNext = g_explosionsFree;				
				g_explosionsFree->pPrev = explosion;
			}
			g_explosionsFree = explosion;
			explosion = explosionTemp;
			continue;
		}
		explosion->frame++;		
		explosion = explosion->pNext;
	}
}

void ExplosionManagerRender() {
	Explosion *explosion;
	Sprite *sprite;
	explosion = g_explosionsUsed;
	while (explosion) {
		sprite = &g_explosionSprites[explosion->frame * 4];
		setsprite(SpriteAlloc(), explosion->x + sprite->offX, explosion->y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
		sprite = &g_explosionSprites[explosion->frame * 4 + 1];
		setsprite(SpriteAlloc(), explosion->x + sprite->offX, explosion->y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
		sprite = &g_explosionSprites[explosion->frame * 4 + 2];
		setsprite(SpriteAlloc(), explosion->x + sprite->offX, explosion->y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
		sprite = &g_explosionSprites[explosion->frame * 4 + 3];
		setsprite(SpriteAlloc(), explosion->x + sprite->offX, explosion->y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);		
		explosion = explosion->pNext;
	}
}