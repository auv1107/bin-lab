#include <stdio.h>
#include <stdlib.h>
#include <term.h>
#include <curses.h>
#include <termios.h>
#include <unistd.h>


static FILE *output_stream = (FILE*)0;

char *menu[] = {
	"a - add new record",
	"d - delete record",
	"q - quit",
	NULL,
};

int getchoice(char *greet, char *choices[], FILE *in, FILE *out);
int char_to_terminal(int char_to_write);

int main()
{
	int choice;
	FILE *in;
	FILE *out;
	struct termios initial_settings, new_settings;

	if(!isatty(fileno(stdout)))
	{
		fprintf(stderr, "You are not a terminal, OK.\n");
	}

	in = fopen("/dev/tty", "r");
	out = fopen("/dev/tty", "w");

	if(!in || !out)
	{
		fprintf(stderr, "Unable to open /dev/tty!\n");
		exit(1);
	}

	tcgetattr(fileno(in), &initial_settings);
	new_settings = initial_settings;
	new_settings.c_lflag &= ~ICANON;
	new_settings.c_lflag &= ~ECHO;
	new_settings.c_cc[VMIN] = 1;
	new_settings.c_cc[VTIME] = 0;
	new_settings.c_lflag &= ~ISIG;
	if(tcsetattr(fileno(in), TCSANOW, &new_settings) != 0)
	{
		fprintf(stderr, "could not set attributes\n");
		exit(1);
	}

	do
	{
		choice = getchoice("Welcome....", menu, in, out);
		printf("You have choosed %c\n", choice);
		sleep(1);
	} while(choice != 'q');

	tcsetattr(fileno(in), TCSANOW, &initial_settings);
	exit(0);
}


int getchoice(char *greet, char *choices[], FILE *in, FILE *out)
{
	char **option;
	int chosen = 0;
	int selected;
	int screenrow, screencol = 10;
	char *cursor, *clear;

	output_stream = out;

	setupterm(NULL, fileno(out), (int*)0);
	cursor = tigetstr("cup");
	clear = tigetstr("clear");

	screenrow = 4;
	tputs(clear, 1, char_to_terminal);
	tputs(tparm(cursor, screenrow, screencol), 1, char_to_terminal);
	fprintf(out, "Choice: %s", greet);
	screenrow += 2;
	option = choices;

	while(*option)
	{
		tputs(tparm(cursor, screenrow, screencol), 1, char_to_terminal);
		fprintf(out, "%s", *option);
		option++;
		screenrow++;
	}
	fprintf(out, "\n");

	do
	{
		fflush(out);
		fflush(in);
		selected = fgetc(in);
		option = choices;
		while(*option)
		{
			if(*option[0] == selected)
			{
				chosen = 1;
				break;
			}
			option++;
		}

		if(!chosen)
		{	
			tputs(tparm(cursor, screenrow, screencol), 1, char_to_terminal);
			fprintf(out, "Incorrect choice, select again\n");
		}
	} while(!chosen);

	tputs(clear, 1, char_to_terminal);
	return selected;
}

int char_to_terminal(int char_to_write)
{
	if(output_stream) putc(char_to_write, output_stream);
	return 0;
}



