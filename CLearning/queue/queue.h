#pragma once
#include <stdbool.h>

typedef int E;
typedef struct {
	E* elements;
	int size;
	int capacity;
	int front;
	int rear;	// Where to insert a new elements
} Queue;

// API
Queue* queue_create(void);
void queue_destroy(Queue* q);

void queue_push(Queue* q, E val);
E queue_pop(Queue* q);
E queue_peek(const Queue* q);
bool queue_empty(const Queue* q);
bool queue_full(const Queue* q);