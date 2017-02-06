
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "map.h"
#include "util.h"

#define OBJECT_MACHINEGUNNER 0
#define OBJECT_TOPGUNNER 1
#define OBJECT_KNIFERUNNERLEFT 2
#define OBJECT_KNIFERUNNERRIGHT 3
#define OBJECT_DOGLEFT 4
#define OBJECT_DOGRIGHT 5
#define OBJECT_FLOORGUNNER 6
#define OBJECT_SHELLBOMBER 7
#define OBJECT_HELICOPTERLEFT 8
#define OBJECT_HELICOPTERRIGHT 9
#define OBJECT_BALLOON 10

typedef struct Object_Tag {
	struct Object_Tag *pNext;
	struct Object_Tag *pPrev;
	int x;
	int y;
	unsigned char tile;
	BOOL created;
	void *context;
}Object;

typedef struct ObjectMap_Tag {
	Object *objects;
	int count;
}ObjectMap;

ObjectMap *ObjectMapCreate(unsigned char *objMapData);
void ObjectMapRelease(ObjectMap *objMap);
void ObjectMapUpdate(ObjectMap *objMap, struct Map_Tag *map);
void ObjectMapRender(ObjectMap *objMap, struct Map_Tag *map);
void ObjectMapRemove(ObjectMap *objMap, Object *obj);

#endif