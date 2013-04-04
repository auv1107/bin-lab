#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

int main()
{
	WINDOW *win = initscr();

	move(5,15);
	printw("Hello World");
//	refresh();

	move(30,9);
	box(win, ACS_VLINE, ACS_HLINE);
	refresh();
	beep();
	flash();

	sleep(2);
	
	endwin();
	exit(EXIT_SUCCESS);
}
