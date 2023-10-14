#ifndef STACK_LL_H
#define STACK_LL_H

#include "linked_list.h"

struct stack_ll {
    node *tail;
    int size;
    int curr_size;
};
typedef struct stack_ll stack_ll;

void push_ll(stack_ll *stack_var, int val, int *full_flg);

int pop_ll(stack_ll *stack_var, int *empty_flg);

#endif