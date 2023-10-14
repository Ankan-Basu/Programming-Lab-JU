//  FOR TESTING

#include <stdio.h>
#include "priority_queue.h"
#include "linked_list.h"

int main() {
    node *head=NULL, *tail=NULL, *ptr=NULL;
    // int arr[] = {16, 4, 10, 14, 7, 9, 3, 2, 8, 1};
    int arr[] = {4, 1, 3, 2, 16, 9, 10, 14, 8, 7};
    for (int i=0; i<10; i++) {
        tail = insert_after(tail, arr[i]); 
    }
    ptr = tail;
    while(ptr && ptr->prev) {
        ptr = ptr->prev;
    }
    head = ptr;
    print_list(head);
    print_list_back(tail);

    priority_q pq;
    pq.head = head;
    pq.curr_size = 10;
    pq.size = 10;

    build_max_heap(&pq);
    print_list(pq.head);

    printf("Size curr of heap: %d\n", (&pq)->curr_size);

    int flg = 1, n, empty_flg, full_flg, val;
    while(flg) {
        printf("1. Enqueue\n");
        printf("2. Deque\n: ");
        scanf("%d", &n);

        switch(n) {
            case 1:
                printf("Enter val: ");
                scanf("%d", &val);
                enqueue_heap(&pq, val, &full_flg);
                print_list(pq.head);
                break;
            case 2:
                val = dequeue_heap(&pq, &empty_flg);
                printf("%d\n", val);
                print_list(pq.head);
                tail = pq.head;
                while(tail && tail->next) tail = tail->next; 
                print_list_back(tail);
                break;
        }

    }
   
    return 0;
}