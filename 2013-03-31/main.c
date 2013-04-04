#include "packet.h"
#include <pthread.h>

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

int main()
{
	int i;
	sem_id = semget(IPC_PRIVATE, 3, 0666);
	set_sem(sem_id, 0, 0);
	set_sem(sem_id, 1, 0);
	set_sem(sem_id, 2, 3);

	int pid;
	pthread_t tid[3];
	pthread_attr_t attr[3];

		pid = fork();
		
		if(pid == 0)
		{
			for( i = 0; i < 3; i++ )
				pthread_attr_init(attr+i);

			pthread_create(tid, attr, father_work, NULL);
			pthread_create(tid+1, attr+1, daughter_work, NULL);
			pthread_create(tid+2, attr+2, son_work, NULL);
			
			for( i = 0; i < 3; i++ )
			{
				pthread_join(*(tid+i), NULL);
				sleep(1);
			}
		}
		else
		if(pid > 0)
		{
			wait(NULL);
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
			sleep(TIME_FOR_APPLE);
			printf("Father ***ed an apple\n");
			sem_v(sem_id, APPLE);
		}
		if(fruit == ORANGE)	
		{
			sleep(TIME_FOR_ORANGE);
			printf("Father ***ed an orange\n");
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
		printf("Daughter ate an orange\n");

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
		printf("Son ate an apple\n");

		sem_v(sem_id, 2);
	}
	pthread_exit(0);
}
