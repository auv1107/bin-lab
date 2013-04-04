#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH_OF_ID 20
#define NUM_OF_KEYWORD 6
#define MAX_LENGTH_OF_LINE 1024

void lexical();
void getdigit(int);

char prom[MAX_LENGTH_OF_LINE] = "";
char *keyword[6]={"for","if","then","else","while","do"};
char *p;
int row = 0;
int num = 0;
char id[MAX_LENGTH_OF_ID] = "";
int token;
int j=0;

int main()
{
	gets(prom);
	p = prom;

	do
	{
		lexical();
		switch(token)
		{
//			case 11: printf("(%d,%d)", token, num); break;
			case -1: printf("\nerror occured in line %d\n", row); break;
			case 10: printf("(%d,'%s')", token, id); break;
			default: printf("(%d,%s)", token, id); break;
		}
	} while(token != 0);
	printf("\n");
	exit(0);
}

void lexical()
{
	j = 0;
	char ch = *p;
	num = 0;
	int i = 0;
	while(*p == ' ' || *p == '\t' || *p == '\n')
	{
		if(*p == '\n') row++;
		p++;
	}

	if(*p >= 'a' && *p <= 'z' || *p >= 'A'  && *p <= 'Z')
	{
		while(*p >= 'a' && *p <= 'z' || *p >= 'A'  && *p <= 'Z' || *p >= '0' && *p <= '9')
		{
			id[j++] = *(p++);
		}
		id[j] = '\0';
		
		while(strcmp(id, keyword[i]) != 0)
		{
			i++;
			if( i == NUM_OF_KEYWORD )
			{
				token = 10;
				return;
			}
		}
		token = i + 1;

		return;
	}
	
	if(*p >= '0' && *p <= '9')
	{
		token = 11;
		while(*p >= '0' && *p <= '9')
		{
//			num = num * 10 + *p - '0';
			id[j++] = *p;
			p++;
		}
		if(*p == '.')
		{
			id[j++] = *p;
			p++;
			if(*p < '0' || *p > '9')
			{
				token = -1;
				return;
			}
			else
			{
//			printf("\n%c\n", *p);
//				getdigit(j);
	while(*p >= '0' && *p <= '9')
	{
		id[j++] = *p;
		p++;
	}
				if(*p == 'e' || *p == 'E')
				{
					id[j++] = *p;
					p++;
					if(*p == '+' || *p == '-')
					{
						id[j++] = *p;
						p++;
					}
					getdigit(j);
				}
			}
			token = 11;
			return;
		}

		if(*p == 'e' || *p == 'E')
		{
			id[j++] = *p;
			p++;
			if(*p == '+' || *p == '-')
			{
				id[j++] = *p;
				p++;
				if(*p < '0' || *p > '9')
				{
					token = -1;
					return;
				}
				getdigit(j);
			}
			else getdigit(j);
			if(*p >= 'a' && *p <= 'z' || *p >= 'A' && *p <= 'Z')
			{
				token = -1;
				return;
			}
		}
			

		if(*p >= 'a' && *p <= 'z' || *p >= 'A' && *p <= 'Z')
		{
			while(*p >= 'a' && *p <= 'z' || *p >= 'A'  && *p <= 'Z' || *p >= '0' && *p <= '9')
			{
				p++;
			}
			token = -1;
		}
		return;
	}

	ch = *p;
//	printf("%c\n", ch);
//	exit(-1);
	p++;
	switch(ch)
	{
		case '+': strcpy(id, "+"); token=13; break;
		case '-': strcpy(id, "-"); token=14; break;
		case '*': strcpy(id, "*"); token=15; break;
		case '/': strcpy(id, "/"); token=16; break;
		case ':': if(*p == '=') { strcpy(id, ":="); token=18; p++; break; }
					else { strcpy(id, ":"); token = 17; break; }
		case '<': if(*p == '=') { strcpy(id, "<="); token = 22; p++; break; }
					else if(*p == '>') { strcpy(id, "<>"); token=21; p++; break; }
					else { strcpy(id, "<"); token = 20; break; }
		case '>': if(*p == '=') { strcpy(id, ">="); token = 24; p++; break; }
					else { strcpy(id, ">"); token = 23; break; }
		case '=': strcpy(id, "="); token = 25; break;
		case ';': strcpy(id, ";"); token = 26; break;
		case '(': strcpy(id, "("); token = 27; break;
		case ')': strcpy(id, ")"); token = 28; break;
		case '#': strcpy(id, "#"); token = 0; break;
		default: token = -1;
	}
}


void getdigit(int j)
{
	while(*p >= '0' && *p <= '9')
	{
		id[j++] = *p;
		p++;
	}
}
