#include "packet.h"

#define ORANGE 1
#define APPLE 0
#define TIME_FOR_ORANGE 1
#define TIME_FOR_APPLE 2
#define TIME_FOR_EATING_ORANGE 5
#define TIME_FOR_EATING_APPLE 3

void* father_work();
void* daughter_work();
void* son_work();

int sem_id;
int fruit;
int start_time;

int main()
{
	int i;
	sem_id = semget(IPC_PRIVATE, 3, 0666);
	set_sem(sem_id, 0, 0);
	set_sem(sem_id, 1, 0);
	set_sem(sem_id, 2, 3);

	int pid;
	start_time = time(0);

		pid = fork();
		
		if(pid == 0)
		{
			father_work();
		}
		else
		if(pid > 0)
		{
			pid = fork();
			if(pid == 0)
				daughter_work();
			else
			if(pid > 0)
			{
				pid = fork();
				if(pid == 0)
					son_work();
				
				if(pid > 0)
					wait(NULL);
			}
		}

	exit(0);
}

void* father_work()
{
	srand(time((void*)0) );

	for( ; ; )
	{
		sem_p(sem_id, 2);
		fruit = rand() % 2;

		if(fruit == APPLE)
		{
			Printf("父亲开始削苹果\n");
			sleep(TIME_FOR_APPLE);
			Printf("父亲削完了一个苹果\n");
			sem_v(sem_id, APPLE);
		}
		if(fruit == ORANGE)	
		{
			Printf("父亲开始剥橘子\n");
			sleep(TIME_FOR_ORANGE);
			Printf("父亲剥完了一个橘子\n");
			sem_v(sem_id, ORANGE);
		}
	}
	pthread_exit(0);
}

void* daughter_work()
{
	for( ; ; )
	{
		sleep(TIME_FOR_EATING_ORANGE);
		sem_p(sem_id, ORANGE);
		Printf("女儿吃掉了一个橘子\n");

		sem_v(sem_id, 2);
	}
	pthread_exit(0);
}

void* son_work()
{
	for( ; ; )
	{
		sleep(TIME_FOR_EATING_APPLE);
		sem_p(sem_id, APPLE);
		Printf("儿子吃掉了一个苹果\n");

		sem_v(sem_id, 2);
	}
	pthread_exit(0);
}
