#ifndef SHOWPIC
#define SHOWPIC


#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <stdio.h>
#include <string.h>

#include "basetype.h"
#include "drawpic.h"

BITMAPFILEHEADER File_header;
BITMAPINFOHEADER Info_header;

extern struct fb_var_screeninfo vinfo;
extern struct fb_fix_screeninfo finfo;
extern char *fbp_limit_low;
extern char *fbp_limit_up;

void ReadBitmapFileHeader(char *path, BITMAPFILEHEADER *file_header)
{
	int fp = open(path, O_RDONLY);
	lseek(fp, 0, SEEK_SET);
	read(fp, file_header->cfType, 2);
	read(fp, &file_header->cfSize, 4);
	read(fp, &file_header->cfReserved, 4);
	read(fp, &file_header->cfoffBits, 4);
/*
	printf("cfType : %s\n", file_header->cfType);
	printf("cfSize : %ld\n", file_header->cfSize);
	printf("cfReserved : %ld\n", file_header->cfReserved);
	printf("cfoffBits : %ld\n", file_header->cfoffBits);
*/
	close(fp);

}

void readBitmapFileHeader(int fp, BITMAPFILEHEADER *file_header)
{
	lseek(fp, 0, SEEK_SET);
	read(fp, file_header->cfType, 2);
	read(fp, &file_header->cfSize, 4);
	read(fp, &file_header->cfReserved, 4);
	read(fp, &file_header->cfoffBits, 4);
/*
	printf("cfType : %s\n", file_header->cfType);
	printf("cfSize : %ld\n", file_header->cfSize);
	printf("cfReserved : %ld\n", file_header->cfReserved);
	printf("cfoffBits : %ld\n", file_header->cfoffBits);
*/

}

void ReadBitmapInfoHeader(char *path, BITMAPINFOHEADER *info_header)
{
	int fp = open(path, O_RDONLY);
	lseek(fp, 14, SEEK_SET);
	read(fp, info_header->ciSize, 4);
	read(fp, &info_header->ciWidth, 4);
	read(fp, &info_header->ciHeight, 4);
	read(fp, info_header->ciPlanes, 2);
	read(fp, &info_header->ciBitCount, 2);
	read(fp, info_header->ciCompress, 4);
	read(fp, info_header->ciSizeImage, 4);
	read(fp, info_header->ciXPelsPerMeter, 4);
	read(fp, info_header->ciYPelsPerMeter, 4);
	read(fp, info_header->ciClrUsed, 4);
	read(fp, info_header->ciClrImportant, 4);
/*
	printf("ciSize: %s\n", info_header->ciSize);
	printf("ciWidth: %ld\n", info_header->ciWidth);
	printf("ciHeight: %ld\n", info_header->ciHeight);
	printf("ciPlanes: %s\n", info_header->ciPlanes);
	printf("ciBitCount: %d\n", info_header->ciBitCount);
	printf("ciCompress: %s\n", info_header->ciCompress);
	printf("ciSizeImage: %s\n", info_header->ciSizeImage);
	printf("ciXPelsPerMeter: %s\n", info_header->ciXPelsPerMeter);
	printf("ciYPelsPerMeter: %s\n", info_header->ciYPelsPerMeter);
	printf("ciClrUsed: %s\n", info_header->ciClrUsed);
	printf("ciClrImportant: %s\n", info_header->ciClrImportant);
*/
	close(fp);
}

void readBitmapInfoHeader(int fp, BITMAPINFOHEADER *info_header)
{
	lseek(fp, 14, SEEK_SET);
	read(fp, info_header->ciSize, 4);
	read(fp, &info_header->ciWidth, 4);
	read(fp, &info_header->ciHeight, 4);
	read(fp, info_header->ciPlanes, 2);
	read(fp, &info_header->ciBitCount, 2);
	read(fp, info_header->ciCompress, 4);
	read(fp, info_header->ciSizeImage, 4);
	read(fp, info_header->ciXPelsPerMeter, 4);
	read(fp, info_header->ciYPelsPerMeter, 4);
	read(fp, info_header->ciClrUsed, 4);
	read(fp, info_header->ciClrImportant, 4);
/*
	printf("ciSize: %s\n", info_header->ciSize);
	printf("ciWidth: %ld\n", info_header->ciWidth);
	printf("ciHeight: %ld\n", info_header->ciHeight);
	printf("ciPlanes: %s\n", info_header->ciPlanes);
	printf("ciBitCount: %d\n", info_header->ciBitCount);
	printf("ciCompress: %s\n", info_header->ciCompress);
	printf("ciSizeImage: %s\n", info_header->ciSizeImage);
	printf("ciXPelsPerMeter: %s\n", info_header->ciXPelsPerMeter);
	printf("ciYPelsPerMeter: %s\n", info_header->ciYPelsPerMeter);
	printf("ciClrUsed: %s\n", info_header->ciClrUsed);
	printf("ciClrImportant: %s\n", info_header->ciClrImportant);
*/
}


void readBmpPixel(int fp, long size, char *pixel)
{
	lseek(fp, 54, SEEK_SET);
	int len = read(fp, pixel, size);

}


void drawBmp(char *fbp, char *pixel, long width, long height)
{

	int location;
	int x=0, y=0;
	char *p = pixel;
	while(p != NULL)	
	{
		location = (height - y - 1) * finfo.line_length + x * vinfo.bits_per_pixel / 8;

		if(fbp + location <= fbp_limit_up && fbp + location >= fbp_limit_low)
		{
			*(fbp+location) = *p++ ; 
			*(fbp+location+1) = *p++ ;
			*(fbp+location+2) = *p++ ;
			*(fbp+location+3) = 0 ;
		}
		else
		{
			p+=3;
		}

		x++;
		if(x == width)
		{
			x = 0;
			y++;
			if(y == height)
				break;
		}
	} 
}


void DrawBmp(char *fbp, char *path)
{
	int fp = open(path, O_RDONLY);
	if(fp == -1)
	{
		perror("open");
		exit(-1);
	}
	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER info_header;
	bzero(&file_header, sizeof(file_header) );
	bzero(&info_header, sizeof(info_header) );

	readBitmapFileHeader(fp, &file_header);
	readBitmapInfoHeader(fp, &info_header);

	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	char *pixel = (char *)malloc (size);
	readBmpPixel(fp, size, pixel);

	drawBmp(fbp, pixel, info_header.ciWidth, info_header.ciHeight);
	close(fp);
}

void getBmpPixel(char *path, char *pixel)
{
	int fp = open(path, O_RDONLY);
	if(fp == -1)
	{
		perror("open");
		exit(-1);
	}
	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER info_header;
	bzero(&file_header, sizeof(file_header) );
	bzero(&info_header, sizeof(info_header) );

	readBitmapFileHeader(fp, &file_header);
	readBitmapInfoHeader(fp, &info_header);

	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	readBmpPixel(fp, size, pixel);

	close(fp);
}



void drawBmpPlus(char *fbp, char *pixel, long width, long height, int mul_row, int mul_col)
{

	int location;
	int x=0, y=0;
	char *p = pixel;
	width = width * mul_col;
	while(p != NULL)	
	{
		location = (height - y * mul_row - 1) * finfo.line_length + x * vinfo.bits_per_pixel / 8;

		if(fbp + location <= fbp_limit_up && fbp + location >= fbp_limit_low)
		{
			*(fbp+location) = *p++ ; 
			*(fbp+location+1) = *p++ ;
			*(fbp+location+2) = *p++ ;
			*(fbp+location+3) = 0 ;
		}
		else
		{
			p+=3;
		}

		x += mul_col;
		if(x == width)
		{
			x = 0;
			y++;
			if(y == height)
				break;
		}
	} 
}



void getPixelWidthHeight(char *path, char *pixel, int *width, int *height)
{
	int fp = open(path, O_RDONLY);
	if(fp == -1)
	{
		perror("open");
		exit(-1);
	}
	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER info_header;
	bzero(&file_header, sizeof(file_header) );
	bzero(&info_header, sizeof(info_header) );

	readBitmapFileHeader(fp, &file_header);
	readBitmapInfoHeader(fp, &info_header);

	*width = info_header.ciWidth;
	*height = info_header.ciHeight;

	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;

	pixel = (char*) malloc (size);
	readBmpPixel(fp, size, pixel);

	close(fp);
}


#endif

