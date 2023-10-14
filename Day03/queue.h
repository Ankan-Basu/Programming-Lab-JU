#ifndef QUEUE_H 
#define QUEUE_H

struct queue {
    int *arr; //array to store the queue
    int size;
    int head;
};
typedef struct queue queue;

int enqueue(queue *queue_var, int val, int *full_flg);
int dequeue(queue *queue_var, int *empty_flg);
int compare_queues(queue *queue1, queue *queue2);
void free_queue(queue *queue_var);

#endif