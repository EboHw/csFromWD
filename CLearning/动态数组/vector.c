#include "vector.h"
#include <stdlib.h>
#include <stdio.h>

#define DEFAULT_CAPACITY 8		// 初始的初始的元素的大小
#define MAX_PREALLOC 1024		// 增长的最大限制

typedef int E;

vector* vector_create(void)
{
	vector* v = malloc(sizeof(vector));
	if (!v)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}

	v->elements = malloc(DEFAULT_CAPACITY * sizeof(E));
	if (!v->elements)
	{
		free(v);
		printf("Error: malloc failed\n");
		exit(1);
	}

	v->size = 0;
	v->capacity = DEFAULT_CAPACITY;

	return v;

}

void vector_destroy(vector* v)
{
	free(v->elements);
	free(v);
}

void grow_capacity(vector* v)
{
	// 扩容策略
	int new_capacity = (v->capacity < MAX_PREALLOC) ?
		(v->capacity << 1) : (v->capacity + MAX_PREALLOC);

	E* p = realloc(v->elements, new_capacity * sizeof(E));
	if (!p)
	{
		printf("Error: realloc failed\n");
		exit(1);
	}

	v->elements = p;
	v->capacity = new_capacity;

}

void push_back(vector* v, E val)
{
	if (v->size == v->capacity)
	{
		grow_capacity(v);
	}

	v->elements[v->size] = val;
	v->size++;
}