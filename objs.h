
#ifndef _OBJMACHINEGUNNER_H_
#define _OBJMACHINEGUNNER_H_

#include "map.h"
#include "obj.h"

void ObjMachineGunnerCreate(struct Object_Tag *obj, struct Map_Tag *map);
void ObjMachineGunnerRelease(struct Object_Tag *obj);
void ObjMachineGunnerRender(struct Object_Tag *obj, struct Map_Tag *map);
void ObjMachineGunnerUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map);

void ObjTopGunnerCreate(struct Object_Tag *obj, struct Map_Tag *map);
void ObjTopGunnerRelease(struct Object_Tag *obj);
void ObjTopGunnerRender(struct Object_Tag *obj, struct Map_Tag *map);
void ObjTopGunnerUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map);

void ObjKnifeRunnerCreate(struct Object_Tag *obj, struct Map_Tag *map);
void ObjKnifeRunnerRelease(struct Object_Tag *obj);
void ObjKnifeRunnerRender(struct Object_Tag *obj, struct Map_Tag *map);
void ObjKnifeRunnerUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map);

void ObjDogCreate(struct Object_Tag *obj, struct Map_Tag *map);
void ObjDogRelease(struct Object_Tag *obj);
void ObjDogRender(struct Object_Tag *obj, struct Map_Tag *map);
void ObjDogUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map);

void ObjFloorGunnerCreate(struct Object_Tag *obj, struct Map_Tag *map);
void ObjFloorGunnerRelease(struct Object_Tag *obj);
void ObjFloorGunnerRender(struct Object_Tag *obj, struct Map_Tag *map);
void ObjFloorGunnerUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map);

void ObjShellBomberCreate(struct Object_Tag *obj, struct Map_Tag *map);
void ObjShellBomberRelease(struct Object_Tag *obj);
void ObjShellBomberRender(struct Object_Tag *obj, struct Map_Tag *map);
void ObjSehllBomberUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map);

void ObjHelicopterCreate(struct Object_Tag *obj, struct Map_Tag *map);
void ObjHelicopterRelease(struct Object_Tag *obj);
void ObjHelicopterRender(struct Object_Tag *obj, struct Map_Tag *map);
void ObjHelicopterUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map);

void ObjBalloonCreate(struct Object_Tag *obj, struct Map_Tag *map);
void ObjBalloonRelease(struct Object_Tag *obj);
void ObjBalloonRender(struct Object_Tag *obj, struct Map_Tag *map);
void ObjBalloonUpdate(struct Object_Tag *obj, struct ObjectMap_Tag *objMap, struct Map_Tag *map);

#endif