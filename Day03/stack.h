#ifndef STACK_H 
#define STACK_H

struct stack{
    int *arr; // array to store the stack
    int size;
    int top;
};
typedef struct stack stack;

int push(stack *stack_var, int val, int *full_flg);
int pop(stack *stack_var, int *empty_flg);
int compare_stacks(stack *stack1, stack *stack2);
void free_stack(stack *stack_var);

#endif