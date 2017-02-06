
#include "spr.h"

static int g_count = 0;

void SpriteReset() {
	g_count = 0;
}

void SpriteCleanup() {
	int i;
	for (i = g_count; i < 128; i++)
		setsprite(i, 0, 240, 0, 31, 0, 0);
}

unsigned char SpriteAlloc() {
	if (g_count >= 128)
		g_count = 0;
	return g_count++;
}