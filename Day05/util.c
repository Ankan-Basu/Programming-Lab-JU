#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int *input(int *size) {
    int *buffer = NULL;
    int tmp, x, y;
    bool flg = true;
    *size = 0;

    while (flg) {
        x = scanf("%d", &tmp);
        y = getchar();

        if (y == '\n') {
            flg = false;
        }
        if (x == 0) {
            // ignore non int 
            getchar();
            continue;
        }
        (*size)++;
        buffer = realloc(buffer, (*size)*sizeof(int));
        if (buffer == NULL) {
            printf("MEMORY ALLOCATION ERROR.\n");
            exit(-1);
        } 
        buffer[(*size)-1] = tmp;
    }

    return buffer;
}

void print_array(int *arr, int size) {
    for (int i=0; i<size; i++) {
        printf("%d,", arr[i]);
    }
    printf("\n");
}