#include "kbhit.h"

int main()
{
	init_keyboard();
	int up=kbhit();
	int down = kbhit();
	int left= kbhit();
	int right = kbhit();

	int press=0;
	while(press != 'q')
	{
		usleep(20);
		press = kbhit();
		if(press == 27)
		if((press = kbhit()) == 91)
		switch(press=kbhit())
		{
			case 65: printf("up\n"); break;
			case 66: printf("down\n"); break;
			case 68: printf("left\n"); break;
			case 67: printf("right\n"); break;
		}

/*	if(press == 27)
	{
		if(kbhit() == 91 && kbhit() == 65)
		{
				printf("up\n");
		}
	}
*/	}

	close_keyboard();
}
