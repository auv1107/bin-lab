#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>

int main(int argc, char *argv[])
{
	if ( argc != 2 && argc != 3 )
	{
		printf("Usage: ./timetst yourprogram [time]\n");
		exit(-1);
	}

	int pid = fork();
	
		if(pid == 0)
		{
			execv(argv[1], NULL);
		}
		else
		{
			time_t start_time = time(0);
			if(argc == 2 || atoi(argv[2]) == 0)
				wait();
			else
			{
				sleep(atoi(argv[2]));
				kill(pid, SIGINT);
			}

			time_t end_time = time(0);
			int timespan = end_time - start_time;

			printf("run time: %d\n", timespan);
		}

	exit(0);
}



