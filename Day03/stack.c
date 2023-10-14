#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int push(stack *stack_var, int val, int *full_flg) {
    if (stack_var->top == (stack_var->size) - 1) {
        printf("Stack Overflow Detected.\n");
        *full_flg = 1;
        return 0;
    }
    (stack_var->top)++;
    (stack_var->arr)[stack_var->top] = val;
    *full_flg = 0;

    return stack_var->top;
}

int pop(stack *stack_var, int *empty_flg) {
    int val;
    if (stack_var->top == -1) {
        printf("Stack is Empty\n");\
        *empty_flg = 1;
        return 0;
    }

    val = (stack_var->arr)[stack_var->top];
    (stack_var->top)--;
    *empty_flg = 0;

    return val;
}

int compare_stacks(stack *stack1, stack *stack2) {
    if ((stack1->top != stack2->top)) {
        return 0; // not equal because not same no. of elements
    }

    int eqs = 1; // bool
    // else compare element wise
    for (int i=0; i<=stack1->top; i++) {
        if ((stack1->arr)[i] != (stack2->arr)[i]) {
            eqs = 0;
            break;
        }
    }
    return eqs;
}

void free_stack(stack *stack_var) {
    free(stack_var->arr);
}