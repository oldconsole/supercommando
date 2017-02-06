
#ifndef _COMMANDO_H_
#define _COMMANDO_H_

#include "map.h"
#include "obj.h"

void CommandoInit(Map *map, ObjectMap *objMap, int startX, int startY);
void CommandoUpdate();
void CommandoRender();
void CommandoButtonJump();
void CommandoButtonLeft();
void CommandoButtonRight();
void CommandoButtonUp();
void CommandoButtonDown();
void CommandoButtonFire();
Point *CommandoXY();
void CommandoKill();
BOOL CommandoDead();

#endif