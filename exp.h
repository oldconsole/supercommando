
#ifndef _EXPLOSION_H_
#define _EXPLOSION_H_

void ExplosionManagerInit();
void ExplosionManagerRelease();
void ExplosionManagerAdd(int startX, int startY, int stepX, int stepY);
void ExplosionManagerRender();
void ExplosionManagerUpdate();

#endif