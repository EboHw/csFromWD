#pragma once
#include <stdbool.h>

typedef int E;

typedef struct node {
	E data;
	struct node* next;
} Node;

typedef struct {
	Node* top;
	int size;
} Stack;

// API
Stack* stack_creat(void);
void stack_destroy(Stack* stack);

void stack_push(Stack* stack, E val);
E stack_pop(Stack* stack);
E stack_peek(const Stack* stack);
bool stack_empty(const Stack* stack);