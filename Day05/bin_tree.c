#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "tree.h"

node *create_tree();

int main() {
    node *head = NULL;
    bool flg = true;
    int chx;

    while(flg) {
        printf("\nBINARY TREE (Linked Representation)\n");
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
                if (head) {
                    head = dealloc_tree(head);
                }
                head = create_tree();
                // inorder(head);
                break;
            case 2:
                printf("Preorder Traversal: ");
                preorder(head);
                printf("\n");
                break;
            case 3:
                printf("Inorder Traversal: ");
                inorder(head);
                printf("\n");
                break;
            case 4:
                printf("Postorder Traversal: ");
                postorder(head);
                printf("\n");
                break;
            default:
                printf("Invalid Input.\n");
        }
    
    }
    head = dealloc_tree(head);

    return 0;
}


node *create_tree() {
    int val, y, x;
    node *tmp = NULL;

    printf("Enter value: ");
    x = scanf("%d", &val);

    if (x == 0) {
        do {
            y = getchar();
        } while(y != '\n');
        return NULL;
    }

    tmp = create_node(val);
    printf("LEFT subtree of %d\n", val);
    tmp->left = create_tree();
    printf("RIGHT subtree of %d\n", val);
    tmp->right = create_tree();

    return tmp;
}