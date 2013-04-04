#include "stack.h"

int main()
{
	Stack stack;
	init_stack(&stack, DIGIT);
	pusha(&stack, 'A');
	if(!is_full(&stack))
	pusha(&stack, 100);

	int num;
	popa(&stack, &num);
	//popd(&stack, &num);
	printf("%c\n", num);
}
