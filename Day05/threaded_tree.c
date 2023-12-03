#include <stdio.h>
#include <stdlib.h>
#include "util.h"

struct threaded_node {
    int val;
    struct threaded_node *left;
    struct threaded_node *right;
    bool is_threaded;
};
typedef struct threaded_node threaded_node;

enum node_type {
    root = 0,
    left = 1,
    right = 2
};
typedef enum node_type node_type;

threaded_node *create_threaded_node(int val);
threaded_node *create_threaded_tree(threaded_node *parent_node, node_type curr_node_type, bool *incoming_thread_flg);
threaded_node *get_leftmost_node(threaded_node *curr_node);
void threaded_inorder(threaded_node *root);

int main() {
    threaded_node *tree_root = NULL;
    bool flg = false;

    tree_root = create_threaded_tree(NULL, root, &flg);
    threaded_inorder(tree_root);
    return 0;
}

threaded_node *create_threaded_node(int val) {
    threaded_node *tmp = malloc(sizeof(threaded_node));
    if (tmp == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    tmp->val = val;
    tmp->left = NULL;
    tmp->right = NULL;
    tmp->is_threaded = false;
    return tmp;
}


threaded_node *create_threaded_tree(threaded_node *parent_node, node_type curr_node_type, bool *incoming_thread_flg) {
    int val, y, x;
    threaded_node *tmp = NULL;

    printf("Enter value: ");
    x = scanf("%d", &val);

    if (x == 0) {
        do {
            y = getchar();
        } while(y != '\n');
        return NULL;
    }

    tmp = create_threaded_node(val);

    printf("LEFT subtree of %d\n", val);
    tmp->left = create_threaded_tree(tmp, left, incoming_thread_flg);
    if (*incoming_thread_flg) {
        *incoming_thread_flg = false;
        tmp->left->right = parent_node;
    }

    printf("RIGHT subtree of %d\n", val);
    tmp->right = create_threaded_tree(tmp, right, incoming_thread_flg);
    if (*incoming_thread_flg) {
        *incoming_thread_flg = false;
        if (curr_node_type == left) {
            tmp->right->right = parent_node;
        }
    }

    if (tmp->right == NULL) {
        if (curr_node_type == left) { // if curr_node is left child
            tmp->is_threaded = true;
            tmp->right = parent_node;
        } else if (curr_node_type == right) {
            *incoming_thread_flg = true;
            tmp->is_threaded = true;
            return tmp;
        }
    }

    // if (*incoming_thread_flg) {
    //     *incoming_thread_flg = false;
    //     tmp->right->right = parent_node;
    // }

    return tmp;
}

threaded_node *get_leftmost_node(threaded_node *curr_node) {
    if (curr_node == NULL) {
        return NULL;
    }

    while (curr_node->left != NULL) {
        curr_node = curr_node->left;
    }

    return curr_node;
}

void threaded_inorder(threaded_node *root) {
    threaded_node *curr_node = get_leftmost_node(root);

    while(curr_node != NULL) {
        printf("%d, ", curr_node->val);

        if (curr_node->is_threaded) {
            curr_node = curr_node->right;
        }
        else {
            curr_node = get_leftmost_node(curr_node->right);
        }
    }
}