#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <term.h>
#include <curses.h>
#include <unistd.h>


#define K_UP -99
#define K_DOWN -98
#define K_LEFT -97
#define K_RIGHT -96

static struct termios initial_settings, new_settings;
static int peek_character = -1;

void init_keyboard()
{
	tcgetattr(0, &initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_lflag &= ~ISIG;
	tcsetattr(0, TCSANOW, &new_settings);
}

void close_keyboard()
{
	tcsetattr(0, TCSANOW, &initial_settings);
}

int kbhit_simple()
{
	int hit;
	peek_character = fgetc(stdin);
	if(peek_character == -1)
		return 0;
	return 1;
}

int kbhit()
{
	char ch;
	int nread;

	if(peek_character != -1)
		return 1;
	new_settings.c_cc[VMIN] = 0;
	tcsetattr(0, TCSANOW, &new_settings);
	nread = read(0, &ch, 1);
	new_settings.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &new_settings);
	return ch;
}

int readch()
{
	char ch = peek_character;
	peek_character = -1;
	return ch;
}

int getudlr()
{
	int press = kbhit();
	if(press == 27 && kbhit() == 91)
	switch(kbhit())
	{
		case 65: return K_UP;
		case 66: return K_DOWN;
		case 68: return K_LEFT;
		case 67: return K_RIGHT;
	}
	return press;
}
