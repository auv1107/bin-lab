#include <unistd.h>
#include <stdlib.h>
#include <curses.h>

#define BASE_COLOR 0

int main()
{
	initscr();
	start_color();
	int x_loop, y_loop;
	x_loop = 0;
	y_loop = 0;
	short color_green, color_blue, color_red;
	color_green = BASE_COLOR;
	color_blue = BASE_COLOR;
	color_red = BASE_COLOR;

	clear();

	if(can_change_color())
		mvprintw(20,20, "Can change\n");
	else
		mvprintw(20, 20, "Can't change color\n");

	sleep(2);


	for(y_loop = 0; y_loop <= LINES; y_loop++)
	{
		for(x_loop = 0; x_loop <= COLS; x_loop++)
		{
			if(init_color(COLOR_GREEN, color_red, color_green, color_blue) != OK)
				continue;
			init_pair(1, COLOR_BLUE, COLOR_GREEN);
			attrset(COLOR_PAIR(1));
			mvprintw(y_loop, x_loop, " ");
			color_red += 1000 / COLS;
			color_blue += 1000 / COLS;
			refresh();
		}
		refresh();
		if(y_loop % 5 == 0)
			sleep(1);
		color_red = BASE_COLOR;
		color_blue = BASE_COLOR;
		color_green += 1000 / LINES;
	}

	refresh();
	sleep(5);

	clear();

	attrset(COLOR_PAIR(0));
	mvprintw(10, 10, "COLS: %d   ROWS: %d   COLORS: %d   COLOR_PAIRS: %d", COLS, LINES, COLORS, COLOR_PAIRS);
	refresh();
	sleep(3);
	clear();
	endwin();
	exit(EXIT_SUCCESS);
}
