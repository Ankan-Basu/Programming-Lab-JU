#include <stdio.h>
#include <stdlib.h>
#include "stack_ll.h"

void push_ll(stack_ll *stack_var, int val, int *full_flg) {
    if (stack_var->size == stack_var->curr_size) {
        printf("Stack Overflow Detected.\n");
        *full_flg = 1;
        return;
    }

    stack_var->tail = insert_after(stack_var->tail, val);
    // stack_var->tail = stack_var->tail->next;
    (stack_var->curr_size)++;
    
    return;
}

int pop_ll(stack_ll *stack_var, int *empty_flg) {
    if (stack_var->curr_size == 0) {
        printf("Stack is Empty.\n");
        *empty_flg = 1;
        return 0;
    }

    int val = stack_var->tail->val;
    stack_var->tail = delete_last_node(stack_var->tail);
    (stack_var->curr_size)--;
    *empty_flg = 0;    

    return val;
}

void free_stack_ll() {

}