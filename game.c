
#include "data.h"
#include "snes.h"
#include "util.h"
#include "spr.h"
#include "map.h"
#include "obj.h"
#include "com.h"
#include "bull.h"
#include "exp.h"

#define TILES_HORZ 32
#define TILES_VERT 32

#define PHASE_INIT 0
#define PHASE_LOGO 10
#define PHASE_INITGAME 20
#define PHASE_GAME 30
#define PHASE_NEXTLEVEL 40
#define PHASE_CONTINUE 50
#define PHASE_WAIT 60
#define PHASE_GAMEOVER 70

#define BACKGROUND1 0
#define BACKGROUND2 1

#define WAIT_FRAMES 60

static int g_lives = 1;
static long long g_points = 0ll;
static int g_level = 0;
static Map *g_map = NULL;
static unsigned char *g_collision = NULL;
static ObjectMap *g_objectMap = NULL;
static int g_phase = PHASE_LOGO;
static unsigned char *g_mapData0 = NULL;
static unsigned char *g_mapData1 = NULL;
static int g_commandoX = 0;
static int g_commandoY = 0;
static char g_background = BACKGROUND1;
static int g_waitCount = 0;

void LevelLoad() {
	if (g_map) {
		MapRelease(g_map);
		g_map = NULL;
	}
	switch(g_level) {
		case 0:
			//BG1 map address & size
			*(unsigned char *)0x2107 = 1;
			//BG2 map address & size
			*(unsigned char *)0x2108 = 8;
			settiles(0, level1_tiles, 32768);
			setpalette(level1_palette);
			g_map = MapCreate(ORIENT_HORZ);
			MapSectionAdd(g_map, level1_map_x0y0, level1_collision_x0y0);
			MapSectionAdd(g_map, level1_map_x1y0, level1_collision_x1y0);
			MapSectionAdd(g_map, level1_map_x2y0, level1_collision_x2y0);
			MapSectionAdd(g_map, level1_map_x3y0, level1_collision_x3y0);
			MapSectionAdd(g_map, level1_map_x4y0, level1_collision_x4y0);
			MapSectionAdd(g_map, level1_map_x5y0, level1_collision_x5y0);
			MapSectionAdd(g_map, level1_map_x6y0, level1_collision_x6y0);
			MapSectionAdd(g_map, level1_map_x7y0, level1_collision_x7y0);
			MapSectionAdd(g_map, level1_map_x8y0, level1_collision_x8y0);
			MapSectionAdd(g_map, level1_map_x9y0, level1_collision_x9y0);
			MapSectionAdd(g_map, level1_map_x10y0, level1_collision_x10y0);
			MapSectionAdd(g_map, level1_map_x11y0, level1_collision_x11y0);
			MapSectionAdd(g_map, level1_map_x12y0, level1_collision_x12y0);
			MapSectionAdd(g_map, level1_map_x13y0, level1_collision_x13y0);
			MapSectionAdd(g_map, level1_map_x14y0, level1_collision_x14y0);
			setmap(0, MapDataGet(g_map, g_map->scrollX, g_map->scrollY, 0));
			g_objectMap = ObjectMapCreate(level1_object);
			setmap(2, level1_background1_map);
			CommandoInit(g_map, g_objectMap, 50, 192);
			BulletManagerInit();
			ExplosionManagerInit();
			break;
	}
	scrollBG(BG_1, PLANE_HORZ, 0);
	scrollBG(BG_1, PLANE_VERT, 0);
	scrollBG(BG_2, PLANE_HORZ, 0);
	scrollBG(BG_2, PLANE_VERT, 0);
}

void Update() {
	int js;
	static int count = 0;
	js = getjoystatus(0);
	if (js & A_BUTTON)
		CommandoButtonJump();
	CommandoUpdate();
	if (js & LEFT_BUTTON)
		CommandoButtonLeft();
	else if (js & RIGHT_BUTTON)
		CommandoButtonRight();
	if (js & UP_BUTTON)
		CommandoButtonUp();
	else if(js & DOWN_BUTTON)
		CommandoButtonDown();
	if (js & B_BUTTON)
		CommandoButtonFire();
	if (count++ >= 5) {
		if (g_background == BACKGROUND1) {
			setmap(2, level1_background1_map);
			g_background = BACKGROUND2;
		}
		else {
			setmap(2, level1_background2_map);
			g_background = BACKGROUND1;
		}
		count = 0;
	}
	BulletManagerUpdate(g_map);
	ObjectMapUpdate(g_objectMap, g_map);
	ExplosionManagerUpdate();	
}

void Render() {
	unsigned char *mapData0;
	unsigned char *mapData1;
	SpriteReset();
	mapData0 = MapDataGet(g_map, g_map->scrollX, g_map->scrollY, 0);
	mapData1 = MapDataGet(g_map, g_map->scrollX, g_map->scrollY, 1);
	if (mapData0 != g_mapData0) {
		if (mapData0 != NULL)
			setmap(0, mapData0);
		g_mapData0 = mapData0;
	}
	if (mapData1 != g_mapData1) {
		if (mapData1 != NULL)
			setmap(1, mapData1);
		g_mapData1 = mapData1;
	}
	scrollBG(BG_1, PLANE_HORZ, g_map->scrollX);
	scrollBG(BG_1, PLANE_VERT, g_map->scrollY);
	scrollBG(BG_2, PLANE_HORZ, g_map->scrollX2);
	scrollBG(BG_2, PLANE_VERT, g_map->scrollY2);
	ExplosionManagerRender();
	CommandoRender();
	BulletManagerRenderFoe();
	BulletManagerRenderFriend();	
	ObjectMapRender(g_objectMap, g_map);
	SpriteCleanup();
}

int main() {
	int js;
	int i;
	snesc_init();
	enablescreen();
	while(1) {
		switch (g_phase) {
			case PHASE_LOGO:
				g_level = 0;
				g_points = 0ll;
				g_lives = 3;
				settiles(0, logo_tiles, 32768);
				setpalette(logo_palette);
				setmap(0, logo_map);
				for (i = 0; i < 128; i++)
					setsprite(i, 0, 0, 0, 31, 0, 0);
				g_phase++;
				break;
			case PHASE_LOGO + 1:
				js = getjoystatus(0);
				if (js & START_BUTTON)
					g_phase = PHASE_INITGAME;
				break;
			case PHASE_INITGAME:
				g_lives = 1;
				LevelLoad();
				g_phase = PHASE_GAME;
				break;
			case PHASE_GAME:
				Update();
				Render();
				if (CommandoDead()) {
					g_waitCount = 0;
					g_phase = PHASE_WAIT;
				}
				break;
			case PHASE_WAIT:
				Update();
				Render();
				if (g_waitCount++ > WAIT_FRAMES) {
					if (--g_lives > 0)
						g_phase = PHASE_GAMEOVER;
					else
						g_phase = PHASE_GAMEOVER;
				}
				break;
			case PHASE_CONTINUE:
				break;
			case PHASE_GAMEOVER:
				MapRelease(g_map);
				g_map = NULL;
				ObjectMapRelease(g_objectMap);
				g_objectMap = NULL;
				BulletManagerRelease();
				ExplosionManagerRelease();
				settiles(0, interstitial_tiles, 4096);
				setpalette(interstitial_palette);
				setmap(0, interstitial_gameover_map);
				scrollBG(BG_1, PLANE_HORZ, 0);
				scrollBG(BG_1, PLANE_VERT, 0);
				scrollBG(BG_2, PLANE_HORZ, 0);
				scrollBG(BG_2, PLANE_VERT, 0);
				for (i = 0; i < 128; i++)
					setsprite(i, 0, 0, 0, 31, 0, 0);
				g_phase++;
				break;
			case PHASE_GAMEOVER + 1:
				js = getjoystatus(0);
				if (js & START_BUTTON)
					g_phase = PHASE_INITGAME;
				break;
			case PHASE_NEXTLEVEL:
				g_level++;
				if (g_level == 8)
					g_level = 0;
				g_phase = PHASE_INITGAME;
				break;
		}
		//ExplosionManagerAdd(rand()%256, 210, 0, -2);
		rand();
		resettimer();
		clearjoy(0);
		//delay(1);
		sync(1);
	}
}