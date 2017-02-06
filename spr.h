#ifndef _SPRITE_H_
#define _SPRITE_H_

typedef struct Sprite_Tag {
	int tile;
	char flipH;	
	char flipV;
	int offX;
	int offY;
}Sprite;

void SpriteReset();
void SpriteCleanup();
unsigned char SpriteAlloc();

#endif