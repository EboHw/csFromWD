#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "vector.h"

/*************************************************************
*						  COMMENT                            *
**************************************************************/

/*
µ¥Ôª²âÊÔ
*/
int main(void)
{
	vector* v = vector_create();

	for (int i = 1; i <= 100; i++)
		push_back(v, i * 10);

	for (int i = 0; i < v->size; i++)
		printf("%d ", v->elements[i]);

	printf("\n");

	vector_destroy(v);
	return 0;
}