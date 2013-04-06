#ifndef GAMEINIT
#define GAMEINIT _


#include "initplane.h"
#include "drawpic.h"
#include "kbhit.h"

extern struct fb_var_screeninfo vinfo;
extern struct fb_fix_screeninfo finfo;

int Period;
int Rate;

int screen_ceil_limit;
int screen_floor_limit;
int screen_left_limit;
int screen_right_limit;

int margin_left;
int margin_right;
int margin_ceil;
int margin_floor;


void constant_init()
{
	Period = 10000;
	Rate = 100;
	
//  the margin to the ...
	margin_left = 10;
	margin_right = 10;
	margin_ceil = 10;
	margin_floor = 10;

//   set the scope of screen
	screen_ceil_limit = margin_ceil;
	screen_floor_limit = vinfo.yres - margin_floor;
	screen_left_limit = margin_left;
	screen_right_limit = vinfo.xres - margin_right;
/*	
	printf("screen_ceil_limit: %d\n", screen_ceil_limit);
	printf("screen_floor_limit: %d\n", screen_floor_limit);
	printf("screen_left_limit: %d\n", screen_left_limit);
	printf("screen_right_limit: %d\n", screen_right_limit);
*/
}


int game_init()
{
	fbd_init();
	constant_init();
	init_all_modules();
	init_keyboard();

	return 0;
}

int game_exit()
{
	fbd_exit();
	close_keyboard();
	return 0;
}





#endif
