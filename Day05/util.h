#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>

enum bool {
    false = 0,
    true = 1
};
typedef enum bool bool;

int *input(int *size);
void print_array(int *arr, int size);

#endif