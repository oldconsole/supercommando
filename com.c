
#include "snes.h"
#include "util.h"
#include "com.h"
#include "spr.h"
#include "map.h"
#include "bull.h"

#define COMMANDO_RIGHT_STAND 0
#define COMMANDO_RIGHT_WALK0 1
#define COMMANDO_RIGHT_WALK1 2
#define COMMANDO_RIGHT_JUMP0 3
#define COMMANDO_RIGHT_JUMP1 4
#define COMMANDO_RIGHT_JUMP2 5
#define COMMANDO_RIGHT_JUMP3 6
#define COMMANDO_RIGHT_DIAGUP0 7
#define COMMANDO_RIGHT_DIAGUP1 8
#define COMMANDO_RIGHT_DIAGDOWN0 9
#define COMMANDO_RIGHT_DIAGDOWN1 10
#define COMMANDO_RIGHT_CROUCH 11
#define COMMANDO_RIGHT_HIT0 12
#define COMMANDO_RIGHT_HIT1 13
#define COMMANDO_RIGHT_HIT2 14
#define COMMANDO_RIGHT_HIT3 15
#define COMMANDO_LEFT_STAND 16
#define COMMANDO_LEFT_WALK0 17
#define COMMANDO_LEFT_WALK1 18
#define COMMANDO_LEFT_JUMP0 19
#define COMMANDO_LEFT_JUMP1 20
#define COMMANDO_LEFT_JUMP2 21
#define COMMANDO_LEFT_JUMP3 22
#define COMMANDO_LEFT_DIAGUP0 23
#define COMMANDO_LEFT_DIAGUP1 24
#define COMMANDO_LEFT_DIAGDOWN0 25
#define COMMANDO_LEFT_DIAGDOWN1 26
#define COMMANDO_LEFT_CROUCH 27
#define COMMANDO_LEFT_HIT0 28
#define COMMANDO_LEFT_HIT1 29
#define COMMANDO_LEFT_HIT2 30
#define COMMANDO_LEFT_HIT3 31
#define COMMANDO_SHOOTUP 32

#define PHASE_STANDING 0
#define PHASE_JUMPING 10
#define PHASE_DUCKING 20
#define PHASE_WALKING 30
#define PHASE_FALLING 40
#define PHASE_KILLING 50

#define MOVE_HORZ_SPEED 4
#define MOVE_VERT_SPEED 15

static int g_phase = PHASE_STANDING;
static Map *g_map = NULL;
static ObjectMap *g_objMap = NULL;
static int g_x = 0;
static int g_y = 0;
static int g_offX = 0;
static int g_offY = 0;
static int g_frame = COMMANDO_RIGHT_STAND;
static int g_radius = 30;
static int g_degrees = 0;
static char g_facing = RIGHT;
static BOOL g_pressedLeft = FALSE;
static BOOL g_pressedRight = FALSE;
static BOOL g_pressedUp = FALSE;
static BOOL g_pressedDown = FALSE;
static BOOL g_pressedFire = FALSE;
static BOOL g_initWalk = FALSE;
static BOOL g_initJump = FALSE;
static BOOL g_initKill = FALSE;

Sprite g_spritesCommando[] = { 
    //COMMANDO_RIGHT_STAND
	{0, 0, 0, 0, 0},
	{1, 0, 0, 8, 0},
	{32, 0, 0, 0, 8},
	{33, 0, 0, 8, 8},
	//COMMANDO_RIGHT_WALK0
	{2, 0, 0, 0, 0},
	{3, 0, 0, 8, 0},
	{34, 0, 0, 0, 8},
	{35, 0, 0, 8, 8},
	//COMMANDO_RIGHT_WALK1
	{0, 0, 0, 0, 0},
	{1, 0, 0, 8, 0},
	{32, 0, 0, 0, 8},
	{33, 0, 0, 8, 8},
	//COMMANDO_RIGHT_JUMP0
	{4, 0, 0, 0, 0},
	{5, 0, 0, 8, 0},
	{36, 0, 0, 0, 8},
	{37, 0, 0, 8, 8},
	//COMMANDO_RIGHT_JUMP1
	{6, 0, 0, 0, 0},
	{7, 0, 0, 8, 0},
	{38, 0, 0, 0, 8},
	{39, 0, 0, 8, 8},
	//COMMANDO_RIGHT_JUMP2
	{4, 1, 1, 8, 8},
	{5, 1, 1, 0, 8},
	{36, 1, 1, 8, 0},
	{37, 1, 1, 0, 0},
	//COMMANDO_RIGHT_JUMP3
	{6, 1, 1, 8, 8},
	{7, 1, 1, 0, 8},
	{38, 1, 1, 8, 0},
	{39, 1, 1, 0, 0},
	//COMMANDO_RIGHT_DIAGUP0
	{8, 0, 0, 0, 0},
	{9, 0, 0, 8, 0},
	{40, 0, 0, 0, 8},
	{41, 0, 0, 8, 8},
	//COMMANDO_RIGHT_DIAGUP1
	{14, 0, 0, 0, 0},
	{15, 0, 0, 8, 0},
	{46, 0, 0, 0, 8},
	{47, 0, 0, 8, 8},
	//COMMANDO_RIGHT_DIAGDOWN0
	{16, 0, 0, 0, 0},
	{17, 0, 0, 8, 0},
	{48, 0, 0, 0, 8},
	{49, 0, 0, 8, 8},
	//COMMANDO_RIGHT_DIAGDOWN1
	{18, 0, 0, 0, 0},
	{19, 0, 0, 8, 0},
	{50, 0, 0, 0, 8},
	{51, 0, 0, 8, 8},	
	//COMMANDO_RIGHT_CROUCH
	{12, 0, 0, 0, 0},
	{13, 0, 0, 8, 0},
	{44, 0, 0, 0, 8},
	{45, 0, 0, 8, 8},
	//COMMANDO_RIGHT_HIT0
	{6, 1, 1, 8, 8},
	{7, 1, 1, 0, 8},
	{38, 1, 1, 8, 0},
	{39, 1, 1, 0, 0},
	//COMMANDO_RIGHT_HIT1
	{4, 1, 1, 8, 8},
	{5, 1, 1, 0, 8},
	{36, 1, 1, 8, 0},
	{37, 1, 1, 0, 0},
	//COMMANDO_RIGHT_HIT2
	{6, 0, 0, 0, 0},
	{7, 0, 0, 8, 0},
	{38, 0, 0, 0, 8},
	{39, 0, 0, 8, 8},
	//COMMANDO_RIGHT_HIT3
	{4, 0, 0, 0, 0},
	{5, 0, 0, 8, 0},
	{36, 0, 0, 0, 8},
	{37, 0, 0, 8, 8},
    //COMMANDO_LEFT_STAND
	{1, 1, 0, 0, 0},
	{0, 1, 0, 8, 0},
	{33, 1, 0, 0, 8},
	{32, 1, 0, 8, 8},
	//COMMANDO_LEFT_WALK0
	{3, 1, 0, 0, 0},
	{2, 1, 0, 8, 0},
	{35, 1, 0, 0, 8},
	{34, 1, 0, 8, 8},
	//COMMANDO_LEFT_WALK1
	{1, 1, 0, 0, 0},
	{0, 1, 0, 8, 0},
	{33, 1, 0, 0, 8},
	{32, 1, 0, 8, 8},
	//COMMANDO_LEFT_JUMP0
	{5, 1, 0, 0, 0},
	{4, 1, 0, 8, 0},
	{37, 1, 0, 0, 8},
	{36, 1, 0, 8, 8},
	//COMMANDO_LEFT_JUMP1
	{7, 1, 0, 0, 0},
	{6, 1, 0, 8, 0},
	{39, 1, 0, 0, 8},
	{38, 1, 0, 8, 8},
	//COMMANDO_LEFT_JUMP2
	{5, 0, 1, 8, 8},
	{4, 0, 1, 0, 8},
	{37, 0, 1, 8, 0},
	{36, 0, 1, 0, 0},
	//COMMANDO_LEFT_JUMP3
	{7, 0, 1, 8, 8},
	{6, 0, 1, 0, 8},
	{39, 0, 1, 8, 0},
	{38, 0, 1, 0, 0},
	//COMMANDO_LEFT_DIAGUP0
	{9, 1, 0, 0, 0},
	{8, 1, 0, 8, 0},
	{41, 1, 0, 0, 8},
	{40, 1, 0, 8, 8},
	//COMMANDO_LEFT_DIAGUP1
	{15, 1, 0, 0, 0},
	{14, 1, 0, 8, 0},
	{47, 1, 0, 0, 8},
	{46, 1, 0, 8, 8},
	//COMMANDO_LEFT_DIAGDOWN0
	{16, 1, 0, 8, 0},
	{17, 1, 0, 0, 0},
	{48, 1, 0, 8, 8},
	{49, 1, 0, 0, 8},
	//COMMANDO_LEFT_DIAGDOWN1
	{18, 1, 0, 8, 0},
	{19, 1, 0, 0, 0},
	{50, 1, 0, 8, 8},
	{51, 1, 0, 0, 8},
	//COMMANDO_LEFT_CROUCH
	{13, 1, 0, 0, 0},
	{12, 1, 0, 8, 0},
	{45, 1, 0, 0, 8},
	{44, 1, 0, 8, 8},
	//COMMANDO_LEFT_HIT0
	{7, 0, 1, 8, 8},
	{6, 0, 1, 0, 8},
	{39, 0, 1, 8, 0},
	{38, 0, 1, 0, 0},
	//COMMANDO_LEFT_HIT1
	{5, 0, 1, 8, 8},
	{4, 0, 1, 0, 8},
	{37, 0, 1, 8, 0},
	{36, 0, 1, 0, 0},	
	//COMMANDO_LEFT_HIT2
	{7, 1, 0, 0, 0},
	{6, 1, 0, 8, 0},
	{39, 1, 0, 0, 8},
	{38, 1, 0, 8, 8},
	//COMMANDO_LEFT_HIT3
	{5, 1, 0, 0, 0},
	{4, 1, 0, 8, 0},
	{37, 1, 0, 0, 8},
	{36, 1, 0, 8, 8},
	//COMMANDO_SHOOTUP
	{10, 0, 0, 0, 0},
	{11, 0, 0, 8, 0},
	{42, 0, 0, 0, 8},
	{43, 0, 0, 8, 8}
};

void CommandoInit(Map *map, ObjectMap *objMap, int startX, int startY) {
	g_map = map;
	g_objMap = objMap;
	g_x = startX;
	g_y = startY;
	g_offX = 0;
	g_offY = 0;
	g_facing = RIGHT;
	g_phase = PHASE_STANDING;
}

BOOL CommandoCollisionAbove() {
	if (MapCollisionGetTile(g_map, g_map->scrollX + g_x + g_offX + 4, g_map->scrollY + g_y + g_offY - 1) == COLLISION_SOLID)
		return TRUE;
	if (MapCollisionGetTile(g_map, g_map->scrollX + g_x + g_offX + 12, g_map->scrollY + g_y + g_offY - 1) == COLLISION_SOLID)
		return TRUE;
	return FALSE;
}

BOOL CommandoCollisionBelow(int amount) {
	unsigned char tile;
	int x = g_map->scrollX + g_x + g_offX;
	int y = g_map->scrollY + g_y + g_offY;
	int i;
	for (i = 1; i <= amount; i++) {
		tile = MapCollisionGetTile(g_map, x, y + 16 + i);
		if (tile == COLLISION_SOLID || tile == COLLISION_TOPSOLID)
			return TRUE;
		tile = MapCollisionGetTile(g_map, x + 4, y + 16 + i);
		if (tile == COLLISION_SOLID || tile == COLLISION_TOPSOLID)
			return TRUE;
		tile = MapCollisionGetTile(g_map, x + 8, y + 16 + i);
		if (tile == COLLISION_SOLID || tile == COLLISION_TOPSOLID)
			return TRUE;		
		tile = MapCollisionGetTile(g_map, x + 12, y + 16 + i);
		if (tile == COLLISION_SOLID || tile == COLLISION_TOPSOLID)
			return TRUE;
	}
	return FALSE;
}

BOOL CommandoCollisionLeft(int amount) {
	int x = g_map->scrollX + g_x + g_offX;
	int y = g_map->scrollY + g_y + g_offY;
	int i;
	for (i = 1; i <= amount; i++) {
		if (MapCollisionGetTile(g_map, x - i, y) == COLLISION_SOLID)
			return TRUE;
		if (MapCollisionGetTile(g_map, x - i, y + 4) == COLLISION_SOLID)
			return TRUE;
		if (MapCollisionGetTile(g_map, x - i, y + 8) == COLLISION_SOLID)
			return TRUE;		
		if (MapCollisionGetTile(g_map, x - i, y + 12) == COLLISION_SOLID)
			return TRUE;
	}
	return FALSE;
}

BOOL CommandoCollisionRight(int amount) {
	int x = g_map->scrollX + g_x + g_offX;
	int y = g_map->scrollY + g_y + g_offY;
	int i;
	for (i = 1; i <= amount; i++) {
		if (MapCollisionGetTile(g_map, x + 16 + i, y) == COLLISION_SOLID)
			return TRUE;
		if (MapCollisionGetTile(g_map, x + 16 + i, y + 4) == COLLISION_SOLID)
			return TRUE;		
		if (MapCollisionGetTile(g_map, x + 16 + i, y + 8) == COLLISION_SOLID)
			return TRUE;		
		if (MapCollisionGetTile(g_map, x + 16 + i, y + 12) == COLLISION_SOLID)
			return TRUE;
	}
	return FALSE;
}

void CommandoDoMoveLeft() {
	int i;
	if (!g_pressedLeft)
		return;
	g_facing = LEFT;
	for (i = 0; i < MOVE_HORZ_SPEED; i++) {
		if (!CommandoCollisionLeft(1))
			g_x--;
		else
			break;
	}
}

void CommandoDoMoveRight() {
	int i;
	if (!g_pressedRight)
		return;
	g_facing = RIGHT;
	for (i = 0; i < MOVE_HORZ_SPEED; i++) {
		if (!CommandoCollisionRight(1))
			g_x++;
		else
			break;
	}
}

void CommandoDoMoveLeftAnim() {
	int i;
	if (!g_pressedLeft)
		return;
	g_facing = LEFT;
	for (i = 0; i < MOVE_HORZ_SPEED; i++) {
		if (!CommandoCollisionLeft(1))
			g_x--;
		else
			break;
	}
	if (g_pressedUp) {
		if (g_frame == COMMANDO_LEFT_DIAGUP0)
			g_frame = COMMANDO_LEFT_DIAGUP1;
		else
			g_frame = COMMANDO_LEFT_DIAGUP0;		
	}
	else if (g_pressedDown) {
		if (g_frame == COMMANDO_LEFT_DIAGDOWN0)
			g_frame = COMMANDO_LEFT_DIAGDOWN1;
		else
			g_frame = COMMANDO_LEFT_DIAGDOWN0;
	}	
	else {
		if (g_frame == COMMANDO_LEFT_WALK0)
			g_frame = COMMANDO_LEFT_WALK1;
		else
			g_frame = COMMANDO_LEFT_WALK0;
	}
}

void CommandoDoMoveRightAnim() {
	int i;
	if (!g_pressedRight)
		return;
	g_facing = RIGHT;
	for (i = 0; i < MOVE_HORZ_SPEED; i++) {
		if (!CommandoCollisionRight(1))
			g_x++;
		else
			break;
	}
	if (g_pressedUp) {
		if (g_frame == COMMANDO_RIGHT_DIAGUP0)
			g_frame = COMMANDO_RIGHT_DIAGUP1;
		else
			g_frame = COMMANDO_RIGHT_DIAGUP0;
	}
	else if (g_pressedDown) {
		if (g_frame == COMMANDO_RIGHT_DIAGDOWN0)
			g_frame = COMMANDO_RIGHT_DIAGDOWN1;
		else
			g_frame = COMMANDO_RIGHT_DIAGDOWN0;
	}
	else {
		if (g_frame == COMMANDO_RIGHT_WALK0)
			g_frame = COMMANDO_RIGHT_WALK1;
		else
			g_frame = COMMANDO_RIGHT_WALK0;
	}
}

void CommandoDoFire() {
	if (!g_pressedFire)
		return;
	if (g_pressedUp) {
		if (g_pressedLeft)
			BulletManagerAdd(g_x + g_offX + 8, g_y + g_offY + 8, -1, -1, BULLET_TYPE_FRIEND);
		else if (g_pressedRight)
			BulletManagerAdd(g_x + g_offX, g_y + g_offY + 8, 1, -1, BULLET_TYPE_FRIEND);
		else 
			BulletManagerAdd(g_x + g_offX + 4, g_y + g_offY + 6, 0, -1, BULLET_TYPE_FRIEND);
		return;
	}
	if (g_pressedDown) {
		if (g_pressedLeft)
			BulletManagerAdd(g_x + g_offX + 8, g_y + g_offY, -1, 1, BULLET_TYPE_FRIEND);
		else if (g_pressedRight)
			BulletManagerAdd(g_x + g_offX, g_y + g_offY, 1, 1, BULLET_TYPE_FRIEND);
		else {
			if (g_facing == LEFT)
				BulletManagerAdd(g_x + g_offX + 10, g_y + g_offY + 8, -1, 0, BULLET_TYPE_FRIEND);
			else
				BulletManagerAdd(g_x + g_offX, g_y + g_offY + 8, 1, 0, BULLET_TYPE_FRIEND);
		}
		return;
	}
	if (g_facing == LEFT)
		BulletManagerAdd(g_x + g_offX + 10, g_y + g_offY + 6, -1, 0, BULLET_TYPE_FRIEND);
	else
		BulletManagerAdd(g_x + g_offX, g_y + g_offY + 6, 1, 0, BULLET_TYPE_FRIEND);
}

void CommandoUpdateJumpFrame() {
	if (g_facing == RIGHT) {
		switch (g_frame) {
			case COMMANDO_RIGHT_JUMP0:
			case COMMANDO_RIGHT_JUMP1:
			case COMMANDO_RIGHT_JUMP2:
				g_frame++;
				break;
			case COMMANDO_RIGHT_JUMP3:
				g_frame = COMMANDO_RIGHT_JUMP0;
				break;			
			default:
				g_frame = COMMANDO_RIGHT_JUMP0;
				break;
		}	
	}
	else {
		switch (g_frame) {
			case COMMANDO_LEFT_JUMP0:
			case COMMANDO_LEFT_JUMP1:
			case COMMANDO_LEFT_JUMP2:
				g_frame++;
				break;
			case COMMANDO_LEFT_JUMP3:
				g_frame = COMMANDO_LEFT_JUMP0;
				break;			
			default:
				g_frame = COMMANDO_LEFT_JUMP0;
				break;
		}
	}	
}

Bullet *CommandoCheckCollsionBullet(int x, int y, int width, int height) {
	Bullet *bullet;	
	Rect r1;
	Rect r2;
	RectSet(&r1, x, y, width, height);
	bullet = BulletManagerBullets();
	while (bullet) {
		if (bullet->type != BULLET_TYPE_FOE) {
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

void CommandoUpdate() {
	Bullet *bullet;
	int i;
	int offYOld;
	int y;
	switch (g_phase) {
		case PHASE_JUMPING:
			if (!g_initJump) {
				g_radius = 40;
				g_degrees = 180;
				g_frame = (g_facing == RIGHT) ? COMMANDO_RIGHT_JUMP0 : COMMANDO_LEFT_JUMP0;
				offYOld = 0;
				g_initJump = TRUE;
			}
			if (g_degrees + 15 >= 360) {								
				offYOld = g_offY;
				y = SinPercent(360) * g_radius / 100;
				for (i = offYOld; i <= y; i++) {
					if (!CommandoCollisionBelow(1))
						g_offY++;
					else
						break;
				}
				g_phase++;
				break;
			}
			g_degrees += 15;
			offYOld = g_offY;
			y = SinPercent(g_degrees) * g_radius / 100;
			if (g_degrees > 270) {
				for (i = offYOld; i <= y; i++) {
					if (!CommandoCollisionBelow(1)) {
						g_offY++;
					}
					else {
						g_x = g_x + g_offX;
						g_y = g_y + g_offY;
						g_offX = 0;
						g_offY = 0;
						g_phase = PHASE_STANDING;
						break;
					}
				}
				if (g_phase == PHASE_STANDING)
					break;
			}
			else {
				g_offY = y;
			}
			CommandoUpdateJumpFrame();
			//If collision above, go down.
			if (CommandoCollisionAbove()) {
				if (g_degrees < 270)
					g_degrees = 270;
			}
			CommandoDoMoveLeft();
			CommandoDoMoveRight();
			CommandoDoFire();
			break;
		case PHASE_JUMPING + 1:
			CommandoDoMoveLeft();
			CommandoDoMoveRight();
			CommandoDoFire();
			CommandoUpdateJumpFrame();
			if (!CommandoCollisionBelow(MOVE_VERT_SPEED)) {
				g_y += MOVE_VERT_SPEED;
				break;
			}
			for (i = 0; i < MOVE_VERT_SPEED; i++) {
				if (!CommandoCollisionBelow(1))
					g_y++;
				else
					break;
			}
			g_x = g_x + g_offX;
			g_y = g_y + g_offY;
			g_offX = 0;
			g_offY = 0;
			g_phase = PHASE_STANDING;
			break;
		case PHASE_STANDING:
			if (g_pressedUp) {
				if (!g_pressedLeft && !g_pressedRight)
					g_frame = COMMANDO_SHOOTUP;
				else
					g_frame = (g_facing == RIGHT) ? COMMANDO_RIGHT_DIAGUP0 : COMMANDO_LEFT_DIAGUP0;
			}
			else if (g_pressedDown) {
				if (!g_pressedLeft && !g_pressedRight)
					g_frame = (g_facing == RIGHT) ? COMMANDO_RIGHT_CROUCH : COMMANDO_LEFT_CROUCH;
				else
					g_frame = (g_facing == RIGHT) ? COMMANDO_RIGHT_DIAGDOWN0 : COMMANDO_LEFT_DIAGDOWN0;
			}
			else {
				g_frame = (g_facing == RIGHT) ? COMMANDO_RIGHT_STAND : COMMANDO_LEFT_STAND;
			}
			if (g_pressedLeft) {
				g_facing = LEFT;
				g_initWalk = FALSE;
				g_phase = PHASE_WALKING;
			}
			else if (g_pressedRight) {
				g_facing = RIGHT;
				g_initWalk = FALSE;
				g_phase = PHASE_WALKING;
			}
			CommandoDoFire();
			break;
		case PHASE_WALKING:
			if (!g_initWalk) {
				g_frame = (g_facing == RIGHT) ? COMMANDO_RIGHT_WALK1 : COMMANDO_LEFT_WALK1;
				g_initWalk = TRUE;
			}
			CommandoDoMoveLeftAnim();
			CommandoDoMoveRightAnim();
			CommandoDoFire();
			if (!CommandoCollisionBelow(1))
				g_phase = PHASE_FALLING;
			else if (!g_pressedLeft && !g_pressedRight)
				g_phase = PHASE_STANDING;
			break;
		case PHASE_FALLING:
			for (i = 0; i < MOVE_VERT_SPEED; i++) {
				if (CommandoCollisionBelow(1)) {
					g_phase = PHASE_STANDING;
					break;
				}
				g_y++;
			}
			CommandoDoMoveLeftAnim();
			CommandoDoMoveRightAnim();
			CommandoDoFire();
			break;
		case PHASE_KILLING:
			break;
	}
	if (g_map->orientation == ORIENT_HORZ) {
		i = g_x + g_offX;
		if (i > 128) {
			if (MapCanScroll(g_map, i - 128)) {
				MapScroll(g_map, i - 128);
				g_x = 128;
			}
			else {
				MapScrollPosSet(g_map, g_map->width - 256);
			}
		}
	}
	else {
		i = g_y + g_offY;
		if (i > 128) {
			if (MapCanScroll(g_map, i - 128)) {
				MapScroll(g_map, i - 128);
				g_x = 128;
			}
			else {
				MapScrollPosSet(g_map, g_map->height - 256);
			}
		}
	}
	if (g_x < 0)
		g_x = 0;
	if (g_y < 0)
		g_y = 0;
	if (g_x + 16 > 256)
		g_x = 256 - 16;
	if (g_y + 16 > 256)
		g_y = 256 - 16;
	if (g_phase != PHASE_KILLING) {
		if ((bullet = CommandoCheckCollsionBullet(g_x + g_offX, g_y + g_offY, 16, 16)) != NULL) {
			BulletManagerRemove(bullet);
			CommandoKill();
		}
	}
	g_pressedLeft = FALSE;
	g_pressedRight = FALSE;
	g_pressedUp = FALSE;
	g_pressedDown = FALSE;
	g_pressedFire = FALSE;
}

void CommandoRender() {
	Sprite *sprite = NULL;
	int x = g_x + g_offX;
	int y = g_y + g_offY;
	if (g_phase == PHASE_KILLING)
		return;
	sprite = &g_spritesCommando[g_frame * 4];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesCommando[g_frame * 4 + 1];
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesCommando[g_frame * 4 + 2];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
	sprite = &g_spritesCommando[g_frame * 4 + 3];	
	setsprite(SpriteAlloc(), x + sprite->offX, y + sprite->offY, sprite->tile, 31, sprite->flipH, sprite->flipV);
}

void CommandoButtonJump() {
	if (g_phase != PHASE_STANDING && g_phase != PHASE_WALKING)
		return;
	g_initJump = FALSE;
	g_phase = PHASE_JUMPING;
}

void CommandoButtonLeft() {
	g_pressedLeft = TRUE;
}

void CommandoButtonRight() {
	g_pressedRight = TRUE;
}

void CommandoButtonUp() {
	g_pressedUp = TRUE;
}

void CommandoButtonDown() {
	g_pressedDown = TRUE;
}

void CommandoButtonFire() {
	g_pressedFire = TRUE;
}

Point *CommandoXY() {
	static Point pt;
	pt.x = g_x + g_offX;
	pt.y = g_y + g_offY;
	return &pt;
}

void CommandoKill() {
	if (g_phase == PHASE_KILLING)
		return;
	ExplosionManagerAdd(g_x + g_offX, g_y + g_offY, 0, -2);
	ExplosionManagerAdd(g_x + g_offX, g_y + g_offY, 2, 0);
	ExplosionManagerAdd(g_x + g_offX, g_y + g_offY, 0, 2);
	ExplosionManagerAdd(g_x + g_offX, g_y + g_offY, -2, 0);
	g_initKill = FALSE;
	g_phase = PHASE_KILLING;
}

BOOL CommandoDead() {
	return (g_phase == PHASE_KILLING);
}