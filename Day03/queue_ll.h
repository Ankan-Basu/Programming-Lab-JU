#ifndef QUEUE_LL_H
#define QUEUE_LL_H

#include "linked_list.h"

struct queue_ll {
    node *head;
    node *tail;
    int size;
    int curr_size;
};
typedef struct queue_ll queue_ll;

void enqueue_ll(queue_ll *queue_var, int val, int *full_flg);

int dequeue_ll(queue_ll *queue_var, int *empty_flg);

#endif