
#include <stdio.h>
#include "util.h"

#define SIN_LOOP 5
#define COS_LOOP 5

static int g_cosPercentLookup[] = {100, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 97, 97, 97, 96, 96, 95, 95, 94, 93, 93, 92, 92, 91, 90, 89, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 71, 70, 69, 68, 66, 65, 64, 62, 61, 60, 58, 57, 55, 54, 52, 51, 50, 48, 46, 45, 43, 42, 40, 39, 37, 35, 34, 32, 30, 29, 27, 25, 24, 22, 20, 19, 17, 15, 13, 12, 10, 8, 6, 5, 3, 1, 0, -1, -3, -5, -6, -8, -10, -12, -13, -15, -17, -19, -20, -22, -24, -25, -27, -29, -30, -32, -34, -35, -37, -39, -40, -42, -43, -45, -46, -48, -49, -51, -52, -54, -55, -57, -58, -60, -61, -62, -64, -65, -66, -68, -69, -70, -71, -73, -74, -75, -76, -77, -78, -79, -80, -81, -82, -83, -84, -85, -86, -87, -88, -89, -89, -90, -91, -92, -92, -93, -93, -94, -95, -95, -96, -96, -97, -97, -97, -98, -98, -98, -99, -99, -99, -99, -99, -99, -99, -99, -100, -99, -99, -99, -99, -99, -99, -99, -99, -98, -98, -98, -97, -97, -97, -96, -96, -95, -95, -94, -93, -93, -92, -92, -91, -90, -89, -89, -88, -87, -86, -85, -84, -83, -82, -81, -80, -79, -78, -77, -76, -75, -74, -73, -71, -70, -69, -68, -66, -65, -64, -62, -61, -60, -58, -57, -55, -54, -52, -51, -50, -48, -46, -45, -43, -42, -40, -39, -37, -35, -34, -32, -30, -29, -27, -25, -24, -22, -20, -19, -17, -15, -13, -12, -10, -8, -6, -5, -3, -1, 0, 1, 3, 5, 6, 8, 10, 12, 13, 15, 17, 19, 20, 22, 24, 25, 27, 29, 30, 32, 34, 35, 37, 39, 40, 42, 43, 45, 46, 48, 50, 51, 52, 54, 55, 57, 58, 60, 61, 62, 64, 65, 66, 68, 69, 70, 71, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 89, 90, 91, 92, 92, 93, 93, 94, 95, 95, 96, 96, 97, 97, 97, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 100};
static int g_sinPercentLookup[] = {0, 1, 3, 5, 6, 8, 10, 12, 13, 15, 17, 19, 20, 22, 24, 25, 27, 29, 30, 32, 34, 35, 37, 39, 40, 42, 43, 45, 46, 48, 49, 51, 52, 54, 55, 57, 58, 60, 61, 62, 64, 65, 66, 68, 69, 70, 71, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 89, 90, 91, 92, 92, 93, 93, 94, 95, 95, 96, 96, 97, 97, 97, 98, 98, 98, 99, 99, 99, 99, 99, 99, 99, 99, 100, 99, 99, 99, 99, 99, 99, 99, 99, 98, 98, 98, 97, 97, 97, 96, 96, 95, 95, 94, 93, 93, 92, 92, 91, 90, 89, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 71, 70, 69, 68, 66, 65, 64, 62, 61, 60, 58, 57, 55, 54, 52, 51, 49, 48, 46, 45, 43, 42, 40, 39, 37, 35, 34, 32, 30, 29, 27, 25, 24, 22, 20, 19, 17, 15, 13, 12, 10, 8, 6, 5, 3, 1, 0, -1, -3, -5, -6, -8, -10, -12, -13, -15, -17, -19, -20, -22, -24, -25, -27, -29, -30, -32, -34, -35, -37, -39, -40, -42, -43, -45, -46, -48, -50, -51, -52, -54, -55, -57, -58, -60, -61, -62, -64, -65, -66, -68, -69, -70, -71, -73, -74, -75, -76, -77, -78, -79, -80, -81, -82, -83, -84, -85, -86, -87, -88, -89, -89, -90, -91, -92, -92, -93, -93, -94, -95, -95, -96, -96, -97, -97, -97, -98, -98, -98, -99, -99, -99, -99, -99, -99, -99, -99, -100, -99, -99, -99, -99, -99, -99, -99, -99, -98, -98, -98, -97, -97, -97, -96, -96, -95, -95, -94, -93, -93, -92, -92, -91, -90, -89, -89, -88, -87, -86, -85, -84, -83, -82, -81, -80, -79, -78, -77, -76, -75, -74, -73, -71, -70, -69, -68, -66, -65, -64, -62, -61, -60, -58, -57, -55, -54, -52, -51, -50, -48, -46, -45, -43, -42, -40, -39, -37, -35, -34, -32, -30, -29, -27, -25, -24, -22, -20, -19, -17, -15, -13, -12, -10, -8, -6, -5, -3, -1, 0};

const char *LongLongToStr(long long val) {
	static char str[16];
	int numbers[10];
	int minus = 0;
	int i;
	int j = 0;
	long long r = 1000000000ll;	
	if (val < 0ll) {
		minus = 1;
		val = -val;
	}
	memset(numbers, 0, sizeof(int) * 10);
	for (i = 0; i < 10; i++) {
		while(val >= r) {
			numbers[j]++;
			val -= r;
		}
		r /= 10ll;
		j++;
	}
	i = 0;
	if (minus)
		str[i++] = '-';
	for (j = 0; j < 10; j++)
		str[i + j] = numbers[j] + '0';
	str[i + j] = '\0';
	return str;
}

int StrToInt(const char *str) {
	int len;
	int i;
	int num = 0;
	int base = 1;
	char minus = 0;
	if (str == NULL)
		return 0;
	while (*str == ' ' || *str == '\t')
		str++;
	if (*str == '\0')
		return 0;
    if (*str == '-') {
		minus = 1;
		str++;
	}
	len = strlen(str);
	for (i = len - 1; i >= 0; i--) {
		if (str[i] < '0' || str[i] > '9')
			break;
		num += (str[i] - '0') * base;
		base *= 10;
	}
	return (minus) ? -num : num;
}

int CosPercent(int x) {
	return g_cosPercentLookup[x];
}

int SinPercent(int x) {
	return g_sinPercentLookup[x];
}

void RectSet(Rect *r, int left, int top, int width, int height) {
	r->left = left;
	r->top = top;
	r->width = width;
	r->height = height;
}

BOOL RectInRect(Rect *r1, Rect *r2) {
	if (r1->left < r2->left + r2->width && 
		r1->left + r1->width > r2->left &&
		r1->top < r2->top + r2->height &&
		r1->top + r1->height > r2->top)
		return TRUE;
	return FALSE;
}