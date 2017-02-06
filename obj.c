
#include <stdio.h>
#include <stdlib.h>
#include "obj.h"
#include "util.h"
#include "objs.h"

ObjectMap *ObjectMapCreate(unsigned char *objMapData) {
	ObjectMap *objMap;
	Object *obj;
	Object *objLast;
	int count;
	int i;
	int track;
	if (objMap == NULL)
		return NULL;
	objMap = (ObjectMap *)malloc(sizeof(ObjectMap));
	memset(objMap, 0, sizeof(ObjectMap));
	count = (objMapData[0] << 8) | objMapData[1];
	track = 2;
	for (i = 0; i < count; i++) {
		obj = (Object *)malloc(sizeof(Object));
		memset(obj, 0, sizeof(Object));
		obj->created = FALSE;
		obj->x = (objMapData[track] << 8) | objMapData[track + 1];
		obj->y = (objMapData[track + 2] << 8) | objMapData[track + 3];
		obj->tile = objMapData[track + 4];
		track += 5;
		if (objMap->objects == NULL) {
			objMap->objects = obj;
			continue;
		}
		objLast = objMap->objects;
		while (objLast->pNext)
			objLast = objLast->pNext;
		objLast->pNext = obj;
		obj->pPrev = objLast;
	}
	objMap->count = count;
	return objMap;
}

void ObjectMapRelease(ObjectMap *objMap) {
	Object *obj;
	Object *objNext;
	if (objMap == NULL)
		return;
	obj = objMap->objects;
	while (obj) {
		objNext = obj->pNext;
		ObjectMapRemove(objMap, obj);
		obj = objNext;
	}
	free(objMap);
}

void ObjectMapUpdate(ObjectMap *objMap, struct Map_Tag *map) {
	Object *obj;
	Object *objNext;
	int x;
	int y;
	obj = objMap->objects;
	while (obj) {
		objNext = obj->pNext;
		x = obj->x - map->scrollX;
		y = obj->y - map->scrollY;
		//Check object in view.
		if (x < 0 || x >= 240 || y < 0 || y >= 240) {
			obj = objNext;
			continue;
		}
		if (!obj->created) {
			switch (obj->tile) {
				case OBJECT_MACHINEGUNNER:
					ObjMachineGunnerCreate(obj, map);
					break;
				case OBJECT_TOPGUNNER:
					ObjTopGunnerCreate(obj, map);
					break;
				case OBJECT_KNIFERUNNERLEFT:
				case OBJECT_KNIFERUNNERRIGHT:				
					ObjKnifeRunnerCreate(obj, map);
					break;
				case OBJECT_DOGLEFT:
				case OBJECT_DOGRIGHT:
					ObjDogCreate(obj, map);
					break;
				case OBJECT_FLOORGUNNER:
					ObjFloorGunnerCreate(obj, map);
					break;
				case OBJECT_SHELLBOMBER:
					ObjShellBomberCreate(obj, map);
					break;
				case OBJECT_HELICOPTERLEFT:
				case OBJECT_HELICOPTERRIGHT:
					ObjHelicopterCreate(obj, map);
					break;
				case OBJECT_BALLOON:
					ObjBalloonCreate(obj, map);
					break;
			}
			obj->created = TRUE;
		}
		switch (obj->tile) {
			case OBJECT_MACHINEGUNNER:
				ObjMachineGunnerUpdate(obj, objMap, map);
				break;
			case OBJECT_TOPGUNNER:
				ObjTopGunnerUpdate(obj, objMap, map);
				break;
			case OBJECT_KNIFERUNNERLEFT:
			case OBJECT_KNIFERUNNERRIGHT:			
				ObjKnifeRunnerUpdate(obj, objMap, map);
				break;
			case OBJECT_DOGLEFT:
			case OBJECT_DOGRIGHT:
				ObjDogUpdate(obj, objMap, map);
				break;
			case OBJECT_FLOORGUNNER:
				ObjFloorGunnerUpdate(obj, objMap, map);
				break;
			case OBJECT_SHELLBOMBER:
				ObjShellBomberUpdate(obj, objMap, map);
				break;
			case OBJECT_HELICOPTERLEFT:
			case OBJECT_HELICOPTERRIGHT:
				ObjHelicopterUpdate(obj, objMap, map);
				break;
			case OBJECT_BALLOON:
				ObjBalloonUpdate(obj, objMap, map);
				break;			
		}
		obj = objNext;
	}
}

void ObjectMapRender(ObjectMap *objMap, struct Map_Tag *map) {
	Object *obj;
	int x;
	int y;
	obj = objMap->objects;
	while (obj) {
		x = obj->x - map->scrollX;
		y = obj->y - map->scrollY;
		//Check object in view.
		if (x < 0 || x >= 240 || y < 0 || y >= 240) {
			obj = obj->pNext;
			continue;
		}		
		switch (obj->tile) {
			case OBJECT_MACHINEGUNNER:
				ObjMachineGunnerRender(obj, map);
				break;
			case OBJECT_TOPGUNNER:
				ObjTopGunnerRender(obj, map);
				break;
			case OBJECT_KNIFERUNNERLEFT:
			case OBJECT_KNIFERUNNERRIGHT:
				ObjKnifeRunnerRender(obj, map);
				break;
			case OBJECT_DOGLEFT:
			case OBJECT_DOGRIGHT:
				ObjDogRender(obj, map);
				break;
			case OBJECT_FLOORGUNNER:
				ObjFloorGunnerRender(obj, map);
				break;
			case OBJECT_SHELLBOMBER:
				ObjShellBomberRender(obj, map);
				break;
			case OBJECT_HELICOPTERLEFT:
			case OBJECT_HELICOPTERRIGHT:
				ObjHelicopterRender(obj, map);
				break;
			case OBJECT_BALLOON:
				ObjBalloonRender(obj, map);
				break;			
		}
		obj = obj->pNext;
	}
}

void ObjectMapRemove(ObjectMap *objMap, Object *obj) {
	if (objMap == NULL || obj == NULL)
		return;
	switch (obj->tile) {
		case OBJECT_MACHINEGUNNER:
			ObjMachineGunnerRelease(obj);
			break;
		case OBJECT_TOPGUNNER:
			ObjTopGunnerRelease(obj);
			break;
		case OBJECT_KNIFERUNNERLEFT:
		case OBJECT_KNIFERUNNERRIGHT:			
			ObjKnifeRunnerRelease(obj);
			break;
		case OBJECT_DOGLEFT:
		case OBJECT_DOGRIGHT:			
			ObjDogRelease(obj);
			break;
		case OBJECT_FLOORGUNNER:
			ObjFloorGunnerRelease(obj);
			break;
		case OBJECT_SHELLBOMBER:
			ObjShellBomberRelease(obj);
			break;
		case OBJECT_HELICOPTERLEFT:
		case OBJECT_HELICOPTERRIGHT:
			ObjHelicopterRelease(obj);
			break;
		case OBJECT_BALLOON:
			ObjBalloonRelease(obj);
			break;			
	}
	if (obj->pNext)
		obj->pNext->pPrev = obj->pPrev;
	if (obj->pPrev)
		obj->pPrev->pNext = obj->pNext;
	else
		objMap->objects = obj->pNext;	
	free(obj);
	objMap->count--;
}