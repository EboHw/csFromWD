#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "stack.h"

/*************************************************************
*						  COMMENT                            *
**************************************************************/

int main(void)
{
	Stack* stack = stack_creat();

	stack_push(stack, 1);
	stack_push(stack, 2);
	stack_push(stack, 3);
	stack_push(stack, 4);

	// traverse the stack
	while (!stack_empty(stack)) {
		E val = stack_peek(stack);
		printf("%d ", val);
		stack_pop(stack);
	}
	printf("\n");

	stack_destroy(stack);

	return 0;
}