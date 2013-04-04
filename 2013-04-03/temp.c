#include "kbhit.h"

int main()
{
	int press=0;
	init_keyboard();
	while(press != 'q')
	{
		press = getudlr();
		switch(press)
		{
			case K_UP: printf("UP\n"); break;
			case K_DOWN: printf("DOWN\n"); break;
			case K_LEFT: printf("LEFT\n"); break;
			case K_RIGHT: printf("RIGHT\n"); break;
		}
	}
	close_keyboard();
}
