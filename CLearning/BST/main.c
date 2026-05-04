#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "BST.h"

/*************************************************************
 *						  COMMENT                            *
 **************************************************************/

int main(void) {
    BST* tree = bst_create();

    /*bst_insert(tree, 9);
    bst_insert(tree, 5);
    bst_insert(tree, 42);
    bst_insert(tree, 57);
    bst_insert(tree, 13);
    bst_insert(tree, 3);*/

    bst_insert(tree, 4);
    bst_insert(tree, 3);
    bst_insert(tree, 2);
    bst_insert(tree, 1);
    bst_insert(tree, 0);

    bst_preorder(tree);
    bst_inorder(tree);
    bst_postorder(tree);

    //bst_delete(tree, 9);

    bst_levelorder(tree);


    return 0;
}