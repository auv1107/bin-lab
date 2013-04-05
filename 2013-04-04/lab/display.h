#ifndef DISPLAY
#define DISPLAY _


#include "showpic.h"
#include "drawpic.h"

extern char *fbp;
extern struct fb_var_screeninfo vinfo;
extern struct fb_fix_screeninfo finfo;

void draw_pic_at(int x, int y, char *pixel, int width, int height)
{
	char *p;
	p = fbp + x * vinfo.bits_per_pixel / 8 + y * finfo.line_length;
//	printf("x: %d  y: %d\n", x, y);
//	printf("fbp: %x  p: %x\n", fbp, p);
	drawBmp(p, pixel, width, height);
}





#endif
