#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct process
{
	int pid;
	int cpuBurst;
	struct process *next;
} Process;

void get_info(Process* p);
void print_process(Process *p);
void fcfs(Process*);
void round_robin(Process*);

int sum_of_burst_time = 0;
int sum_of_process = 0;

int main()
{
	Process head;
	Process *p = &head;

	get_info(p);

	printf("%d\n", sum_of_burst_time);

	p = &head;
	fcfs(p);

	p = &head;
	round_robin(p);
	
}

void print_process(Process *p)
{
	printf("%d: %d\n", p->pid, p->cpuBurst);
}

void get_info(Process* p)
{
	int i;
	for(i=0; scanf("%d", &p->cpuBurst) != -1; i++)
	{
		p->pid = i;
		p->bak = p->cpuBurst;
		sum_of_burst_time += p->cpuBurst;
		Process* new_process;
		new_process = (Process*)malloc(sizeof(Process));
		p->next = new_process;
		p = p->next;
		p->next = NULL;
	}
	sum_of_process = i;
}

void fcfs(Process *head)
{
	Process *p = head;
	int wait_times = 0;
	int run_times = 0;
	printf("FCFS:\n\t");
	for( ; p->next != NULL; p = p->next)
	{
		printf("|  P%d  ", p->pid);
		if(p->next->next != NULL)
			wait_times += p->cpuBurst;
		run_times += run_times + p->cpuBurst;
	}

	printf("|\n\t");
	int times=0;

	p = head;
	printf("0");
	for( ; p->next != NULL; p = p->next)
	{
		times += p->cpuBurst;
		printf("%7d", times);
	}

	printf("\n");
	printf("average wait time: %.2f\n", wait_times*1.0/sum_of_process);
	printf("average run time: %.2f\n", run_times*1.0/sum_of_process);
}

void round_robin(Process *head)
{
	int timespace = 2;
	Process *p = head;
	int times = 0;
	int wait_times = 0;
	int run_times = 0;
	char buf[1024] = "0";
	int num_of_process = sum_of_process;
	
	printf("Round Robin\n\t");
	for( ; p->next != NULL; )
	{
		if(p->cpuBurst > 0)
		{
			printf("|  P%d  ", p->pid);
			if(p->cpuBurst >= timespace)
			{
				p->cpuBurst -= timespace;
				times += timespace;
				wait_times += (num_of_process - 1) * 2;
				sprintf(buf, "%s%7d", buf, times);
			}
			else
			{
				times += p->cpuBurst;
				run_times += times;
				wait_times += (num_of_process - 1) * p->cpuBurst;
				num_of_process--;
				p->cpuBurst = 0;
				sprintf(buf, "%s%7d", buf, times);
			}
		}
		if(times >= sum_of_burst_time)
			break;
		else 
		if(p->next->next == NULL)
			p = head;
		else
			p = p->next;
	}

	printf("|\n\t");
	printf("%s\n", buf);
	printf("\n");
	printf("average wait time: %.2f\n", wait_times*1.0/sum_of_process);
	printf("average run time: %.2f\n", run_times*1.0/sum_of_process);
}

