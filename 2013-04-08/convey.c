#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct words
{
	char word[21];
	char follow[21];
	
	int ring;
	int number;

	int ensure;

	struct words *next;
};

struct words head[101];
int number_of_player;
int number_of_list;
int number_of_char;
char sentence[100][21];


void readwords()
{
	scanf("%d %d", &number_of_player, &number_of_list);
	number_of_player--;
	
	int i = 0;
	for ( ; i < number_of_list; i++)
	{
		bzero (&head[i], sizeof(struct words) );
		scanf ("%s", head[i].word);
		scanf ("%s", head[i].follow);
		head[i].next = NULL;
		head[i].ring = 0;
		head[i].number = 0;
		head[i].ensure = 0;
	}
	i = 0;
	do 
	{
		scanf("%s", sentence[i++]);
	} while(getchar() != '\n');
	number_of_char = i;
}

void printlist()
{
	int i = 0;
	for ( ; i < number_of_list; i++)
	{
		printf("%s %s %d %d %d\n", head[i].word, head[i].follow, head[i].ring, head[i].number, head[i].ensure);
	}
	i = 0;
	for ( ; i < number_of_char; i++)
	{
		printf("%s ", sentence[i]);
	}
	printf("\n");
}

void findnext()
{
	int i = 0;
	int j;
	for ( ; i < number_of_list; i++)
	{
		for ( j = i+1; j < number_of_list; j++)
		{
			if ( strcmp (head[i].follow, head[j].word) == 0)
				head[i].next = &head[j];
			if ( strcmp (head[j].follow, head[i].word) == 0)
				head[j].next = &head[i];
		}
	}
}

void _findnext()
{
	int i = 0;
	for ( ; i < number_of_list; i++)
	{
		if (head[i].next != NULL)
			printf("%s -> %s\n", head[i].word, head[i].follow);
	}
}

void findring()
{
	int i = 0;
	int n = 1;
	for ( ; i < number_of_list; i++)
	{
		struct words* p = &head[i];
		if ( p->ensure == 1)
			continue;

		for ( ; p != NULL; p = p->next)
		{
			if (p->ensure == 1)
				break;
			if (p->number != 0)
			{
				p->ring = 1;
				p->number = n - p->number;
				p->ensure = 1;
				n++;
			}
			else
			{
				p->number = n++;
			}
		}
		
		p = &head[i];
		for ( ; p != NULL && p->ensure != 1; p = p->next)
		{
				p->number = 0;
		}
		n = 1;
	}
}

void length_for_noring()
{
	int i = 0;
	int n = 0;
	for ( ; i < number_of_list; i++)
	{
		if ( head[i].ensure == 1)
			continue;

		struct words* p = &head[i];
		for ( ; p != NULL && p->ensure != 1; p = p->next, n++);
		if ( p == NULL)
		{
			head[i].ring = 0;
			head[i].number = n;
			head[i].ensure = 1;
		}
		else
		if ( p->ring == 1)
		{
			head[i].ring = 2;
			head[i].number = n;
			head[i].ensure = 1;
		}
		else
		if ( p->ring == 2)
		{
			head[i].ring = 2;
			head[i].number = n + p->number;
			head[i].ensure = 1;
		}
		else
		{
			head[i].ring = 0;
			head[i].number = n + p->number;
			head[i].ensure = 1;
		}
		n = 0;
	}
}

void gofindthe(int n, struct words* p)
{
	int i = 1;
	for ( ; i < n && p->next != NULL; p = p->next, i++);

	printf(" %s", p->follow);
}

struct words* findword(char * word)
{
	int i = 0;
	for ( ; i < number_of_list; i++)
	{
		if ( strcmp ( word, head[i].word) == 0)
		return &head[i];
	}
	return NULL;
}

void instead()
{
	int i = 0;
	for ( ; i < number_of_char; i++)
	{
		struct words* p = findword(sentence[i]);
		if ( p == NULL)
		{
			printf(" %s", sentence[i]);
			continue;
		}

		if (p->ring == 1)
			gofindthe ( (number_of_player - 1) % p->number + 1, p);
		if (p->ring == 2)
		{
			if ( p->number >= number_of_player)
				gofindthe ( number_of_player, p);
			else
			{
				int t = 0;
				for ( ; p->ring != 1; p = p->next, t++);
				gofindthe ( number_of_player - t, p);
			}
		}
		if (p->ring == 0)
			gofindthe ( number_of_player, p );
	}
}

int main()
{
	int number_of_group;
	scanf("%d", &number_of_group);

	int i = 0;
	for ( ; i < number_of_group; i++)
	{
		printf("Case #%d:", i+1);
			readwords();
			findnext();
//			_findnext();
			findring();
			length_for_noring();
//			printlist();
			instead();
		printf("\n");
	}
	return 0;
}
