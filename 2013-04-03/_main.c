#include "showpic.h"
#include "drawpic.h"
#include "basetype.h"
#include "kbhit.h"

#include <curses.h>
#include <unistd.h>
#include <stdlib.h>

extern struct fb_var_screeninfo vinfo;
extern struct fb_fix_screeninfo finfo;
extern char *fbp_limit_low;
extern char *fbp_limit_up;


char* Move(int hor, int ver, char *current_fbp, char *pixel, int width, int height)
{
	if(hor < 0)
		current_fbp -= abs(hor) * vinfo.bits_per_pixel / 8;
	else
		current_fbp += abs(hor) * vinfo.bits_per_pixel / 8;
	
	if(ver < 0)
		current_fbp -= abs(ver) * finfo.line_length;
	else
		current_fbp += abs(ver) * finfo.line_length;

//	drawBmp(current_fbp, pixel, width, height);
	drawBmpPlus(current_fbp, pixel, width, height, 1, 1);

	return current_fbp;
}

void buildBackground(char *fbp)
{
	char path[32] = "pige.bmp";
	int row=200;
	char *current_fbp = fbp;

	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(info_header) );
	ReadBitmapInfoHeader(path, &info_header);

	char *pixel = (char *) malloc( info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8 );
	getBmpPixel(path, pixel);

	for( ; ; )
	{
		usleep(20000);
		Move(0, row, current_fbp, pixel, info_header.ciWidth, info_header.ciHeight);
		row++;
		if(row == 700)
			row=200;
	}

}


int main()
{
	int press=0;
	char path[32] = "dog.bmp";
	char path2[32] = "pige.bmp";

	char *fbp = fbd_init();
	char *current_fbp = fbp;
//	DrawBmp(fbp, path2);
//	DrawBmp(fbp, path);
	char *pixel;
	struct point p;

	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(info_header) );
	ReadBitmapInfoHeader(path, &info_header);

	pixel = (char *) malloc( info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8 );
	getBmpPixel(path, pixel);
//	drawBmp(current_fbp, pixel, info_header.ciWidth, info_header.ciHeight );

//	buildBackground(fbp);
	
	init_keyboard();
	
	while(press != 'q')
	{
		usleep(20000);
		press = getudlr();
		switch(press)
		{
			case K_UP: current_fbp = Move(0, -18, current_fbp, pixel, info_header.ciWidth, info_header.ciHeight); break;
			case K_DOWN: current_fbp = Move(0, 18, current_fbp, pixel, info_header.ciWidth, info_header.ciHeight); break;
			case K_LEFT: current_fbp = Move(-27, 0, current_fbp, pixel, info_header.ciWidth, info_header.ciHeight); break;
			case K_RIGHT: current_fbp = Move(27, 0, current_fbp, pixel, info_header.ciWidth, info_header.ciHeight); break;
		}
	}

	close_keyboard();

	exit(0);
}
