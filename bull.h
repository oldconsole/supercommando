
#ifndef _BULLET_H_
#define _BULLET_H_

#define BULLET_TYPE_FRIEND 0
#define BULLET_TYPE_FOE 1

typedef struct Bullet_Tag {
	struct Bullet_Tag *pNext;
	struct Bullet_Tag *pPrev;
	int x;
	int y;
	int stepX;
	int stepY;
	char type;
	char frame;
}Bullet;

void BulletManagerInit();
void BulletManagerRelease();
void BulletManagerAdd(int startX, int startY, int stepX, int stepY, int type);
void BulletManagerRenderFriend();
void BulletManagerRenderFoe();
void BulletManagerUpdate(struct Map_Tag *map);
Bullet *BulletManagerBullets();
void BulletManagerRemove(Bullet *bullet);

#endif