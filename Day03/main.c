#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "stack.h"
#include "queue.h"
#include "stack_ll.h"
#include "queue_ll.h"
#include "linked_list_outer.h"
#include "priority_queue.h"

void stack_func();
void queue_func();
void stack_n_func();
void queue_n_func();
void stack_ll_func();
void queue_ll_func();
void queue_ll_n_func();
void stack_ll_n_func();
void heap_func();

int main() {
    int chx, flg=1;

    while(flg) {
        printf("\n1. Stack (Array)\n");
        printf("2. Queue (Array)\n");
        printf("3. N Stacks (Array)\n");
        printf("4. N Queues (Array)\n");
        printf("5. N Stacks (Linked List)\n");
        printf("6. N Queues (Linked List)\n");
        printf("7. Priority Queue (Linked List)\n");
        printf("0. Exit\n");

        printf("\nEnter Choice: ");
        scanf("%d", &chx);

        switch (chx) {
            case 0:
                flg = 0;
                break;
            case 1:
                stack_func();
                break;
            case 2:
                queue_func();
                break;
            case 3:
                stack_n_func();
                break;
            case 4:
                queue_n_func();
                break;
            case 5:
                stack_ll_n_func();
                break;
            case 6:
                queue_ll_n_func();
                break;
            case 7:
                heap_func();
                break;
            default:
                printf("Invalid Input");
                break;
        }
    }

    return 0;
}

void stack_func() {
    int n, x, val, full_flg=0, empty_flg=0, flg=1;
    printf("Stack (Array)\n");
    printf("Enter max size: ");
    scanf("%d", &n);

    stack stack1;
    stack1.size = n;
    stack1.arr = malloc(n*sizeof(int));
    if (stack1.arr == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    stack1.top = -1;

    while(flg) {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("0. Back\n");
        printf("\nEnter Choice: ");
        scanf("%d", &x);

        switch(x) {
            case 0:
                flg = 0;
                break;
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                push(&stack1, val, &full_flg);
                break;
            case 2:
                val = pop(&stack1, &empty_flg);
                if (!empty_flg) {
                    printf("%d\n", val); 
                }
                break;
            default:
                printf("Invalid Input.\n");
        }
    }
    free_stack(&stack1);
}

void queue_func() {
    int n, x, val, full_flg=0, empty_flg=0, flg=1;
    printf("Queue (Array)\n");
    printf("Enter max size: ");
    scanf("%d", &n);

    queue queue1;
    queue1.size = n;
    queue1.arr = malloc(n*sizeof(int));
    if (queue1.arr == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    queue1.head = queue1.size;

    while(flg) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("0. Back\n");
        printf("\nEnter Choice: ");
        scanf("%d", &x);

        switch(x) {
            case 0:
                flg = 0;
                break;
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                enqueue(&queue1, val, &full_flg);
                break;
            case 2:
                val = dequeue(&queue1, &empty_flg);
                if (!empty_flg) {
                    printf("%d\n", val); 
                }
                break;
            default:
                printf("Invalid Input.\n");
        }
    }
    free_queue(&queue1);
}

void stack_n_func() {
    int n, N, x, val, j, a, b, full_flg=0, empty_flg=0, flg=1;
    stack *stack_arr = NULL;
    printf("N Stacks (Array)\n");
    printf("Enter no. of stacks: ");
    scanf("%d", &N);

    // create array
    stack_arr = malloc(N*sizeof(stack));
    if (stack_arr == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    for (int i=0; i<N; i++) {
        printf("Enter max size of %dth stack: ", i+1);
        scanf("%d", &n);

        stack_arr[i].size = n;
        stack_arr[i].arr = malloc(n*sizeof(int));
        if (stack_arr[i].arr == NULL) {
            printf("MEMORY ALLOCATION ERROR.\n");
            exit(-1);
        }
        stack_arr[i].top = -1;
    }

    while(flg) {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("3. Compare\n");
        printf("0. Back\n");
        printf("\nEnter Choice: ");
        scanf("%d", &x);

        switch(x) {
            case 0:
                flg = 0;
                break;
            case 1:
                printf("Enter stack no: ");
                scanf("%d", &j);
                if (j >= N || j < 0) {
                    printf("Stack does not exist. Can be maximum %d.\n and minimum 0", N);
                    break;
                }
                printf("Enter value: ");
                scanf("%d", &val);
                push(&stack_arr[j], val, &full_flg);
                break;
            case 2:
                printf("Enter stack no: ");
                scanf("%d", &j);
                if (j >= N || j < 0) {
                    printf("Stack does not exist. Can be maximum %d. and minimum 0\n", N);
                    break;
                }
                val = pop(&stack_arr[j], &empty_flg);
                if (!empty_flg) {
                    printf("%d\n", val); 
                }
                break;
            case 3:
                printf("Enter stack no. 1: ");
                scanf("%d", &a);
                printf("Enter stack no. 2: ");
                scanf("%d", &b);
                if (a >= N || b >= N || a < 0 || b < 0) {
                    printf("Stack does not exist. Can be maximum %d. and minimum 0\n", N);
                    break;
                }

                if (compare_stacks(&stack_arr[a], &stack_arr[b])) {
                    printf("EQUALS.\n");
                } else {
                    printf("NOT EQUALS.\n");
                }

            default:
                printf("Invalid Input.\n");
        }
    }

    // freeing up memory
    for (int i=0; i<N; i++) {
        free_stack(&stack_arr[i]);
    }
    free(stack_arr);
}


void queue_n_func() {
    int n, N, x, val, j, a, b, full_flg=0, empty_flg=0, flg=1;
    queue *queue_arr = NULL;
    printf("N Queues (Array)\n");
    printf("Enter no. of queues: ");
    scanf("%d", &N);

    // create array
    queue_arr = malloc(N*sizeof(queue));
    if (queue_arr == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    for (int i=0; i<N; i++) {
        printf("Enter max size of %dth queue: ", i+1);
        scanf("%d", &n);

        queue_arr[i].size = n;
        queue_arr[i].arr = malloc(n*sizeof(int));
        if (queue_arr[i].arr == NULL) {
            printf("MEMORY ALLOCATION ERROR.\n");
            exit(-1);
        }
        queue_arr[i].head = queue_arr[i].size;
    }

    while(flg) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Compare\n");
        printf("0. Back\n");
        printf("\nEnter Choice: ");
        scanf("%d", &x);

        switch(x) {
            case 0:
                flg = 0;
                break;
            case 1:
                printf("Enter queue no: ");
                scanf("%d", &j);
                if (j >= N || j < 0) {
                    printf("Queue does not exist. Can be maximum %d.\n and minimum 0", N);
                    break;
                }
                printf("Enter value: ");
                scanf("%d", &val);
                enqueue(&queue_arr[j], val, &full_flg);
                break;
            case 2:
                printf("Enter queue no: ");
                scanf("%d", &j);
                if (j >= N || j < 0) {
                    printf("Queue does not exist. Can be maximum %d. and minimum 0\n", N);
                    break;
                }
                val = dequeue(&queue_arr[j], &empty_flg);
                if (!empty_flg) {
                    printf("%d\n", val); 
                }
                break;
            case 3:
                printf("Enter queue no. 1: ");
                scanf("%d", &a);
                printf("Enter queue no. 2: ");
                scanf("%d", &b);
                if (a >= N || b >= N || a < 0 || b < 0) {
                    printf("Queue does not exist. Can be maximum %d. and minimum 0\n", N);
                    break;
                }

                if (compare_queues(&queue_arr[a], &queue_arr[b])) {
                    printf("EQUALS.\n");
                } else {
                    printf("NOT EQUALS.\n");
                }
                break;
            default:
                printf("Invalid Input.\n");
        }
    }

    // freeing up memory
    for (int i=0; i<N; i++) {
        free_queue(&queue_arr[i]);
    }
    free(queue_arr);
}

void stack_ll_func() {
    int n, x, val, full_flg=0, empty_flg=0, flg=1;
    printf("Stack (LL)\n");
    printf("Enter max size: ");
    scanf("%d", &n);

    stack_ll stack1;
    stack1.size = n;
    stack1.tail = NULL;
    stack1.curr_size = 0;

    while(flg) {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        printf("0. Back\n");
        printf("Enter Choice: ");
        scanf("%d", &x);

        switch(x) {
            case 0:
                flg = 0;
                break;
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                push_ll(&stack1, val, &full_flg);
                break;
            case 2:
                val = pop_ll(&stack1, &empty_flg);
                if (!empty_flg) {
                    printf("%d\n", val); 
                }
                break;
            default:
                printf("Invalid Input.\n");
        }
    }

    free_list_backward(stack1.tail);
}

void queue_ll_func() {
    int n, x, val, full_flg=0, empty_flg=0, flg=1;
    printf("Queue (LL)\n");
    printf("Enter max size: ");
    scanf("%d", &n);

    queue_ll queue1;
    queue1.size = n;
    queue1.head = NULL;
    queue1.tail = NULL;
    queue1.curr_size = 0;

    while(flg) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("0. Back\n");
        printf("Enter Choice: ");
        scanf("%d", &x);

        switch(x) {
            case 0:
                flg = 0;
                break;
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                enqueue_ll(&queue1, val, &full_flg);
                break;
            case 2:
                val = dequeue_ll(&queue1, &empty_flg);
                if (!empty_flg) {
                    printf("%d\n", val); 
                }
                break;
            default:
                printf("Invalid Input.\n");
        }
    }

    free_list(queue1.head);
}


void queue_ll_n_func() {
    int n, N, x, val, j, a, b, full_flg=0, empty_flg=0, flg=1;
    node_ll *head=NULL, *ptr=NULL, *tmp=NULL;
    printf("N Queues (LL)\n");
    printf("Enter no. of queues: ");
    scanf("%d", &N);

    // create outer list. 
    if (N <= 0) {
        printf("Invalid Input.\n");
        return;
    }

    head = create_node_ll();
    ptr = head;
    for (int i=1; i<N; i++) {
        ptr->next = create_node_ll();
        ptr = ptr->next;
    }


    ptr = head;
    for (int i=0; i<N; i++) {
        printf("Enter max size of %dth queue: ", i);
        scanf("%d", &n);
        printf("Size scanned at %d is %d\n", i, n);

        ptr->data.queue_var.size = n;
        ptr->data.queue_var.head = NULL;
        ptr->data.queue_var.tail = NULL;
        ptr->data.queue_var.curr_size = 0;

        ptr = ptr->next; 
    }

    while(flg) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        // printf("3. Compare\n");
        printf("0. Back\n");
        printf("\nEnter Choice: ");
        scanf("%d", &x);

        switch(x) {
            case 0:
                flg = 0;
                break;
            case 1:
                printf("Enter queue no: ");
                scanf("%d", &j);
                if (j >= N || j < 0) {
                    printf("Queue does not exist. Can be maximum %d.\n and minimum 0", N);
                    break;
                }
                printf("Enter value: ");
                scanf("%d", &val);
                ptr = head;

                for (int i=1; i<=j; i++) {
                    ptr = ptr->next;
                }
                enqueue_ll(&ptr->data.queue_var, val, &full_flg);
                break;
            case 2:
                printf("Enter queue no: ");
                scanf("%d", &j);
                if (j >= N || j < 0) {
                    printf("Queue does not exist. Can be maximum %d. and minimum 0\n", N);
                    break;
                }

                ptr = head;

                for (int i=1; i<=j; i++) {
                    ptr = ptr->next;
                }

                val = dequeue_ll(&ptr->data.queue_var, &empty_flg);
                if (!empty_flg) {
                    printf("%d\n", val); 
                }
                break;
            default:
                printf("Invalid Input.\n");
        }
    }

    // freeing up memory
    ptr = head;
    while(ptr != NULL) {
        free_list(ptr->data.queue_var.head);
        ptr = ptr->next;
    }
    ptr = head;
    tmp =NULL;
    while(ptr) {
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
    
}


void stack_ll_n_func() {
    int n, N, x, val, j, a, b, full_flg=0, empty_flg=0, flg=1;
    node_ll *head=NULL, *ptr=NULL, *tmp=NULL;
    printf("N Stacks (LL)\n");
    printf("Enter no. of stacks: ");
    scanf("%d", &N);

    // create outer list. 
    if (N <= 0) {
        printf("Invalid Input.\n");
        return;
    }

    head = create_node_ll();
    ptr = head;
    for (int i=1; i<N; i++) {
        ptr->next = create_node_ll();
        ptr = ptr->next;
    }


    ptr = head;
    for (int i=0; i<N; i++) {
        printf("Enter max size of %dth stack: ", i);
        scanf("%d", &n);

        ptr->data.stack_var.size = n;
        ptr->data.stack_var.tail = NULL;
        ptr->data.stack_var.curr_size = 0;

        ptr = ptr->next; 
    }

    while(flg) {
        printf("\n1. Push\n");
        printf("2. Pop\n");
        // printf("3. Compare\n");
        printf("0. Back\n");
        printf("\nEnter Choice: ");
        scanf("%d", &x);

        switch(x) {
            case 0:
                flg = 0;
                break;
            case 1:
                printf("Enter stack no: ");
                scanf("%d", &j);
                if (j >= N || j < 0) {
                    printf("Stack does not exist. Can be maximum %d.\n and minimum 0", N);
                    break;
                }
                printf("Enter value: ");
                scanf("%d", &val);
                ptr = head;

                for (int i=1; i<=j; i++) {
                    ptr = ptr->next;
                }
                push_ll(&ptr->data.stack_var, val, &full_flg);
                break;
            case 2:
                printf("Enter queue no: ");
                scanf("%d", &j);
                if (j >= N || j < 0) {
                    printf("Queue does not exist. Can be maximum %d. and minimum 0\n", N);
                    break;
                }

                ptr = head;

                for (int i=1; i<=j; i++) {
                    ptr = ptr->next;
                }

                val = pop_ll(&ptr->data.stack_var, &empty_flg);
                if (!empty_flg) {
                    printf("%d\n", val); 
                }
                break;
            default:
                printf("Invalid Input.\n");
        }
    }

    // freeing up memory
    ptr = head;
    while(ptr != NULL) {
        free_list_backward(ptr->data.stack_var.tail);
        ptr = ptr->next;
    }
    ptr = head;
    tmp =NULL;
    while(ptr) {
        tmp = ptr;
        ptr = ptr->next;
        free(tmp);
    }
}

void heap_func() {
    int n, x, val, full_flg=0, empty_flg=0, flg=1;
    printf("Max Priority Queue (LL)\n");
    printf("Enter max size: ");
    scanf("%d", &n);

    priority_q pq;
    pq.size = n;
    pq.curr_size = 0;
    pq.head = NULL;

    while(flg) {
        printf("\n1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("0. Back\n");
        printf("\nEnter Choice: ");
        scanf("%d", &x);

        switch(x) {
            case 0:
                flg = 0;
                break;
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                enqueue_heap(&pq, val, &full_flg);
                break;
            case 2:
                val = dequeue_heap(&pq, &empty_flg);
                if (!empty_flg) {
                    printf("%d\n", val); 
                }
                break;
            default:
                printf("Invalid Input.\n");
        }
    }
    free_list(pq.head);
}