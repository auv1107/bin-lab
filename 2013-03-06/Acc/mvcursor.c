#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>

int main()
{
	char *cursor;
	char *esc_sequence;

	setupterm(NULL, fileno(stdout), (int*)0);

	cursor = tigetstr("cup");
	esc_sequence = tparm(cursor, 5, 100);
	putp(esc_sequence);
//	printf("cursor, 5, 30\n");
	exit(0);
}
