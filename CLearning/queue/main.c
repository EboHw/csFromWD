#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "queue.h"

/*************************************************************
*						  COMMENT                            *
**************************************************************/

int main(void)
{
	Queue* q = queue_create();

	for (int i = 1; i <= 100; i++) {
		queue_push(q, i);
	}

	while (!queue_empty(q)) {
		E val = queue_peek(q);
		printf("%d ", val);
		queue_pop(q);
	}
	printf("\n");

	return 0;
}