
#ifndef _UTIL_H_
#define _UTIL_H_

#define LEFT 0
#define RIGHT 1
#define UP 2
#define DOWN 3

#define BOOL char

#define TRUE 1
#define FALSE 0

#define PI 3.1415f

typedef struct Rect_Tag {
	int left;
	int top;
	int width;
	int height;
}Rect;

const char *LongLongToStr(long long val);
int StrToInt(const char *str);
int CosPercent(int x);
int SinPercent(int x);
void RectSet(Rect *r, int left, int top, int width, int height);
BOOL RectInRect(Rect *r1, Rect *r2);

#endif