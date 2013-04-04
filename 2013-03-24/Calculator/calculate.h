#ifndef CALCULATE
#define CALCULATE

#include "get_postfix_exp.h"
#include "stack.h"
#include <ctype.h>

double cal(double num1, double num2, char op);

double calculate(char *postfix_exp)
{
	int i = 0;
	Stack digit_stack;
	Stack *stack = &digit_stack;
	init_stack(stack, DIGIT);

	double num = 0;
	double num1, num2;

	while(postfix_exp[i] != '\0')
	{
		if(postfix_exp[i] == ' ')
		{
			i++;
			continue;
		}

		if(isdigit(postfix_exp[i]) )
		{
			while(isdigit(postfix_exp[i]) )
			{
				num = num * 10 + postfix_exp[i++] - '0';
			}
			pushd(stack, num);
			num = 0;
			continue;
		}

		popd(stack, &num2);
		popd(stack, &num1);

		pushd(stack, cal(num1, num2, postfix_exp[i]) );
		i++;
	}

	popd(stack, &num);
	return num;
}
		

double cal(double num1, double num2, char op)
{
	switch(op)
	{
		case '+': return num1+num2;
		case '-': return num1-num2;
		case '*': return num1*num2;
		case '/': return num1/num2;
	}
}

#endif
