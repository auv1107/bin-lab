#ifndef GET_POSTFIX_EXP
#define GET_POSTFIX_EXP

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include "stack.h"


int get_priority(char ch);

int get_postfix_exp(char *PostfixExp)
{
	char ch;
//	char PostfixExp[MAX_LENGTH_OF_ELEMENT * 2];
	int i = 0;
	int priority;
	Stack alpha_stack;
	Stack *stack = &alpha_stack;
	init_stack(stack, ALPHA);
	stack->top = 0;

	while((ch = getchar()) != '\n' && ch != '\0')
	{
		if(isdigit(ch))
		{
			PostfixExp[i++] = ch;
			continue;
		}

		if(ch == '(')
		{
			pusha(stack, ch);
			if(PostfixExp[i-1] != ' ' )
				PostfixExp[i++] = ' ';
			continue;
		}

		if(ch == ')')
		{
			if(stack->top == 0)
			{
				printf("括号不匹配\n");
				exit(-1);
			}

			{
				char ch;
				popa(stack, &ch);
				while(ch != '(')
				{
					if(stack->top == 0)
					{
						printf("括号不匹配\n");
						exit(-1);
					}
					PostfixExp[i++] = ' ';
					PostfixExp[i++] = ch;
					popa(stack, &ch);
				}
			}
			continue;
		}

		priority = get_priority(ch);
		if(priority == -2)
		{
			printf("无效字符: %c\n", ch);
			exit(-2);
		}

		while(stack->top != 0 && topa(stack) != '(' && priority <= get_priority(topa(stack)) )
		{
			char ch;
			popa(stack, &ch);
			PostfixExp[i++] = ' ';
			PostfixExp[i++] = ch;
		}

		pusha(stack, ch);
		if(PostfixExp[i-1] != ' ' )
			PostfixExp[i++] = ' ';

	}

	while(stack->top > 0)
	{
		popa(stack, &ch);
		PostfixExp[i++] = ' ';
		PostfixExp[i++] = ch;
	}

	PostfixExp[i] = '\0';

	return SUCCESS;
}

int get_priority(char ch)
{
	switch(ch)
	{
		case '+':
		case '-': return 1;
		case '*':
		case '/': return 2;
		default: return -2;
	}
}	

#endif
