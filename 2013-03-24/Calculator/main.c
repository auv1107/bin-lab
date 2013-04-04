#include "get_postfix_exp.h"
#include "stack.h"
#include "calculate.h"

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char postfix_exp[MAX_LENGTH_OF_ELEMENT * 2];

	get_postfix_exp(postfix_exp);
	double result = calculate(postfix_exp);

//	printf("postfix_exp: %s\n", postfix_exp);
	printf("result = %.2lf\n", result);

	exit(0);
}
