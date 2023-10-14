#ifndef LINKED_LIST_H
#define LINKED_LIST_H


struct node {
    struct node *prev;
    int val;
    struct node *next;
};
typedef struct node node;

node *create_node(int val);

node *insert_after(node *ptr, int val);

node *insert_before(node *ptr, int val);

node *delete_first_node(node *ptr);

node *delete_last_node(node *ptr);

node *swap_nodes(node *head, node *ptr1, node *ptr2);

void print_list(node *head);

void print_list_back(node *tail);

int get_index(node *head, node *target);

node *get_ptr(node *head, int target_val);

node *get_ptr_from_indx(node *head, int indx);

node *free_list(node *head);
node *free_list_backward(node *tail);

#endif