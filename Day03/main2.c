// FOR TESTING

#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

int main() {
    node *head = NULL, *ptr = NULL, *ptr1, *ptr2;
    int flg = 1, chx, val, indx, val1, val2, indx1, indx2;

    while(flg) {
        printf("\n1. Insert\n");
        printf("2. Print Forward\n");
        printf("3. Print Backward\n");
        printf("4. Search\n");
        printf("5. Swap\n");
        printf("6. Search Ny index\n");

        scanf("%d", &chx);

        switch (chx) {
            case 1:
                printf("Enter val: ");
                scanf("%d", &val);
                head = insert_before(head, val);
                break;
            case 2:
                print_list(head);
                break;
            case 3:
                ptr = head;
                while (ptr && ptr->next) {
                    ptr = ptr->next;
                }
                print_list_back(ptr);
                break;
            case 4:
                printf("Enter val: ");
                scanf("%d", &val);
                ptr = get_ptr(head, val);
                indx = get_index(head, ptr);
                printf("%d\t%p\n", indx, ptr);
                break;
            case 5:
                printf("Enter val1: ");
                scanf("%d", &val1);
                printf("Enter val2: ");
                scanf("%d", &val2);

                ptr1 = get_ptr(head, val1);
                indx1 = get_index(head, ptr1);

                ptr2 = get_ptr(head, val2);
                indx2 = get_index(head, ptr2);

                head = swap_nodes(head, ptr1, ptr2);

                break;
            case 6:
                printf("Enter indx val: ");
                scanf("%d", &indx);
                ptr = get_ptr_from_indx(head, indx);
                printf("%d\t%p\n", indx, ptr);
                break;
            default:
                printf("INVALID\n");
        }
    }
    return 0;
}