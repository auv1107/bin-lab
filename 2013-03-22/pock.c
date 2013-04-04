#include <stdio.h>
#include <time.h>
#include <stdlib.h>

struct Pock
{
	int order;
	int weight;
};

int cmp(const void *a, const void *b)
{
	return ((struct Pock*)a)->weight - ((struct Pock*)b)->weight;
}

int main()
{
	srand(time(0));
	struct Pock pock[54];
	char shape[4] = { 'A', 'B', 'C', 'D' };
	int i;

	for(i = 0; i < 54; i++)
	{
		pock[i].order = i;
		pock[i].weight = rand() % 30000;
	}

	qsort(pock, 54, sizeof(struct Pock), cmp);
	
	for(i = 0; i < 54; i++)
	{	
		printf("%d %c\n", pock[i].order/4 + 1, shape[pock[i].order%4]);
	}
	return 0;
}
