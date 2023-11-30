#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

node *create_node(int val) {
    node *n = malloc(sizeof(node));
    if (n == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    n->val = val;
    n->left = NULL;
    n->right = NULL;

    return n;
}

void preorder(node *head) {
    if (head == NULL) {
        return;
    }

    printf("%d, ", head->val);
    inorder(head->left);
    inorder(head->right);
}

void inorder(node *head) {
    if (head == NULL) {
        return;
    }

    inorder(head->left);
    printf("%d, ", head->val);
    inorder(head->right);
}

void postorder(node *head) {
    if (head == NULL) {
        return;
    }

    inorder(head->left);
    inorder(head->right);
    printf("%d, ", head->val);
}

node *dealloc_tree(node *head) {
    if (head == NULL) {
        return NULL;
    }
    dealloc_tree(head->left);
    dealloc_tree(head->right);
    free(head);

    return NULL;
}