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
#include "packetfunction.h"

BITMAPFILEHEADER File_header;
BITMAPINFOHEADER Info_header;

extern struct fb_var_screeninfo vinfo;
extern struct fb_fix_screeninfo finfo;
extern char *fbp_limit_low;
extern char *fbp_limit_up;

void ReadBitmapFileHeader(char *path, BITMAPFILEHEADER *file_header)
{
	int fp = Open(path, O_RDONLY);
	Lseek(fp, 0, SEEK_SET);
	Read(fp, file_header->cfType, 2);
	Read(fp, &file_header->cfSize, 4);
	Read(fp, &file_header->cfReserved, 4);
	Read(fp, &file_header->cfoffBits, 4);
/*
	printf("cfType : %s\n", file_header->cfType);
	printf("cfSize : %ld\n", file_header->cfSize);
	printf("cfReserved : %ld\n", file_header->cfReserved);
	printf("cfoffBits : %ld\n", file_header->cfoffBits);
*/
	Close(fp);

}

void readBitmapFileHeader(int fp, BITMAPFILEHEADER *file_header)
{
	Lseek(fp, 0, SEEK_SET);
	Read(fp, file_header->cfType, 2);
	Read(fp, &file_header->cfSize, 4);
	Read(fp, &file_header->cfReserved, 4);
	Read(fp, &file_header->cfoffBits, 4);
/*
	printf("cfType : %s\n", file_header->cfType);
	printf("cfSize : %ld\n", file_header->cfSize);
	printf("cfReserved : %ld\n", file_header->cfReserved);
	printf("cfoffBits : %ld\n", file_header->cfoffBits);
*/

}

void ReadBitmapInfoHeader(char *path, BITMAPINFOHEADER *info_header)
{
	int fp = Open(path, O_RDONLY);
	Lseek(fp, 14, SEEK_SET);
	Read(fp, info_header->ciSize, 4);
	Read(fp, &info_header->ciWidth, 4);
	Read(fp, &info_header->ciHeight, 4);
	Read(fp, info_header->ciPlanes, 2);
	Read(fp, &info_header->ciBitCount, 2);
	Read(fp, info_header->ciCompress, 4);
	Read(fp, info_header->ciSizeImage, 4);
	Read(fp, info_header->ciXPelsPerMeter, 4);
	Read(fp, info_header->ciYPelsPerMeter, 4);
	Read(fp, info_header->ciClrUsed, 4);
	Read(fp, info_header->ciClrImportant, 4);
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
	Close(fp);
}

void readBitmapInfoHeader(int fp, BITMAPINFOHEADER *info_header)
{
	Lseek(fp, 14, SEEK_SET);
	Read(fp, info_header->ciSize, 4);
	Read(fp, &info_header->ciWidth, 4);
	Read(fp, &info_header->ciHeight, 4);
	Read(fp, info_header->ciPlanes, 2);
	Read(fp, &info_header->ciBitCount, 2);
	Read(fp, info_header->ciCompress, 4);
	Read(fp, info_header->ciSizeImage, 4);
	Read(fp, info_header->ciXPelsPerMeter, 4);
	Read(fp, info_header->ciYPelsPerMeter, 4);
	Read(fp, info_header->ciClrUsed, 4);
	Read(fp, info_header->ciClrImportant, 4);
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
//	char *pixel = (char*) malloc (size);
	Lseek(fp, 54, SEEK_SET);
	int len = Read(fp, pixel, size);
//	printf("len: %d\n", len);
//	memcpy(p, pixel, size);
	//free(pixel);
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
	int fp = Open(path, O_RDONLY);

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
	Close(fp);
}

void getBmpPixel(char *path, char *pixel)
{
	int fp = Open(path, O_RDONLY);

	BITMAPFILEHEADER file_header;
	BITMAPINFOHEADER info_header;
	bzero(&file_header, sizeof(file_header) );
	bzero(&info_header, sizeof(info_header) );

	readBitmapFileHeader(fp, &file_header);
	readBitmapInfoHeader(fp, &info_header);

	long size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
//	readBmpPixel(fp, size, pixel);
	Lseek(fp, 54, SEEK_SET);
	int len = Read(fp, pixel, size);


	Close(fp);
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
	int fp = Open(path, O_RDONLY);

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
	free (pixel);

	Close(fp);
}


void readn(char *path, char *pixel, int size)
{
	int sleft = size;
	char *p = (char *) malloc (size);
	int fd = Open(path, O_RDONLY);
	int len;
	Lseek (fd, 54, SEEK_SET);

//	while(sleft > 0)
	{
		len = Read (fd, p, 1024);
		sleft -= len;
		printf("len : %d\n", len);
		p += len;
	}
	memcpy ( pixel, p, size );

// TIPS  bad address for read
}
#endif

