#include <stdio.h>
#include <stdlib.h>
#include "util.h"

int *create_tree_arr(int *arr, int *size, int indx);
void preorder_arr(int *tree_arr, int size, int indx);
void inorder_arr(int *tree_arr, int size, int indx);
void postorder_arr(int *tree_arr, int size, int indx);
int *dealloc_tree_arr(int *tree_arr, int *size);

int main() {
    int *tree_arr = NULL, size, chx;
    bool flg = true;

    while(flg) {
        printf("\nBINARY TREE (Array Representation)\n");
        printf("1. Create\n");
        printf("2. Preorder Traversal\n");
        printf("3. Inorder Traversal\n");
        printf("4. Postorder Traversal\n");
        printf("0. Exit\n");
    
        printf("Enter Choice: ");
        scanf("%d", &chx);

        switch (chx) {
            case 0:
                flg = false;
                break;
            case 1:
                if (tree_arr) {
                    tree_arr = dealloc_tree_arr(tree_arr, &size);
                }
                tree_arr = create_tree_arr(tree_arr, &size, 0);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorder_arr(tree_arr, size, 0);
                printf("\n");
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorder_arr(tree_arr, size, 0);
                printf("\n");
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorder_arr(tree_arr, size, 0);
                printf("\n");
                break;
            default:
                printf("Invalid Input.\n");
        }
    
    }
    tree_arr = dealloc_tree_arr(tree_arr, &size);

    return 0;
}

int *create_tree_arr(int *arr, int *size, int indx) {
    int val, left_child_indx, right_child_indx, x, y, old_size;
    printf("Enter value: ");
    x = scanf("%d", &val);

    if (x == 0) {
        do {
            y = getchar();
        } while(y != '\n');
        return arr;
    }

    left_child_indx = (indx+1)*2 - 1;
    right_child_indx = (indx+1)*2;
    
    old_size = *size;

    if (old_size < indx+1) {
        //  new size to accomodate till this element
        (*size) = indx+1;
        arr = realloc(arr, (*size)*sizeof(int));
        if (arr == NULL) {
            printf("MEMORY ALLOCATION ERROR.\n");
            exit(-1);
        }
        // fill from prev size till new size
        for (int i=old_size; i<(*size); i++) {
            arr[i] = -1e9;
        }
    }
    arr[indx] = val;

    // fill subtrees
    printf("LEFT subtree of %d\n", val);
    arr = create_tree_arr(arr, size, left_child_indx);
    printf("RIGHT subtree of %d\n", val);
    arr = create_tree_arr(arr, size, right_child_indx);

    return arr;
}

void preorder_arr(int *tree_arr, int size, int indx) {
    int left_child_indx, right_child_indx;

    if (indx >= size) {
        return;
    }

    left_child_indx = (indx+1)*2 - 1;
    right_child_indx = (indx+1)*2;

    if (tree_arr[indx] > -1e9) {
        printf("%d,", tree_arr[indx]);
    } //else {
    //    printf("NULL,");
    //}
    preorder_arr(tree_arr, size, left_child_indx);
    preorder_arr(tree_arr, size, right_child_indx);
}

void inorder_arr(int *tree_arr, int size, int indx) {
    int left_child_indx, right_child_indx;

    if (indx >= size) {
        return;
    }

    left_child_indx = (indx+1)*2 - 1;
    right_child_indx = (indx+1)*2;
    inorder_arr(tree_arr, size, left_child_indx);
    if (tree_arr[indx] > -1e9) {
        printf("%d,", tree_arr[indx]);
    } //else {
    //    printf("NULL,");
    //}
    inorder_arr(tree_arr, size, right_child_indx);
}

void postorder_arr(int *tree_arr, int size, int indx) {
    int left_child_indx, right_child_indx;

    if (indx >= size) {
        return;
    }

    left_child_indx = (indx+1)*2 - 1;
    right_child_indx = (indx+1)*2;
    postorder_arr(tree_arr, size, left_child_indx);
    postorder_arr(tree_arr, size, right_child_indx);
    if (tree_arr[indx] > -1e9) {
        printf("%d,", tree_arr[indx]);
    } //else {
    //    printf("NULL,");
    //}
}

int *dealloc_tree_arr(int *tree_arr, int *size) {
    *size = 0;
    free(tree_arr);
    return NULL;
}