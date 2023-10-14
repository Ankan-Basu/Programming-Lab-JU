#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int enqueue(queue *queue_var, int val, int *full_flg) {
    if (queue_var->head == 0) {
        printf("Queue Overflow Detected.\n");
        *full_flg = 1;
        return 0;
    } 
    // shift elements by 1 step, to create empty space at end and insert there.
    for (int i=queue_var->head; i<queue_var->size; i++) {
        (queue_var->arr)[i-1] = (queue_var->arr)[i];
    }
    (queue_var->head)--;
    (queue_var->arr)[(queue_var->size) - 1] = val;
    *full_flg = 0;

    return queue_var->head;
}

int dequeue(queue *queue_var, int *empty_flg) {
    int val;

    if (queue_var->head == queue_var->size) {
        printf("Queue is empty.\n");
        *empty_flg = 1; // bool to detect empty condition
        return 0;
    }

    val = (queue_var->arr)[queue_var->head];
    (queue_var->head)++;
    *empty_flg = 0;

    return val;
}

int compare_queues(queue *queue1, queue *queue2) {
    if ((queue1->size - queue1->head != queue2->size - queue2->head)) {
        return 0; // not equal because not same no. of elements
    }

    int eqs = 1; // bool
    // else compare element wise
    for (int i=0; i<=(queue1->size - queue1->head); i++) {
        if ((queue1->arr)[(queue1->head) + i] != (queue2->arr)[(queue2->head) + i]) {
            eqs = 0;
            break;
        }
    }
    return eqs;
}

void free_queue(queue *queue_var) {
    free(queue_var->arr);
}