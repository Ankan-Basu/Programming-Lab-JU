#ifndef LINKED_LIST_OUTER_H
#define LINKED_LIST_OUTER_H

#include "queue_ll.h"
#include "stack_ll.h"

union data_union {
    queue_ll queue_var;
    stack_ll stack_var;
};
typedef union data_union data_union;

struct node_ll {
    data_union data;
    struct node_ll *next;
};
typedef struct node_ll node_ll;

node_ll *create_node_ll();

#endif