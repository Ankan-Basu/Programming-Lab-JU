#ifndef PRIORITY_Q_H
#define PRIORITY_Q_H

#include "linked_list.h"

struct priority_q {
    node *head;
    int size;
    int curr_size;
};
typedef struct priority_q priority_q;

enum child_type {
    LEFT = 0,
    RIGHT = 1
};
typedef enum child_type child_type;

node *get_child(priority_q *p_q, int i, child_type type);

node *get_parent(priority_q *p_q, int i);

void max_heapify(priority_q *p_q, int i);

void build_max_heap(priority_q *p_q);

int dequeue_heap(priority_q *p_q, int *empty_flg);

void heap_increase_key(priority_q *p_q, int i, int new_val);

void enqueue_heap(priority_q *p_q, int val, int *full_flg);

#endif