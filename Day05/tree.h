#ifndef TREE_H
#define TREE_H

struct node {
    int val;
    struct node *left;
    struct node *right;
};
typedef struct node node;

node *create_node(int val);
void preorder(node *head);
void inorder(node *head);
void postorder(node *head);
node *dealloc_tree(node *head);

#endif