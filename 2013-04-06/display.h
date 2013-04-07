#ifndef DISPLAY
#define DISPLAY _


#include "showpic.h"
#include "drawpic.h"
#include "basetype.h"

#include <string.h>
#include <stdlib.h>

extern char *fbp;
extern struct fb_var_screeninfo vinfo;
extern struct fb_fix_screeninfo finfo;

void draw_pic_at(int x, int y, char *pixel, int width, int height)
{
	char *p;
	p = fbp + x * vinfo.bits_per_pixel / 8 + y * finfo.line_length;
//	printf("success\n");
//	printf("fbp : %x, p : %x\n", fbp, p);
//	printf("%s\n", pixel);
	drawBmp(p, pixel, width, height);
}

void scale_pic(struct bmpattr* src, int dest_width, int dest_height)
{
	float mulriple_width = ( src->width  ) * 1.0 / ( dest_width );
	float mulriple_height = ( src->height  ) * 1.0 / ( dest_height );

	int src_line_length = src->width * src->bitcount / 8;
	int src_pixel_length = src->bitcount / 8;

	int dest_line_length = dest_width * src->bitcount / 8;
	int dest_pixel_length = src->bitcount / 8;

	float width = 0;
	float height = 0;

	int src_pos;
	int dest_pos = 0;
	

	long size = ( dest_height) * ( dest_line_length + 3);
	char *p = (char *) malloc ( size );
	
	for ( height = 0; height < src->height; height += mulriple_height)
		for ( width = 0; width < src->width; width += mulriple_width)
		{
			src_pos = (int)(width) * src_pixel_length + (int)(height) * src_line_length;
			
			p[dest_pos++] = src->pixel[src_pos++];
			p[dest_pos++] = src->pixel[src_pos++];
			p[dest_pos++] = src->pixel[src_pos++];
		}
	
//	free(src->pixel);
	src->pixel = realloc (src->pixel, size);
	memcpy (src->pixel, p, size );
	src->width = dest_width;
	src->height = dest_height;

//	free (p);
}

void begin_at_line( int line, struct bmpattr *bmp , int x, int y)
{
//	int location = line * bmp->width * bmp->bitcount / 8;
	draw_pic_at ( x, y, bmp->pixel , bmp->width, bmp->height - line);
}



#endif
