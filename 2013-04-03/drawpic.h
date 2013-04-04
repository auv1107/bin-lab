#ifndef DRAWPIC
#define DRAWPIC


#include <stdlib.h>
#include <linux/fb.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stdio.h>

#include "basetype.h"
#include <math.h>

struct fb_var_screeninfo vinfo;
struct fb_fix_screeninfo finfo;
int fp = 0;
long screensize = 0;
char *fbp_limit_up;
char *fbp_limit_low;

struct color current_color;

char *fbd_init()
{
	char *fbp = 0;

	int x = 0, y = 0;
	
	fp = open("/dev/fb0", O_RDWR);
	if (fp < 0)
	{
		perror("open");
		exit(-1);
	}

	if (ioctl(fp, FBIOGET_FSCREENINFO, &finfo) == -1)
	{
		perror("ioctl");
		exit(-1);
	}

	if (ioctl(fp, FBIOGET_VSCREENINFO, &vinfo) == -1)
	{
		perror("ioctl");
		exit(-1);
	}

	screensize = vinfo.xres * vinfo.yres * vinfo.bits_per_pixel / 8 ;

	fbp = (char *) mmap (0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fp, 0);

	if( fbp == MAP_FAILED)
	{
		perror("mmap");
		exit(-2);
	}
	fbp_limit_up = screensize + fbp;
	fbp_limit_low = fbp;

// TODO   config default color

	return fbp;
}

void draw_point(char *fbp, int x, int y)
{
	if(x < 0 || y < 0 || x >= vinfo.xres || y >= vinfo.yres)
		return;

	long location = x * (vinfo.bits_per_pixel / 8) + y * finfo.line_length;
	*(fbp + location) = current_color.blue;
	*(fbp + location + 1) = current_color.green;
	*(fbp + location + 2) = current_color.red;
	*(fbp + location + 3) = current_color.alpha;
}

void Draw_point(char *fbp, struct point p)
{
	draw_point(fbp, p.x, p.y);
}

int fbd_exit(char *fbp)
{
	munmap(fbp, screensize);
	close(fp);
	return 0;
}

void draw_line(char *fbp, int x1, int y1, int x2, int y2)
{
	float k;
	float b;

	if ( x1 == x2 )
	{
		int y = y1 < y2 ? y1 : y2;
		int y0 = y1 > y2 ? y1 : y2;
		for( ; y <= y0; y++)
			draw_point(fbp, x1, y);

		return;
	}

	k = (y1 - y2) / (x1 - x2);
	b = y1 - x1 * k;

	int x = x1 < x2 ? x1 : x2;
	int x0 = x1 > x2 ? x1 : x2;
	int y;

	for( ; x <= x0; x++ )
	{
		y = (int) (k * x + b);
		draw_point(fbp, x, y);
	}
}

void Draw_line(char *fbp, struct point p1, struct point p2)
{
	draw_line(fbp, p1.x, p1.y, p2.x, p2.y);
}


void set_color(unsigned int blue, unsigned int green, unsigned int red, unsigned int alpha)
{
	current_color.blue = blue;
	current_color.green = green;
	current_color.red = red;
	current_color.alpha = alpha;
}

void Set_color(struct color cl)
{
	set_color(cl.blue, cl.green, cl.red, cl.alpha);
}

void draw_circle(char *fbp, int centre_x, int centre_y, int radius)
{
	float pi = 3.1415;
	float redian;
	float accur = 0.0001;

	int x;
	int y;

	for(redian = 0; redian < 2 * pi; redian += accur )
	{
		x = (int) (radius * cos(redian) + centre_x );
		y = (int) (radius * sin(redian) + centre_y );
		draw_point(fbp, x, y);
	}
}

void Draw_circle(char *fbp, struct point centre, int radius)
{
	draw_circle(fbp, centre.x, centre.y, radius);
}

void draw_rectangle(char *fbp, int x1, int y1, int x2, int y2)
{
	draw_line(fbp, x1, y1, x1, y2);
	draw_line(fbp, x1, y1, x2, y1);
	draw_line(fbp, x2, y2, x2, y1);
	draw_line(fbp, x2, y2, x1, y2);
}

void Draw_rectangle(char *fbp, struct point p1, struct point p2)
{
	draw_rectangle(fbp, p1.x, p1.y, p2.x, p2.y);
}

#endif
