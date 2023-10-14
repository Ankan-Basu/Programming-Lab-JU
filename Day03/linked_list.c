#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"


node *create_node(int val) {
    node *tmp = malloc(sizeof(node));
    if (tmp == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    tmp->val = val;
    tmp->next = NULL;
    tmp->prev = NULL;
    return tmp;
}

node *insert_after(node *ptr, int val) {
    // Insert at end (PUSH). ie. here ptr is tail
    node *tmp = create_node(val);

    if (ptr == NULL) {
        // ie initially empty list
        ptr = tmp;
        return ptr;
    }

    tmp->next = ptr->next;
    ptr->next = tmp;
    tmp->prev = ptr;

    // if (tmp->next != NULL) tmp->next->prev = tmp;
    ptr = ptr->next; //ie tmp. the new tail

    return ptr; // new tail
}

node *insert_before(node *ptr, int val) {
    // insert at beginning (ENQUEUE). ie first node. ptr = head
    node *tmp = create_node(val);
    tmp->next = ptr;
    ptr = tmp;
    tmp->prev = NULL;
    if (tmp->next != NULL) tmp->next->prev = tmp;

    return ptr; // new head
}

node *delete_last_node(node *ptr) {
    // delete node from the end (POP). ie. here ptr is tail
    node *tmp = ptr;
    ptr = ptr->prev;
    if (ptr != NULL) ptr->next = NULL; // if ptr == NULL, we deletd the first node. so empty list
    free(tmp);

    return ptr;
}

node *delete_first_node(node *ptr) {
    // delete node from the beginning (DEQUEUE). ie. here ptr is head
    node *tmp = ptr;
    ptr = ptr->next;
    if (ptr != NULL) ptr->prev = NULL; // ptr == NULL means list had only 1 node. so ptr moved outside list
    free(tmp);

    return ptr;
}

node *swap_nodes(node *head, node *ptr1, node *ptr2) {
    node *ptr1_prev, *ptr1_nxt, *ptr2_prev, *ptr2_nxt, *new_head=NULL, *tmp;

    if (ptr2 == ptr1->next || ptr1 == ptr2->next) {
        if (ptr1 == ptr2->next) {
            tmp = ptr1;
            ptr1 = ptr2;
            ptr2 = tmp;
        }
        ptr1_prev = ptr1->prev;
        ptr2_nxt = ptr2->next;

        ptr1->next = ptr2_nxt;
        if (ptr2_nxt != NULL) {
            ptr2_nxt->prev = ptr1; 
        }
        ptr2->prev = ptr1_prev;
        if (ptr1_prev != NULL) {
            ptr1_prev->next = ptr2;
        } else {
            new_head = ptr2;
        }

        ptr2->next = ptr1;
        ptr1->prev = ptr2;
    } else {
        ptr1_prev = ptr1->prev;
        ptr1_nxt = ptr1->next;
        ptr2_prev = ptr2->prev;
        ptr2_nxt = ptr2->next;

        ptr2->prev = ptr1_prev;
        ptr2->next = ptr1_nxt;

        ptr1->prev = ptr2_prev;
        ptr1->next = ptr2_nxt;

        if (ptr1_prev != NULL) {
            ptr1_prev->next = ptr2;
        } else {
            new_head = ptr2;
        }

        if (ptr1_nxt != NULL) {
            ptr1_nxt->prev = ptr2;
        }

        if (ptr2_prev != NULL) {
            ptr2_prev->next = ptr1;
        } else {
            new_head = ptr1;
        }

        if (ptr2_nxt != NULL) {
            ptr2_nxt->prev = ptr1; 
        }
    }

    if (new_head != NULL) {
        head = new_head;
    }
    return head;
}

void print_list(node *head) {
    node *ptr = head;

    while(ptr != NULL) {
        printf("%d -> ", ptr->val);
        ptr = ptr->next;
    }
    printf("NULL.\n");
}

void print_list_back(node *tail) {
    node *ptr = tail;

    while(ptr != NULL) {
        printf("%d <- ", ptr->val);
        ptr = ptr->prev;
    }
    printf("NULL.\n");
}

int get_index(node *head, node *target) {
    node *ptr = head;
    int indx = 0;

    while (ptr != target) {
        ptr = ptr->next;
        indx++;
    }

    return indx;
}

node *get_ptr(node *head, int target_val) {
    node *ptr = head;

    while(ptr && ptr->val != target_val) {
        ptr = ptr->next;
    }

    return ptr;
}

node *get_ptr_from_indx(node *head, int indx) {
    node *ptr = head;
    if (ptr == NULL) {
        return NULL;
    }

    for (int count=0; count < indx; count++) {
        ptr = ptr->next;
    }

    return ptr;
}

node *free_list(node *head) {
    node *curr = head, *tmp = NULL;

    while(curr) {
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    return NULL;
}

node *free_list_backward(node *tail) {
    node *curr = tail, *tmp = NULL;

    while(curr) {
        tmp = curr;
        curr = curr->prev;
        free(tmp);
    }
    return NULL;
}