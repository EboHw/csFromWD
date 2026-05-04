#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
/*************************************************************
*						  COMMENT                            *
**************************************************************/

typedef struct {
	int data;
	struct Node* next;
} Node;

void add_node(Node** , int);

int main(void)
{
	Node* head = NULL;
	Node* n = head;

	add_node(&head, 3);
	add_node(&head, 2);
	add_node(&head, 1);

	return 0;
}

void add_node(Node** phead, int val)
{
	// 1. creat a node
	Node* node = malloc(sizeof(Node));
	if (!node)
	{
		printf("error malloc\n");
		exit(1);
	}

	// 2. init the node && add to linklist
	node->data = val;
	node->next = *phead;
	*phead = node;

}