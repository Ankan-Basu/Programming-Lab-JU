#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "queue_ll.h"

void enqueue_ll(queue_ll *queue_var, int val, int *full_flg) {
    if (queue_var->size == queue_var->curr_size) {
        printf("Queue Overflow Detected.\n");
        *full_flg = 1;
        return;
    }

    queue_var->tail = insert_after(queue_var->tail, val);
    (queue_var->curr_size)++;

    if (queue_var->curr_size == 1) { // only 1 node present in list
        queue_var->head = queue_var->tail;
    }

    *full_flg = 0;
    
    return;
}

int dequeue_ll(queue_ll *queue_var, int *empty_flg) {
    if (queue_var->curr_size == 0) {
        printf("Queue is Empty.\n");
        *empty_flg = 1;
        return 0;
    }

    int val = queue_var->head->val;
    queue_var->head = delete_first_node(queue_var->head);
    (queue_var->curr_size)--;

    if (queue_var->curr_size == 0) { // list becomes empty
        queue_var->tail = NULL;
    }
    *empty_flg = 0;    

    return val;
}

// int compare_queues_ll(queue_ll *queue1, queue_ll *queue2) {
//     if (queue1->curr_size != queue2->curr_size) {
//         return 0;
//     }

//     // compare queue1->head to end with queue2->head
// }

// if ((queue1->size - queue1->head != queue2->size - queue2->head)) {
//         return 0; // not equal because not same no. of elements
//     }

//     int eqs = 1; // bool
//     // else compare element wise
//     for (int i=0; i<=(queue1->size - queue1->head); i++) {
//         if ((queue1->arr)[(queue1->head) + i] != (queue2->arr)[(queue2->head) + i]) {
//             eqs = 0;
//             break;
//         }
//     }
//     return eqs;