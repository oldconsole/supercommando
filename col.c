
#include <stdio.h>
#include "col.h"
#include "util.h"

unsigned int CollisionGetXY(unsigned char *collision, int xp, int yp) {
	return collision[yp * 32 + xp];
}

unsigned char *CollisionCreate(unsigned char *csv) {
	int xp;
	int yp;
	char num[8];
	int i;
	unsigned char *collision;
	collision = (unsigned char *)malloc(sizeof(unsigned char) * 32 * 32);
	for (yp = 0; yp < 32; yp++) {
		for (xp = 0; xp < 32; xp++) {
			i = 0;
			while (*csv != ',') {
				num[i++] = *csv;
				csv++;
			}
			csv++;		
			num[i] = '\0';
			collision[yp * 32 + xp] = (unsigned char)StrToInt(num);
		}
	}
}

void CollisionRelease(unsigned char *collision) {
	if (collision != NULL)
		free(collision);
}