#ifndef STRUCT_STACK
#define STRUCT_STACK

#include <stdio.h>
#include <stdlib.h>

#define MAX_LENGTH_OF_ELEMENT 32
#define OUT_OF_RANGE 0
#define SUCCESS 1 
#define DIGIT 1
#define ALPHA 0

typedef union 
{
	double digit;
	char alpha;
} Element;

typedef struct 
{	
	int top;
	int type;
	int max_size;
	Element element[MAX_LENGTH_OF_ELEMENT];
}Stack;

int push(Stack *stack, Element ele)
{
	if( stack->top == MAX_LENGTH_OF_ELEMENT )
		return OUT_OF_RANGE;
	
	if(stack->type == DIGIT)
		stack->element[stack->top++].digit = ele.digit;
	
	if(stack->type == ALPHA)
		stack->element[stack->top++].alpha = ele.alpha;
	
	return SUCCESS;
}

int pop(Stack *stack, Element *ele)
{
	if(stack->top == 0)
		return OUT_OF_RANGE;
	
	stack->top--;
	if(stack->type == DIGIT)
		ele->digit = stack->element[stack->top].digit;
	
	if(stack->type == ALPHA)
		ele->alpha = stack->element[stack->top].alpha;
	
	return SUCCESS;
}

int is_full(Stack *stack)
{
	if(stack->top == stack->max_size)
		return 1;
	return 0;
}

int init_stack(Stack *stack, int type)
{
//	stack = (Stack*)malloc(sizeof(Stack));
	stack->top = 0;
	stack->type = type;
	stack->max_size = MAX_LENGTH_OF_ELEMENT;
}

int pushd(Stack *stack, double num)
{
	Element ele;
	ele.digit = num;
	return push(stack, ele);
}

int pusha(Stack *stack, char ch)
{
	Element ele;
	ele.alpha = ch;
	return push(stack, ele);
}

int popd(Stack *stack, double *num)
{
	Element ele;
	int ret = pop(stack, &ele);
	*num = ele.digit;
	return ret;
}

int popa(Stack *stack, char *ch)
{
	Element ele;
	int ret = pop(stack, &ele);
	*ch = ele.alpha;
	return ret;
}

char topa(Stack *stack)
{
	Element ele;
	pop(stack, &ele);
	stack->top++;
	return ele.alpha;
}

double topd(Stack *stack)
{	
	Element ele;
	pop(stack, &ele);
	stack->top++;
	return ele.digit;
}

#endif
