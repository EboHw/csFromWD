#include "BST.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "queue.h"

BST* bst_create(void) { return calloc(1, sizeof(BST)); }

void bst_destroy(BST* tree) {}

void bst_insert(BST* tree, K key) {
    TreeNode* parent = NULL;
    TreeNode* curr   = tree->root;
    int cmp          = 0;
    while (curr) {
        cmp = key - curr->key;
        if (cmp < 0) {
            parent = curr;
            curr   = curr->left;
        } else if (cmp > 0) {
            parent = curr;
            curr   = curr->right;
        } else {
            return;
        }
    }  // curr == NULL
    TreeNode* new_node = calloc(1, sizeof(TreeNode));
    new_node->key      = key;

    if (!parent) {
        tree->root = new_node;
    } else if (cmp < 0) {
        parent->left = new_node;
    } else {
        parent->right = new_node;
    }
}

bool bst_search(BST* tree, K key) {
    TreeNode* curr = tree->root;
    int cmp        = 0;
    while (curr) {
        cmp = key - curr->key;
        if (cmp < 0) {
            curr = curr->left;
        } else if (cmp > 0) {
            curr = curr->right;
        } else {
            return true;
        }
    }
    return false;
}

void bst_delete(BST* tree, K key) {
    TreeNode* parent = NULL;
    TreeNode* curr   = tree->root;

    while (curr) {
        int cmp = key - curr->key;
        if (cmp < 0) {
            parent = curr;
            curr   = curr->left;
        } else if (cmp > 0) {
            parent = curr;
            curr   = curr->right;
        } else {
            break;
        }
    }  // curr == NULL || curr != NULL

    if (!curr) { return; }

    if (curr->left && curr->right) {
        // The degree of the delete node is 2
        TreeNode* parentOfMin = curr;
        TreeNode* minOfRight  = curr->right;

        while (minOfRight->left) {
            parentOfMin = minOfRight;
            minOfRight  = minOfRight->left;
        }

        curr->key = minOfRight->key;
        parent    = parentOfMin;
        curr      = minOfRight;
    }

    TreeNode* child = curr->left ? curr->left : curr->right;
    if (!parent) {
        tree->root = child;
    } else {
        int cmp = curr->key - parent->key;
        if (cmp < 0) {
            parent->left = child;
        } else if (cmp > 0) {
            parent->right = child;
        } else {
            // cmp == 0 (degree == 2 and minOfRight == rootOfRight)
            parent->right = child;
        }
    }

    free(curr);
}

/*
 * DFS
 */

/***************************************************************
 *                       pre first traversing                   *
 ****************************************************************/
void preorder(const TreeNode* root) {
    if (root == NULL) { return; }
    printf("%d ", root->key);
    preorder(root->left);
    preorder(root->right);
}

void bst_preorder(const BST* tree) {
    preorder(tree->root);
    printf("\n");
}

/***************************************************************
 *                       mid first traversing                   *
 ****************************************************************/

void inorder(const TreeNode* root) {
    if (root == NULL) { return; }
    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

void bst_inorder(const BST* tree) {
    inorder(tree->root);
    printf("\n");
}

/***************************************************************
 *                     post first traversing                    *
 ****************************************************************/
void postorder(const TreeNode* root) {
    if (root == NULL) { return; }
    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->key);
}

void bst_postorder(const BST* tree) {
    postorder(tree->root);
    printf("\n");
}

/*
 * BFS
 */
void bst_levelorder(const BST* tree) {
    Queue* q = queue_create();
    queue_push(q, tree->root);

    while (!queue_empty(q)) {
        int level_size = q->size;

        for (int i = 0; i < level_size; i++) {
            TreeNode* node = queue_pop(q);
            printf("%d ", node->key);
            if (node->left) { queue_push(q, node->left); }
            if (node->right) { queue_push(q, node->right); }
        }
        printf("\n");
    }
    printf("\n");
}