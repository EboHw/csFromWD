#include <stdio.h>
#include <stdlib.h>
#include "Stack.h"

Stack* stack_creat(void) {
	return calloc(1, sizeof(Stack));
}

void stack_destroy(Stack* stack) {
	// release the node first
	Node* curr = stack->top;
	while (curr) {
		Node* next = curr->next;
		free(curr);
		curr = next;
	} // curr == NULL

	// second release the stack struct
	free(stack);
}
// use recursion to release the stack
//void stack_destroy(Stack* stack) {
//
//	if (stack == NULL) return;
//
//	if (stack->size == 0) {
//		free(stack);
//		return;
//	}
//		
//	Node* curr = stack->top;
//	stack->top = stack->top->next;
//	free(curr);
//	stack->size--;
//
//	stack_destroy(stack);
//}

void stack_push(Stack* stack, E val) {
	// head insert
	// 1. creat and init a node
	Node* new_node = malloc(sizeof(Node));
	if (!new_node) {
		printf("Error: malloc failed!\n");
		exit(1);
	}
	new_node->data = val;
	new_node->next = stack->top;

	// 2. modify the struct stack
	stack->top = new_node;
	stack->size++;
}

E stack_pop(Stack* stack) {
	if (stack_empty(stack)) {
		printf("Error: stack is empty!\n");
		exit(1);
	}

	Node* remove_node = stack->top;
	E retval = remove_node->data;

	stack->top = remove_node->next;
	stack->size--;
	free(remove_node);

	return retval;

}

E stack_peek(const Stack* stack) {
	if (stack_empty(stack)) {
		printf("Error: stack is empty!\n");
		exit(1);
	}

	return stack->top->data;
}

bool stack_empty(const Stack* stack) {
	return stack->size == 0;
}