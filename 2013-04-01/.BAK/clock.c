#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

void show_time_as_normal();
void show_time_as_self();

int freq = 1;
char format[100];

int main(int argc, char *argv[])
{
	int opt;
	int mod = 0;

	printf("Usage: ./clock [-f frequency] [-t farmat]\n\n");

	while((opt = getopt(argc, argv, "f:t:")) != -1)
	{
		switch(opt)
		{
			case 't': mod = 1; strcpy(format, optarg); break;
			case 'f': freq = optarg[0] - '0'; break;
			case '?': printf("unknown option: %c\n", optopt);
						break;
		}
	}
//	printf("%d  %d %s\n", mod, freq, format);

	switch(mod)
	{
		case 0: show_time_as_normal(); break;
		case 1: show_time_as_self(); break;
	}

	exit(0);
}


void show_time_as_normal()
{
	while(1)
	{
		time_t t = time(0);
		printf("%s", ctime(&t) );
		sleep(freq);
	}
}

void show_time_as_self()
{
	char buf[64];
	while(1)
	{
		time_t  t = time(0);
		struct tm *timer = localtime(&t);
		strftime(buf, 63, format, timer);
		printf("%s\n", buf);
		sleep(freq);
	}
}

