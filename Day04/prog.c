#include <stdio.h>
#include <stdlib.h>

enum bool {
    false = 0,
    true = 1
};
typedef enum bool bool;

int *create_arr(int *arr_size);
void print_arr(int *arr, int arr_size);
void clr_inp_buffr();
int linear_search(int *arr, int arr_size, int target);
int binary_search(int *arr, int arr_size, int target);
void bubble_sort(int *arr, int arr_size);
void selection_sort(int *arr, int arr_size);
void insertion_sort(int *arr, int arr_size);
void quick_sort(int *arr, int arr_size);
void merge_sort(int *arr, int arr_size);
int *merge(int *arr1, int arr1_size, int *arr2, int arr2_size);
void quick_sort_(int *arr, int start, int end);
void merge_sort_(int *arr, int start, int end);
int partition(int *arr, int start, int end);
void swap(int *a, int *b);

int main() {
    bool flg = true;
    int chx;
    int *arr = NULL, arr_size = 0;
    int val, res;

    while (flg) {
        printf("\n1. Enter array.\n");
        printf("2. Linear Search.\n");
        printf("3. Binary Search.\n");
        printf("4. Bubble Sort.\n");
        printf("5. Selection Sort.\n");
        printf("6. Insertion Sort.\n");
        printf("7. Quick Sort (Recursive).\n");
        printf("8. Merge Sort (Recursive).\n");
        printf("0. Exit\n");
        
        printf("\nEnter choice: ");
        scanf("%d", &chx);

        switch (chx) {
            case 0:
                flg = false;
                break;
            case 1:
                if (arr_size > 0) {
                    free(arr); arr_size = 0;
                }
                arr = create_arr(&arr_size);
                printf("ARRAY: ");
                print_arr(arr, arr_size);
                break;
            case 2:
                printf("Enter target value: ");
                scanf("%d", &val);
                clr_inp_buffr();

                res = linear_search(arr, arr_size, val);
                if (res != -1) {
                    printf("FOUND AT INDEX: %d\n", res);
                } else {
                    printf("NOT FOUND\n");
                }
                break;
            case 3:
                printf("Enter target value: ");
                scanf("%d", &val);
                clr_inp_buffr();

                res = binary_search(arr, arr_size, val);
                if (res != -1) {
                    printf("FOUND AT INDEX: %d\n", res);
                } else {
                    printf("NOT FOUND\n");
                }
                break;
            case 4:
                bubble_sort(arr, arr_size);
                printf("SORTED ARRAY (Bubble Sort): ");
                print_arr(arr, arr_size);
                break;
            case 5:
                selection_sort(arr, arr_size);
                printf("SORTED ARRAY (Selection Sort): ");
                print_arr(arr, arr_size);
                break;
            case 6:
                insertion_sort(arr, arr_size);
                printf("SORTED ARRAY (Insertion Sort): ");
                print_arr(arr, arr_size);
                break;
            case 7:
                quick_sort(arr, arr_size);
                printf("SORTED ARRAY (Quick Sort): ");
                print_arr(arr, arr_size);
                break;
            case 8:
                merge_sort(arr, arr_size);
                printf("SORTED ARRAY (Merge Sort): ");
                print_arr(arr, arr_size);
                break;
            default:
                printf("Invalid Input.\n");
        }
    }

    if (arr_size > 0) {
        free(arr);
    }
    
    return 0;
}


int *create_arr(int *arr_size) {
    int x, y, z, *arr = NULL;
    bool flg = true;
    *arr_size = 0;

    printf("Enter the array: ");

    while (flg) {
        y = scanf("%d", &x);
        z = getchar();
        if (z == '\n') {
            flg = false;
        }
        
        if (y == 0) {
            if ( z != ',' || z != ' ' || z != '\t') {
                printf("Invalid Input\n");
                
                if (*arr_size > 0) {
                    free(arr);
                    *arr_size = 0;
                }
                arr = NULL;
                flg = false; // exit out of func
                clr_inp_buffr();
            }
        } else {
            (*arr_size)++;
            arr = realloc(arr, (*arr_size)*sizeof(int));
            if (arr == NULL) {
                printf("MEMORY ALLOCATION ERROR.\n");
                exit(-1);
            }
            arr[(*arr_size)-1] = x;
        }
    }

    return arr;
}

void clr_inp_buffr() {
    int x;
    do {
        x = getchar();
    } while (x != '\n');
}

void print_arr(int *arr, int arr_size) {
    printf("{");
    for (int i=0; i<arr_size; i++) {
        printf("%d", arr[i]);
        if (i != arr_size-1) {
            printf(", ");
        }
    }
    printf("}\n");
}


int linear_search(int *arr, int arr_size, int target) {
    int indx = -1;
    for (int i=0; i<arr_size; i++) {
        if (arr[i] == target) {
            indx = i;
            break;
        }
    }

    return indx;
}

int binary_search(int *arr, int arr_size, int target) {
    int start, end, mid;
    bool found = false;
    start = 0;
    end = arr_size - 1;

    while (start <= end) {
        mid = start + (end - start)/2;
        if (arr[mid] == target) {
            // return
            found = true;
            break;
        } else if (arr[mid] < target) {
            start = mid+1;
        } else {
            end = mid - 1;
        }
    }

    if (!found) {
        mid = -1; // to return as indx
    }
    return mid;
}

void swap(int *a, int *b) {
    int tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void bubble_sort(int *arr, int arr_size) {
    for (int i=0; i<arr_size; i++) {
        for (int j=0; j<arr_size-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}

void selection_sort(int *arr, int arr_size) {
    int curr_min_indx;
    // i denotes boundary (last element) of sorted part of array
    for (int i=-1; i<arr_size-1; i++) {
        curr_min_indx = i+1;
        for(int j=i+1; j<arr_size; j++) {
            if (arr[j] < arr[curr_min_indx]) {
                curr_min_indx = j;
            }
        }
        swap(&arr[i+1], &arr[curr_min_indx]);
    }
}

void insertion_sort(int *arr, int arr_size) {
    for (int i=0; i<arr_size-1; i++) {
        // if (arr[i] < arr[i+1]) {
        //     // do nothing
        // }
        if (arr[i] > arr[i+1]) {
            swap(&arr[i+1], &arr[i]);

            // adjust the sorted part of the array
            for (int j=i; j>0; j--) {
                if (arr[j] < arr[j-1]) {
                    swap(&arr[j-1], &arr[j]);
                }
            }
        }
    }
}

int partition(int *arr, int start, int end) {
    int pivot = arr[end];
    int i = start - 1;
   
    for (int j=i+1; j<end; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    i++;
    swap(&arr[i], &arr[end]); // putting the pivot in place

    return i;
}

void quick_sort_(int *arr, int start, int end) {
    if (start < end) {
        int pivot_index = partition(arr, start, end);

        quick_sort_(arr, start, pivot_index-1);
        quick_sort_(arr, pivot_index+1, end);
    }
}

void quick_sort(int *arr, int arr_size) {
    quick_sort_(arr, 0, arr_size-1);
}

int *merge(int *arr1, int arr1_size, int *arr2, int arr2_size) {
    int arr_size = arr1_size + arr2_size;
    int i, j, k;

    int *arr = malloc(arr_size*sizeof(int));
    if (arr == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }

    i = 0; j = 0, k = 0;

    while(i < arr1_size && j < arr2_size) {
        if(arr1[i] < arr2[j]) {
            arr[k++] = arr1[i];
            i++;
        } else {
            arr[k++] = arr2[j];
            j++;
        }
    }

    // copy remaining elemnets (if exists)
    while (i < arr1_size) {
        arr[k++] = arr1[i++];
    }
    while (j < arr2_size) {
        arr[k++] = arr2[j++];
    }

    return arr;
}

void merge_sort_(int *arr, int start, int end) {
    int mid, *arr_res;
    if (start == end) {
        return;
    }

    if (start < end) {
        mid = start + (end - start)/2;
        merge_sort_(arr, start, mid);
        merge_sort_(arr, mid+1, end);

        arr_res = merge(arr+start, mid-start+1, arr+mid+1, end-(mid+1)+1);

        for (int i=0; i<end-start+1; i++) {
            arr[start+i] = arr_res[i];
        }
        free(arr_res);
    }
}

void merge_sort(int *arr, int arr_size) {
    merge_sort_(arr, 0, arr_size-1);
}

void test() {
    int *arr = NULL, *arr2 =NULL, *arr3 = NULL, size1, size2;
    int s1, e1, s2, e2;
    arr = create_arr(&size1);
    // arr2 = create_arr(&size2);

    printf("Enter start of 1: ");
    scanf("%d", &s1);
    printf("Enter end of 1: ");
    scanf("%d", &e1);
    printf("Enter start of 2: ");
    scanf("%d", &s2);
    printf("Enter end of 2: ");
    scanf("%d", &e2);

    size1 = e1 - s1 + 1;
    size2 = e2 - s2 + 1;

    arr3 = merge(arr+s1, size1, arr+s2, size2);
    print_arr(arr3, size1+size2);
}