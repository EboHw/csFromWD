#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef char* K;
typedef char* V;

typedef struct node {
	K key;
	V val;
	struct node* next;
} Node;

typedef struct {
	Node** elements;	// Pointer to dynamic array
	int capacity;
	int size;			// Number of key-value pairs
	uint32_t hashseed;
} HashMap;

// API
HashMap* hashmap_create(void);
void hashmap_destroy(HashMap* map);

V hashmap_put(HashMap* map, K key, V val);
void hashmap_delete(HashMap* map, K key);
V hashmap_get(HashMap* map, K key);