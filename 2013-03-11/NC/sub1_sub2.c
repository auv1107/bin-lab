#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <sys/types.h>


#define SUB1_START_COL 10
#define SUB1_END_COL COLS-10
#define SUB1_START_ROW 3
#define SUB1_END_ROW 32
#define SUB2_START_ROW 34
#define SUB2_END_ROW LINES-2
#define FILE_NAME "temp.db"
#define MAX_SIZE 1024

int main()
{
	FILE *fp = fopen(FILE_NAME, "r");
	int current_row = 1;
	int start_col = 1;
	char str[MAX_SIZE];
	int times = 0;

	initscr();

	WINDOW *new_sub_window = subwin(stdscr, SUB1_END_ROW - SUB1_START_ROW, SUB1_END_COL - SUB1_START_COL, SUB1_START_ROW, SUB1_START_COL);

	box(new_sub_window, ACS_VLINE, ACS_HLINE);
	while(1)
	{
	while(fgets(str, MAX_SIZE, fp) && current_row < SUB1_END_ROW - SUB1_START_ROW - 1 )
	{
		mvwprintw(new_sub_window, current_row++, start_col, "%s: %d", str, current_row);
		refresh();
		sleep(1);
	}
//		fseek(fp, 0, SEEK_SET); 
		fclose(fp);
		FILE *fp = fopen(FILE_NAME, "r");
		current_row = 1;
		times++;
		mvprintw(LINES-1, COLS, "%d", times);
		refresh();
		sleep(1);
	}
	refresh();
	sleep(3);
	fclose(fp);
	delwin(new_sub_window);
	endwin();
	exit(EXIT_SUCCESS);
}
