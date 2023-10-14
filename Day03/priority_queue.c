#include <stdio.h>
#include "linked_list.h"
#include "priority_queue.h"

node *get_child(priority_q *p_q, int i, child_type type) {
    int child_indx;
    node *child_ptr = NULL;
    if (type == LEFT) {
        child_indx = (i + 1)*2 - 1;
    } else if (type == RIGHT) {
        child_indx = (i + 1)*2;
    }

    if (child_indx >= p_q->curr_size) {
        // out of bounds
        return NULL;
    }

    child_ptr = get_ptr_from_indx(p_q->head, child_indx);

    return child_ptr;
}

node *get_parent(priority_q *p_q, int i) {
    int parent_indx = (i-1)/2;

    if (i < 0) {
        // out of bounds
        return NULL;
    }

    node *parent_ptr = get_ptr_from_indx(p_q->head, parent_indx);

    return parent_ptr;
}

void max_heapify(priority_q *p_q, int i) {
    node *l=NULL, *r=NULL, *curr=NULL, *largest=NULL;
    int indx=0;

    l = get_child(p_q, i, LEFT);
    r = get_child(p_q, i, RIGHT);
    curr = get_ptr_from_indx(p_q->head, i);

    if (l != NULL && l->val > curr->val) {
        largest = l;
    } else {
        largest = curr;
    }

    if (r != NULL && r->val > largest->val) {
        largest = r;
    }

    if (largest != curr) {
        p_q->head = swap_nodes(p_q->head, curr, largest);
        indx = get_index(p_q->head, curr);
        max_heapify(p_q, indx);
    }
}

void build_max_heap(priority_q *p_q) {
    for (int i=((p_q->curr_size - 1)/2); i>=0; i--) {
        max_heapify(p_q, i);
    }
}

int dequeue_heap(priority_q *p_q, int *empty_flg) {
    if (p_q->curr_size == 0) {
        printf("Heap Underflow Detected.\n");
        *empty_flg = 1;
        return 0;
    }

    int max = p_q->head->val;

    if (p_q->curr_size == 1) {
        p_q->head = delete_first_node(p_q->head);
        (p_q->curr_size)--;
    } else {
        node *tmp = p_q->head;
        node *last = get_ptr_from_indx(p_q->head, (p_q->curr_size) - 1);
        p_q->head = swap_nodes(p_q->head, p_q->head, last);
        delete_last_node(tmp);
        (p_q->curr_size)--;
        max_heapify(p_q, 0);
        *empty_flg = 0;
    }

    return max;
}

void heap_increase_key(priority_q *p_q, int i, int new_val) {
    node *curr_ptr = get_ptr_from_indx(p_q->head, i);
    node *parent_ptr = get_parent(p_q, i);
    int curr_indx, parent_indx;
    curr_ptr->val = new_val;


    while (i > 0 && parent_ptr->val < curr_ptr->val) {
        p_q->head = swap_nodes(p_q->head, curr_ptr, parent_ptr);

        // curr_ptr and parent_ptr still points to the old nodes, but the links got changed
        // new parent of curr_ptr after swapping 
        parent_ptr = get_parent(p_q, get_index(p_q->head, curr_ptr));
    }
}

void enqueue_heap(priority_q *p_q, int val, int *full_flg) {
    if (p_q->curr_size == p_q->size) {
        printf("Heap Overlow Detected.\n");
        *full_flg = 1;
        return;
    }

    if (p_q->curr_size == 0) {
        p_q->head = insert_before(p_q->head /*NULL*/, val);
        (p_q->curr_size)++;
        return;
    }
    node *tail = get_ptr_from_indx(p_q->head, (p_q->curr_size) - 1);
    (p_q->curr_size)++;

    int MIN = -1e9;
    insert_after(tail, MIN);

    heap_increase_key(p_q, (p_q->curr_size) - 1, val);
}