#include "hashMap.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DEAFAULT_CAPACITY 8
#define LOAD_FACTOR 0.75  // Maximum average length of linked lists
#define MAX_PREALLOC 4096

HashMap* hashmap_create(void) {
    // Create hashmap
    HashMap* map  = malloc(sizeof(HashMap));
    map->elements = calloc(DEAFAULT_CAPACITY, sizeof(Node*));
    map->capacity = DEAFAULT_CAPACITY;
    map->size     = 0;
    map->hashseed = (uint32_t)time(NULL);

    return map;
}

void hashmap_destroy(HashMap* map) {
    // 1. Free all node first(Traverse the hashmap)
    for (int i = 0; i < map->capacity; i++) {
        Node* curr = map->elements[i];
        while (curr) {
            Node* next = curr->next;
            free(curr);
            curr = next;
        }
    }
    // 2. Free dynamic array
    free(map->elements);
    // 3. Free hashmap struct
    free(map);
}

/* murmurhash2 */
// 1. It can calculate the hash value of any type of key
// 2. The returned hash value is related to the seed,
// improve security
uint32_t hash(const void* key, int len, uint32_t seed) {
    const uint32_t m          = 0x5bd1e995;
    const int r               = 24;
    uint32_t h                = seed ^ len;
    const unsigned char* data = (const unsigned char*)key;

    while (len >= 4) {
        uint32_t k = *(uint32_t*)data;

        k *= m;
        k ^= k >> r;
        k *= m;

        h *= m;
        h ^= k;

        data += 4;
        len -= 4;
    }

    switch (len) {
        case 3:
            h ^= data[2] << 16;
        case 2:
            h ^= data[1] << 8;
        case 1:
            h ^= data[0];
            h *= m;
    };

    h ^= h >> 13;
    h *= m;
    h ^= h >> 15;

    return h;
}

void rehash(Node* node, Node** table, int length, uint32_t seed) {
    // Recalculate the idx(hash code)
    int idx = hash(node->key, strlen(node->key), seed) % length;
    // head insert
    node->next = table[idx];
    table[idx] = node;
}

void grow_capacity(HashMap* map) {
    int new_capacity = (map->capacity <= MAX_PREALLOC) ? (map->capacity << 1) : (map->capacity + MAX_PREALLOC);

    Node** new_table = calloc(new_capacity, sizeof(Node*));
    // rehash
    uint32_t seed = time(NULL);
    for (int i = 0; i < map->capacity; i++) {
        Node* curr = map->elements[i];
        while (curr) {
            Node* next = curr->next;
            rehash(curr, new_table, new_capacity, seed);
            curr = next;
        }
    }

    free(map->elements);
    map->elements = new_table;
    map->capacity = new_capacity;
    map->hashseed = seed;
}

/*
1. If the key exists,
   update the value and return the original value
2. If the key does not exist,
   add the key-value pair and return the special value(NULL)
*/
V hashmap_put(HashMap* map, K key, V val) {
    // 1. Calculate the key's hash value
    int idx = hash(key, strlen(key), map->hashseed) % map->capacity;

    // 2. Traverse the list, Check if the key exists
    Node* curr = map->elements[idx];
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            // Renew the val, return old val
            V oldval  = curr->val;
            curr->val = val;
            return oldval;
        }
        curr = curr->next;
    }

    // 3. Check if a rehash is necessary
    if (map->size >= map->capacity * LOAD_FACTOR) {
        grow_capacity(map);

        // Recalculate the idx
        idx = hash(key, strlen(key), map->hashseed) % map->capacity;
    }

    // 4. Create node, add to the linklist
    Node* new_node     = malloc(sizeof(Node));
    new_node->key      = key;
    new_node->val      = val;
    new_node->next     = map->elements[idx];
    map->elements[idx] = new_node;
    map->size++;

    return NULL;
}

void hashmap_delete(HashMap* map, K key) {
    int idx    = hash(key, strlen(key), map->hashseed) % map->capacity;
    Node* curr = map->elements[idx];
    Node* prev = NULL;
    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            if (prev) {
                prev->next = curr->next;
            } else {
                map->elements[idx] = curr->next;
            }
            free(curr);
            map->size--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

V hashmap_get(HashMap* map, K key) {
    int idx    = hash(key, strlen(key), map->hashseed) % map->capacity;
    Node* curr = map->elements[idx];

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            // Find the val;
            return curr->val;
        }
        curr = curr->next;
    }

    return NULL;
}