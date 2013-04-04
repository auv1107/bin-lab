#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>

extern int start_time;

void Printf(const char* buf)
{
	int cur_time = time(0);
	printf("%d :  %s", cur_time-start_time, buf);
}

union semun 
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

int set_sem(int sem_id, int num, int val)
{
	union semun sem_union;

	sem_union.val = val;
	if (semctl(sem_id, num, SETVAL, sem_union) == -1)
	{
		perror("set_sem");
		exit(-1);
	}
	return 1;
}

void del_sem(int sem_id, int num)
{
	union semun sem_union;

	if (semctl(sem_id, num, IPC_RMID, sem_union) == -1)
	{
		perror("del_sem");
		exit(-1);
	}
}

int sem_p(int sem_id, int num)
{
	struct sembuf sem_b;

	sem_b.sem_num = num;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	if (semop(sem_id, &sem_b, 1) == -1)
	{
		perror("sem_p");
		exit(-1);
	}
	return 1;
}

int sem_v(int sem_id, int num)
{
	struct sembuf sem_b;

	sem_b.sem_num = num;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	if (semop(sem_id, &sem_b, 1) == -1)
	{
		perror("sem_p");
		exit(-1);
	}
	return 1;
}

