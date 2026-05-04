#pragma once
// BST.h  (Binary Search Tree)

#include <stdbool.h>

typedef int K;

typedef struct tree_node {
    K key;
    struct tree_node* left;
    struct tree_node* right;
} TreeNode;

typedef struct {
    TreeNode* root;
} BST;

// API
BST* bst_create(void);
void bst_destroy(BST* tree);

void bst_insert(BST* tree, K key);
bool bst_search(BST* tree, K key);
void bst_delete(BST* tree, K key);

// Traversing the tree
void bst_preorder(const BST* tree);
void bst_inorder(const BST* tree);
void bst_postorder(const BST* tree);
void bst_levelorder(const BST* tree);