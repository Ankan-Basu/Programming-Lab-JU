#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int partition(int arr[][2], int begin, int end) {
    int pivot = arr[end][1];
    int i = begin - 1;

    for (int j=begin; j<end; j++) {
        if (arr[j][1] < pivot) {
            i++;
            swap(&arr[j][1], &arr[i][1]);
        }
    }
    swap(&arr[i+1][1], &arr[end][1]);

    return i+1;
}


void quick_sort(int arr[][2], int begin, int end) {
    int pivot;

    if (begin < end) {
        pivot = partition(arr, begin, end);
        quick_sort(arr, begin, pivot-1);
        quick_sort(arr, pivot+1, end);
    }
}


int *interval_scheduler(int tasks[][2], int len) {
    int j, *res_set = NULL;

    quick_sort(tasks, 0, len-1);
    res_set = malloc(len*sizeof(int)); // store indices of tasks
    if(res_set == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }

    // add taks[0]
    res_set[0] = 0;
    j = 1;
    for(int i=1; i<len; i++) {
        // if start time of tasks[i] greater than end time of last task taken
        if(tasks[i][0] >= tasks[res_set[j-1]][1]) {
            res_set[j++] = i;
        }
    }

    // fill remaining part of res_set with some invalid int to indicate end
    while(j<len) {
        res_set[j++] = -1;
    }

    return res_set;
}

int main() {
    int tasks[10][2] = {{0,4},{1,2},{2,4},{3,5},{3,6},{5,6},{5,7},{6,7},{7,9},{8,10}};
    int *res = interval_scheduler(tasks, 10);

    printf("Given Tasks: \n");
    for(int i=0; i<10; i++) {
        printf("(%d, %d), ", tasks[i][0], tasks[i][1]);
    }

    printf("\n\nSchedule of maximum non-overlapping tasks: \n");
    for(int i=0; i<10; i++) {
        if(res[i] == -1) {
            break;
        }
        printf("(%d, %d), ", tasks[res[i]][0], tasks[res[i]][1]);
    }
    printf("\n");

    free(res);
    return 0;
}
