
#include <stdio.h>
#include "snes.h"
#include "util.h"
#include "spr.h"
#include "map.h"
#include "obj.h"
#include "objs.h"
#include "bull.h"

Bullet *ObjCheckCollisionBullet(int x, int y, int width, int height) {
	Bullet *bullet;	
	Rect r1;
	Rect r2;
	RectSet(&r1, x, y, width, height);
	bullet = BulletManagerBullets();
	while (bullet) {
		if (bullet->type != BULLET_TYPE_FRIEND) {
			bullet = bullet->pNext;
			continue;
		}
		RectSet(&r2, bullet->x, bullet->y, 8, 8);
		if (RectInRect(&r1, &r2))
			return bullet;
		bullet = bullet->pNext;
	}
	return NULL;
}

BOOL ObjCheckCollisionCommando(int x, int y, int width, int height) {
	Rect r1;
	Rect r2;
	Point *pt;
	RectSet(&r1, x, y, width, height);
	pt = CommandoXY();
	RectSet(&r2, pt->x, pt->y, 16, 16);
	if (RectInRect(&r1, &r2))
		return TRUE;
	return FALSE;
}

#define MACHINEGUNNER_LEFT 0
#define MACHINEGUNNER_RIGHT 1

static Sprite g_spritesMachineGunner[] = {
	//MACHINEGUNNER_LEFT
	{64, 0, 0, 0, 0},
	{65, 0, 0, 8, 0},
	{96, 0, 0, 0, 8},
	{97, 0, 0, 8, 8},
	//MACHINEGUNNER_RIGHT
	{64, 1, 0, 8, 0},
	{65, 1, 0, 0, 0},
	{96, 1, 0, 8, 8},
	{97, 1, 0, 0, 8}
};

void ObjMachineGunnerCreate(struct Object_Tag *obj, struct Map_Tag *map) {
}

void ObjMachineGunnerRelease(struct Object_Tag *obj) {
}

void ObjMachineGunnerRender(struct Object_Tag *obj, struct Map_Tag *map) {
	Sprite *sprite = NULL;
	int x = obj->x - map->scrollX;
	int y = obj->y - map->scrollY;
	char frame;
	Point *pt;
	pt = CommandoXY();
	frame = (pt->x < x) ? MACHINEGUNNER_LEFT : MACHINEGUNNER_RIGHT;
	sprite = &g_spritesMachineGunner[frame * 4];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesMachineGunner[frame * 4 + 1];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesMachineGunner[frame * 4 + 2];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesMachineGunner[frame * 4 + 3];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);	
}

void ObjMachineGunnerUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map) {
	Bullet *bullet;
	Point *pt;
	int x = obj->x - map->scrollX;
	int y = obj->y - map->scrollY;	
	if ((bullet = ObjCheckCollisionBullet(obj->x - map->scrollX, obj->y - map->scrollY, 16, 16)) != NULL) {
		ExplosionManagerAdd(obj->x - map->scrollX, obj->y - map->scrollY, 0, -2);
		ObjectMapRemove(objMap, obj);
		BulletManagerRemove(bullet);
		return;
	}
	if (ObjCheckCollisionCommando(obj->x - map->scrollX, obj->y - map->scrollY, 16, 16))
		CommandoKill();
	if ((rand()%20) == 0) {
		pt = CommandoXY();
		if (pt->x < x)
			BulletManagerAdd(x - 8, y + 6, -3, 0, BULLET_TYPE_FOE);
		else
			BulletManagerAdd(x + 16, y + 6, 3, 0, BULLET_TYPE_FOE);
	}
}

#define TOPGUNNER_MIDDLE 0
#define TOPGUNNER_LEFT 1
#define TOPGUNNER_RIGHT 2

static Sprite g_spritesTopGunner[] = {
	//TOPGUNNER_MIDDLE
	{66, 0, 0, 0, 0},
	{67, 0, 0, 8, 0},
	{98, 0, 0, 0, 8},
	{99, 0, 0, 8, 8},
	//TOPGUNNER_LEFT
	{68, 0, 0, 0, 0},
	{69, 0, 0, 8, 0},
	{100, 0, 0, 0, 8},
	{101, 0, 0, 8, 8},
	//TOPGUNNER_RIGHT
	{68, 1, 0, 8, 0},
	{69, 1, 0, 0, 0},
	{100, 1, 0, 8, 8},
	{101, 1, 0, 0, 8}
};

void ObjTopGunnerCreate(struct Object_Tag *obj, struct Map_Tag *map) {
}

void ObjTopGunnerRelease(struct Object_Tag *obj) {
}

void ObjTopGunnerRender(struct Object_Tag *obj, struct Map_Tag *map) {
	Sprite *sprite = NULL;
	int frame;
	int x = obj->x - map->scrollX;
	int y = obj->y - map->scrollY;
	Point *pt;
	pt = CommandoXY();
	if (pt->x >= x - 40 && pt->x <= x + 40)
		frame = TOPGUNNER_MIDDLE;
	else if (pt->x < x)
		frame = TOPGUNNER_LEFT;
	else
		frame = TOPGUNNER_RIGHT;
	sprite = &g_spritesTopGunner[frame * 4];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesTopGunner[frame * 4 + 1];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesTopGunner[frame * 4 + 2];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesTopGunner[frame * 4 + 3];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);	
}

void ObjTopGunnerUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map) {
	Bullet *bullet;
	Point *pt;
	int x = obj->x - map->scrollX;
	int y = obj->y - map->scrollY;	
	if ((bullet = ObjCheckCollisionBullet(obj->x - map->scrollX, obj->y - map->scrollY, 16, 16)) != NULL) {
		ExplosionManagerAdd(obj->x - map->scrollX, obj->y - map->scrollY, 0, -2);
		ObjectMapRemove(objMap, obj);
		BulletManagerRemove(bullet);
		return;
	}
	if (ObjCheckCollisionCommando(obj->x - map->scrollX, obj->y - map->scrollY, 16, 16))
		CommandoKill();	
	if ((rand()%20) == 0) {
		pt = CommandoXY();
		if (pt->x >= x - 40 && pt->x <= x + 40)
			BulletManagerAdd(x + 4, y + 16, 0, 3, BULLET_TYPE_FOE);
		else if (pt->x < x)
			BulletManagerAdd(x - 4, y + 16, -3, 3, BULLET_TYPE_FOE);
		else
			BulletManagerAdd(x + 16, y + 16, 3, 3, BULLET_TYPE_FOE);			
	}
}

#define KNIFERUNNER_SPEED 6

#define KNIFERUNNER_LEFT_RUN0 0
#define KNIFERUNNER_LEFT_RUN1 1
#define KNIFERUNNER_RIGHT_RUN0 2
#define KNIFERUNNER_RIGHT_RUN1 3

typedef struct KnifeRunner_Tag {
	char frame;
}KnifeRunner;

Sprite g_spritesKnifeRunner[] = {
	//KNIFERUNNER_LEFT_RUN0
	{70, 0, 0, 0, 0},
	{71, 0, 0, 8, 0},
	{102, 0, 0, 0, 8},
	{103, 0, 0, 8, 8},
	//KNIFERUNNER_LEFT_RUN1
	{72, 0, 0, 0, 0},
	{73, 0, 0, 8, 0},
	{104, 0, 0, 0, 8},
	{105, 0, 0, 8, 8},
	//KNIFERUNNER_RIGHT_RUN0
	{70, 1, 0, 8, 0},
	{71, 1, 0, 0, 0},
	{102, 1, 0, 8, 8},
	{103, 1, 0, 0, 8},
	//KNIFERUNNER_RIGHT_RUN1
	{72, 1, 0, 8, 0},
	{73, 1, 0, 0, 0},
	{104, 1, 0, 8, 8},
	{105, 1, 0, 0, 8}	

};

void ObjKnifeRunnerCreate(struct Object_Tag *obj, struct Map_Tag *map) {
	KnifeRunner *kr;
	kr = (KnifeRunner *)malloc(sizeof(KnifeRunner));
	switch (obj->tile) {
		case OBJECT_KNIFERUNNERLEFT:
			obj->x -= 235;
			kr->frame = KNIFERUNNER_RIGHT_RUN0;
			break;
		case OBJECT_KNIFERUNNERRIGHT:
			kr->frame = KNIFERUNNER_LEFT_RUN0;
			break;
	}
	obj->context = kr;
}

void ObjKnifeRunnerRelease(struct Object_Tag *obj) {
	free(obj->context);
}

void ObjKnifeRunnerRender(struct Object_Tag *obj, struct Map_Tag *map) {
	Sprite *sprite = NULL;
	KnifeRunner *kr;
	int x;
	int y;
	x = obj->x - map->scrollX;
	y = obj->y - map->scrollY;
	kr = (KnifeRunner *)obj->context;
	sprite = &g_spritesKnifeRunner[kr->frame * 4];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesKnifeRunner[kr->frame * 4 + 1];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesKnifeRunner[kr->frame * 4 + 2];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesKnifeRunner[kr->frame * 4 + 3];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);	
}

void ObjKnifeRunnerUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map) {
	KnifeRunner *kr;
	Bullet *bullet;
	if ((bullet = ObjCheckCollisionBullet(obj->x - map->scrollX, obj->y - map->scrollY, 16, 16)) != NULL) {
		ExplosionManagerAdd(obj->x - map->scrollX, obj->y - map->scrollY, 0, -2);
		ObjectMapRemove(objMap, obj);
		BulletManagerRemove(bullet);
		return;
	}
	if (ObjCheckCollisionCommando(obj->x - map->scrollX, obj->y - map->scrollY, 16, 16))
		CommandoKill();	
	kr = (KnifeRunner *)obj->context;
	switch (obj->tile) {
		case OBJECT_KNIFERUNNERLEFT:
			kr->frame = (kr->frame == KNIFERUNNER_RIGHT_RUN0) ? KNIFERUNNER_RIGHT_RUN1 : KNIFERUNNER_RIGHT_RUN0;
			obj->x += KNIFERUNNER_SPEED;
			break;
		case OBJECT_KNIFERUNNERRIGHT:
			kr->frame = (kr->frame == KNIFERUNNER_LEFT_RUN0) ? KNIFERUNNER_LEFT_RUN1 : KNIFERUNNER_LEFT_RUN0;
			obj->x -= KNIFERUNNER_SPEED;
			break;
	}
}

#define DOG_SPEED 7

#define DOG_LEFT_RUN0 0
#define DOG_LEFT_RUN1 1
#define DOG_RIGHT_RUN0 2
#define DOG_RIGHT_RUN1 3

typedef struct Dog_Tag {
	char frame;
}Dog;

Sprite g_spritesDog[] = {
	//DOG_LEFT_RUN0
	{74, 0, 0, 0, 0},
	{75, 0, 0, 8, 0},
	{106, 0, 0, 0, 8},
	{107, 0, 0, 8, 8},
	//DOG_LEFT_RUN1
	{76, 0, 0, 0, 0},
	{77, 0, 0, 8, 0},
	{108, 0, 0, 0, 8},
	{109, 0, 0, 8, 8},
	//DOG_RIGHT_RUN0
	{74, 1, 0, 8, 0},
	{75, 1, 0, 0, 0},
	{106, 1, 0, 8, 8},
	{107, 1, 0, 0, 8},
	//DOG_RIGHT_RUN1
	{76, 1, 0, 8, 0},
	{77, 1, 0, 0, 0},
	{108, 1, 0, 8, 8},
	{109, 1, 0, 0, 8}
};

void ObjDogCreate(struct Object_Tag *obj, struct Map_Tag *map) {
	Dog *dog;
	dog = (Dog *)malloc(sizeof(KnifeRunner));
	switch (obj->tile) {
		case OBJECT_DOGLEFT:
			obj->x -= 235;
			dog->frame = DOG_RIGHT_RUN0;
			break;
		case OBJECT_DOGRIGHT:
			dog->frame = DOG_LEFT_RUN0;
			break;
	}
	obj->context = dog;
}

void ObjDogRelease(struct Object_Tag *obj) {
	free(obj->context);
}

void ObjDogRender(struct Object_Tag *obj, struct Map_Tag *map) {
	Sprite *sprite = NULL;
	Dog *dog;
	int x;
	int y;
	x = obj->x - map->scrollX;
	y = obj->y - map->scrollY;
	dog = (Dog *)obj->context;
	sprite = &g_spritesDog[dog->frame * 4];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesDog[dog->frame * 4 + 1];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesDog[dog->frame * 4 + 2];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesDog[dog->frame * 4 + 3];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);	
}

void ObjDogUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map) {
	Dog *dog;
	Bullet *bullet;
	if ((bullet = ObjCheckCollisionBullet(obj->x - map->scrollX, obj->y - map->scrollY + 8, 16, 8)) != NULL) {
		ExplosionManagerAdd(obj->x - map->scrollX, obj->y - map->scrollY, 0, -2);
		ObjectMapRemove(objMap, obj);
		BulletManagerRemove(bullet);
		return;
	}
	if (ObjCheckCollisionCommando(obj->x - map->scrollX, obj->y - map->scrollY, 16, 8))
		CommandoKill();	
	dog = (Dog *)obj->context;	
	switch (obj->tile) {
		case OBJECT_DOGLEFT:
			dog->frame = (dog->frame == DOG_RIGHT_RUN0) ? DOG_RIGHT_RUN1 : DOG_RIGHT_RUN0;
			obj->x += DOG_SPEED;
			break;
		case OBJECT_DOGRIGHT:
			dog->frame = (dog->frame == DOG_LEFT_RUN0) ? DOG_LEFT_RUN1 : DOG_LEFT_RUN0;
			obj->x -= DOG_SPEED;
			break;
	}
}

#define FLOORGUNNER_LEFT 0
#define FLOORGUNNER_RIGHT 1

static Sprite g_spritesFloorGunner[] = {
	//FLOORGUNNER_LEFT
	{78, 0, 0, 0, 0},
	{79, 0, 0, 8, 0},
	{110, 0, 0, 0, 8},
	{111, 0, 0, 8, 8},
	//FLOORGUNNER_RIGHT
	{78, 1, 0, 8, 0},
	{79, 1, 0, 0, 0},
	{110, 1, 0, 8, 8},
	{111, 1, 0, 0, 8}
};

void ObjFloorGunnerCreate(struct Object_Tag *obj, struct Map_Tag *map) {
}

void ObjFloorGunnerRelease(struct Object_Tag *obj) {
}

void ObjFloorGunnerRender(struct Object_Tag *obj, struct Map_Tag *map) {
	Sprite *sprite = NULL;
	int x = obj->x - map->scrollX;
	int y = obj->y - map->scrollY;
	char frame;
	Point *pt;
	pt = CommandoXY();
	frame = (pt->x < x) ? FLOORGUNNER_LEFT : FLOORGUNNER_RIGHT;
	sprite = &g_spritesFloorGunner[frame * 4];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesFloorGunner[frame * 4 + 1];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesFloorGunner[frame * 4 + 2];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesFloorGunner[frame * 4 + 3];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);	
}

void ObjFloorGunnerUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map) {
	Bullet *bullet;
	Point *pt;
	int x = obj->x - map->scrollX;
	int y = obj->y - map->scrollY;	
	if ((bullet = ObjCheckCollisionBullet(obj->x - map->scrollX, obj->y - map->scrollY + 8, 16, 8)) != NULL) {
		ExplosionManagerAdd(obj->x - map->scrollX, obj->y - map->scrollY, 0, -2);
		ObjectMapRemove(objMap, obj);
		BulletManagerRemove(bullet);
		return;
	}
	if (ObjCheckCollisionCommando(obj->x - map->scrollX, obj->y - map->scrollY, 16, 8))
		CommandoKill();	
	if ((rand()%20) == 0) {
		pt = CommandoXY();
		if (pt->x < x)
			BulletManagerAdd(x - 8, y + 8, -3, 0, BULLET_TYPE_FOE);
		else
			BulletManagerAdd(x + 16, y + 8, 3, 0, BULLET_TYPE_FOE);
	}	
}

#define SHELLBOMBER_LEFT 0
#define SHELLBOMBER_RIGHT 1

static Sprite g_spritesShellBomber[] = {
	//SHELLBOMBER_LEFT
	{80, 0, 0, 0, 0},
	{81, 0, 0, 8, 0},
	{112, 0, 0, 0, 8},
	{113, 0, 0, 8, 8},
	//SHELLBOMBER_RIGHT
	{80, 1, 0, 8, 0},
	{81, 1, 0, 0, 0},
	{112, 1, 0, 8, 8},
	{113, 1, 0, 0, 8}
};

void ObjShellBomberCreate(struct Object_Tag *obj, struct Map_Tag *map) {
}

void ObjShellBomberRelease(struct Object_Tag *obj) {
}

void ObjShellBomberRender(struct Object_Tag *obj, struct Map_Tag *map) {
	Sprite *sprite = NULL;
	int x = obj->x - map->scrollX;
	int y = obj->y - map->scrollY;
	char frame;
	Point *pt;
	pt = CommandoXY();
	frame = (pt->x < x) ? SHELLBOMBER_LEFT : SHELLBOMBER_RIGHT;
	sprite = &g_spritesShellBomber[frame * 4];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesShellBomber[frame * 4 + 1];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesShellBomber[frame * 4 + 2];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesShellBomber[frame * 4 + 3];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);	
}

void ObjShellBomberUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map) {
	Bullet *bullet;
	Point *pt;
	int x = obj->x - map->scrollX;
	int y = obj->y - map->scrollY;	
	if ((bullet = ObjCheckCollisionBullet(obj->x - map->scrollX, obj->y - map->scrollY, 16, 16)) != NULL) {
		ExplosionManagerAdd(obj->x - map->scrollX, obj->y - map->scrollY, 0, -2);
		ObjectMapRemove(objMap, obj);
		BulletManagerRemove(bullet);
		return;
	}
	if (ObjCheckCollisionCommando(obj->x - map->scrollX, obj->y - map->scrollY, 16, 16))
		CommandoKill();	
	if ((rand()%20) == 0) {
		pt = CommandoXY();
		if (pt->x < x)
			BulletManagerAdd(x - 8, y - 8, -2, -4, BULLET_TYPE_FOE);
		else
			BulletManagerAdd(x + 16, y - 8, 2, -4, BULLET_TYPE_FOE);
	}
}

#define HELICOPTER_SPEED 5

#define HELICOPTER_LEFT_FLY0 0
#define HELICOPTER_LEFT_FLY1 1
#define HELICOPTER_RIGHT_FLY0 2
#define HELICOPTER_RIGHT_FLY1 3

typedef struct Helicopter_Tag {
	char frame;
}Helicopter;

Sprite g_spritesHelicopter[] = {
	//HELICOPTER_LEFT_FLY0
	{88, 0, 0, 0, 0},
	{89, 0, 0, 8, 0},
	{120, 0, 0, 0, 8},
	{121, 0, 0, 8, 8},
	//HELICOPTER_LEFT_FLY1
	{90, 0, 0, 0, 0},
	{91, 0, 0, 8, 0},
	{122, 0, 0, 0, 8},
	{123, 0, 0, 8, 8},
	//HELICOPTER_RIGHT_FLY0
	{88, 1, 0, 8, 0},
	{89, 1, 0, 0, 0},
	{120, 1, 0, 8, 8},
	{121, 1, 0, 0, 8},
	//HELICOPTER_RIGHT_FLY1
	{90, 1, 0, 8, 0},
	{91, 1, 0, 0, 0},
	{122, 1, 0, 8, 8},
	{123, 1, 0, 0, 8}
};

void ObjHelicopterCreate(struct Object_Tag *obj, struct Map_Tag *map) {
	Helicopter *helicopter;
	helicopter = (Helicopter *)malloc(sizeof(KnifeRunner));
	switch (obj->tile) {
		case OBJECT_HELICOPTERLEFT:
			obj->x -= 235;
			helicopter->frame = HELICOPTER_RIGHT_FLY0;
			break;
		case OBJECT_HELICOPTERRIGHT:
			helicopter->frame = HELICOPTER_LEFT_FLY0;
			break;
	}
	obj->context = helicopter;
}

void ObjHelicopterRelease(struct Object_Tag *obj) {
	free(obj->context);
}

void ObjHelicopterRender(struct Object_Tag *obj, struct Map_Tag *map) {
	Sprite *sprite = NULL;
	Helicopter *helicopter;
	int x;
	int y;
	x = obj->x - map->scrollX;
	y = obj->y - map->scrollY;
	helicopter = (Helicopter *)obj->context;
	sprite = &g_spritesHelicopter[helicopter->frame * 4];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesHelicopter[helicopter->frame * 4 + 1];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesHelicopter[helicopter->frame * 4 + 2];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesHelicopter[helicopter->frame * 4 + 3];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
}

void ObjHelicopterUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map) {
	Helicopter *helicopter;
	Bullet *bullet;
	Point *pt;
	int x = obj->x - map->scrollX;
	int y = obj->y - map->scrollY;
	if ((bullet = ObjCheckCollisionBullet(obj->x - map->scrollX, obj->y - map->scrollY, 16, 16)) != NULL) {
		ExplosionManagerAdd(obj->x - map->scrollX, obj->y - map->scrollY, 0, -2);
		ObjectMapRemove(objMap, obj);
		BulletManagerRemove(bullet);
		return;
	}
	if (ObjCheckCollisionCommando(obj->x - map->scrollX, obj->y - map->scrollY, 16, 16))
		CommandoKill();	
	helicopter = (Helicopter *)obj->context;
	switch (obj->tile) {
		case OBJECT_HELICOPTERLEFT:
			helicopter->frame = (helicopter->frame == HELICOPTER_RIGHT_FLY0) ? HELICOPTER_RIGHT_FLY1 : HELICOPTER_RIGHT_FLY0;
			obj->x += HELICOPTER_SPEED;
			break;
		case OBJECT_HELICOPTERRIGHT:
			helicopter->frame = (helicopter->frame == HELICOPTER_LEFT_FLY0) ? HELICOPTER_LEFT_FLY1 : HELICOPTER_LEFT_FLY0;
			obj->x -= HELICOPTER_SPEED;
			break;
	}
	if ((rand()%20) == 0) {
		pt = CommandoXY();
		if (pt->x < x)
			BulletManagerAdd(x - 8, y + 16, -3, 3, BULLET_TYPE_FOE);
		else
			BulletManagerAdd(x + 16, y + 16, 3, 3, BULLET_TYPE_FOE);
	}
}

#define BALLOON_RADIUS 5

typedef struct Balloon_Tag {
	int offX;
	int offY;
	int degrees;
}Balloon;

static Sprite g_spritesBalloon[] = {
	{128, 0, 0, 0, 0},
	{129, 0, 0, 8, 0},
	{160, 0, 0, 0, 8},
	{161, 0, 0, 8, 8},
	{94, 0, 0, 0, 16},
	{95, 0, 0, 8, 16}
};

void ObjBalloonCreate(struct Object_Tag *obj, struct Map_Tag *map) {
	Balloon *balloon;
	balloon = (Balloon *)malloc(sizeof(Balloon));
	balloon->offX = 0;
	balloon->offY = 0;
	balloon->degrees = 0;
	obj->context = balloon;
}

void ObjBalloonRelease(struct Object_Tag *obj) {
	free(obj->context);
}

void ObjBalloonRender(struct Object_Tag *obj, struct Map_Tag *map) {
	Sprite *sprite = NULL;
	Balloon *balloon;
	int x = obj->x - map->scrollX;
	int y = obj->y - map->scrollY;
	balloon = (Balloon *)obj->context;
	x += balloon->offX;
	y += balloon->offY;
	sprite = &g_spritesBalloon[0];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesBalloon[1];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesBalloon[2];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesBalloon[3];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);	
	sprite = &g_spritesBalloon[4];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);	
	sprite = &g_spritesBalloon[5];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);	
}

void ObjBalloonUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map) {
	Balloon *balloon;
	Bullet *bullet;
	Point *pt;
	int x = obj->x - map->scrollX;
	int y = obj->y - map->scrollY;	
	balloon = (Balloon *)obj->context;	
	if ((bullet = ObjCheckCollisionBullet(obj->x - map->scrollX + balloon->offX, obj->y - map->scrollY + balloon->offY, 16, 16)) != NULL) {
		ExplosionManagerAdd(obj->x - map->scrollX + balloon->offX, obj->y - map->scrollY + balloon->offY, 0, -2);
		ObjectMapRemove(objMap, obj);
		BulletManagerRemove(bullet);
		return;
	}
	if (ObjCheckCollisionCommando(obj->x - map->scrollX, obj->y - map->scrollY, 16, 24))
		CommandoKill();	
	balloon->offY = SinPercent(balloon->degrees) * BALLOON_RADIUS / 100;
	balloon->degrees += 5;
	if (balloon->degrees > 360)
		balloon->degrees = 0;
	if ((rand()%20) == 0) {
		x += balloon->offX;
		y += balloon->offY;
		pt = CommandoXY();
		BulletManagerAdd(x + 4, y + 24, 0, 3, BULLET_TYPE_FOE);
		BulletManagerAdd(x - 4, y + 24, -3, 3, BULLET_TYPE_FOE);
		BulletManagerAdd(x + 16, y + 24, 3, 3, BULLET_TYPE_FOE);
	}	
}