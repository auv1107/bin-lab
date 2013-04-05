#include "display.h"



int main(int argc, char *argv[])
{
//	char path[32] = "dog.bmp";
	char *path;
	if(argc == 1)
	{
		return -1;
	}
	path = argv[1];
	fbd_init();

	BITMAPINFOHEADER info_header;
	bzero(&info_header, sizeof(info_header));
	ReadBitmapInfoHeader(path, &info_header);
	printf("bit count : %d\n", info_header.ciBitCount);

	int width = info_header.ciWidth;
	int height = info_header.ciHeight;

	int size = info_header.ciWidth * info_header.ciHeight * info_header.ciBitCount / 8;
	char *pixel;
	pixel = (char *) malloc (size);
	getBmpPixel(path, pixel);
	draw_pic_at(10, 10, pixel, width, height);
	fbd_exit();
}
