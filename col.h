#ifndef _COLLISION_H_
#define _COLLISION_H_

unsigned int CollisionGetXY(unsigned char *collision, int xp, int yp);
unsigned char *CollisionCreate(unsigned char *csv);
void CollisionRelease();

#endif