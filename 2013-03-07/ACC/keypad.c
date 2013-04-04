#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

#define LOCAL_ESCAPE_KEY 27

int main()
{
	int key;

	initscr();
	crmode();
	keypad(stdscr, TRUE);
	noecho();
	clear();
	mvprintw(5, 5, "key pad demonstration. Press 'q' to quit");
	move(7, 5);
	refresh();
	key = getch();

	while(key != ERR && key != 'q')
	{
		move(7, 5);
		clrtoeol();

		if((key >= 'A' && key <= 'Z') || (key >= 'a' && key <= 'z'))
		{
			printw("Key was %c", (char)key);
		}
		else
		{
			switch(key)
			{
				case LOCAL_ESCAPE_KEY: printw("Escape key"); break;
				case KEY_END: printw("END key"); break;
				case KEY_BEG: printw("BEGINNING key"); break;
				case KEY_UP: printw("UP key"); break;
				case KEY_DOWN: printw("DOWN key"); break;
				case KEY_LEFT: printw("LEFT key"); break;
				case KEY_RIGHT: printw("RIGHT key"); break;
				default: printw("Unmatched - %d", key); break;
			}
		}

		refresh();
		key = getch();
	}

	endwin();
	exit(EXIT_SUCCESS);
}

