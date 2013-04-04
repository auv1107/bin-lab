#include "calculator.h"
#include "stack.h"
#include <stdio.h>

int main()
{
	char postfix_exp[MAX_LENGTH_OF_ELEMENT * 2];
	get_postfix_exp(postfix_exp);
	printf("%s\n", postfix_exp);

	return 0;
}
