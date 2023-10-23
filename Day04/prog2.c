#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
};
typedef struct node node;

typedef enum bool {
    false = 0,
    true = 1
} bool;

node *create_node(int val);
node *create_list();
void print_list(node *head, bool display_addr);
node *dealloc_list(node *head);
void swap_pointer_vars(node **a, node **b);
node *swap_nodes(node *head, node *a, node *b);
void swap_vals(node *a, node *b);
int get_list_len(node *head);
node *bubble_sort_ll(node *head);
node *insertion_sort_ll(node *head);
node *selection_sort_ll(node *head);
void bubble_sort(node *head);
void insertion_sort(node *head);
void selection_sort(node *head);


// node *test_get_ptr_from_indx(node *head, int indx);
// void test();

int main() {
    node *head = NULL;
    bool flg = true;
    int chx;

    while(flg) {
        printf("\n1. Enter Liked List.\n");
        printf("2. Bubble Sort (interchanging data).\n");
        printf("3. Selection Sort (interchanging data).\n");
        printf("4. Insertion Sort (interchanging data).\n");
        printf("5. Bubble Sort (interchanging links).\n");
        printf("6. Selection Sort (interchanging links).\n");
        printf("7. Insertion Sort (interchanging links).\n");
        printf("0. Exit\n");
        
        printf("\nEnter choice: ");
        scanf("%d", &chx);

        switch (chx) {
            case 0:
                flg = false;
                break;
            case 1:
                if (head != NULL) {
                    head = dealloc_list(head);
                }
                head = create_list();
                printf("LINKED LIST: ");
                print_list(head, false);
                break;
            case 2:
                printf("ORIGINAL LIST:\n");
                print_list(head, true);
                bubble_sort(head);
                printf("SORTED LIST (Bubble Sort):\n");
                print_list(head, true);
                break;
            case 3:
                printf("ORIGINAL LIST:\n");
                print_list(head, true);
                selection_sort(head);
                printf("SORTED LIST (Selection Sort):\n");
                print_list(head, true);
                break;
            case 4:
                printf("ORIGINAL LIST:\n");
                print_list(head, true);
                insertion_sort(head);
                printf("SORTED LIST (Insertion Sort):\n");
                print_list(head, true);
                break;
            case 5:
                printf("ORIGINAL LIST:\n");
                print_list(head, true);
                head = bubble_sort_ll(head);
                printf("SORTED LIST (Bubble Sort):\n");
                print_list(head, true);
                break;
            case 6:
                printf("ORIGINAL LIST:\n");
                print_list(head, true);
                head = selection_sort_ll(head);
                printf("SORTED LIST (Selection Sort):\n");
                print_list(head, true);
                break;
            case 7:
                printf("ORIGINAL LIST:\n");
                print_list(head, true);
                head = insertion_sort_ll(head);
                printf("SORTED LIST (Insertion Sort):\n");
                print_list(head, true);
                break;
            default:
                printf("Invalid Input.\n");
        }
    }

    if (head != NULL) {
        head = dealloc_list(head);
    }
    
    return 0;
}

node *create_node(int val) {
    node *tmp = malloc(sizeof(node));
    if (tmp == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    tmp->val = val;
    tmp->next = NULL;

    return tmp;
}

node *create_list() {
    int y, x, z;
    bool flg = true;
    node *head = NULL, *ptr = NULL, *tmp = NULL;

    printf("Enter List: ");
    while(flg) {
        y = scanf("%d", &x);
        z = getchar();

        if (z == '\n') {
            flg = false;
        }

        if (y == 0) {
            if (z != ',' || z != ' ' || z !='\t') {
                printf("Invalid Input.\n");
                // free list
                dealloc_list(head);
                return NULL;
            }
        } else {
            // succesful scan
            tmp = create_node(x);
            if (head == NULL) {
                head = tmp;
                ptr = head;
            } else {
                ptr->next = tmp;
                ptr = ptr->next;
            }
        }
    }
    return head;


}

node *swap_nodes(node *head, node *a, node *b) {
    node *prev_a = NULL, *next_a = NULL, *prev_b = NULL, *next_b = NULL;
    node *ptr = head;
    bool found_a = false, found_b = false;

    if (a == b) {
        // do nothing
        return head;
    }

    if (a == head) {
        found_a = true;
        prev_a = NULL;
    }
    if (b == head) {
        found_b = true;
        prev_b = NULL;
    }

    // get prev nodes of a and b
    while(ptr) {
        if (!found_a && ptr->next == a) {
            prev_a = ptr;
            found_a = true;
        }
        if (!found_b && ptr->next == b) {
            prev_b = ptr;
            found_b = true;
        }
        ptr = ptr->next;
        if (found_a && found_b) {
            break;
        }
    }

    if (!found_a || !found_b) {
        // NOT FOUND
        return head;
    }

    next_a = a->next; 
    next_b = b->next;

    if (b == a->next || a == b->next) {
        if (a == b->next) {
            // just swap the variables so that the following logic works
            swap_pointer_vars(&a, &b);
            swap_pointer_vars(&prev_a, &prev_b);
            swap_pointer_vars(&next_a, &next_b);
        }

        if (prev_a == NULL) { // head node
            head = b;
        } else {
            prev_a->next = b;
        }
        b->next = a;
        a->next = next_b;

        return head;
    }

    // rewire pointers
    if (prev_a == NULL) { // a is head
        head = b;
    } else {
        prev_a->next = b;
    }
    b->next = next_a;

    if (prev_b == NULL) { // b is head
        head = a;
    } else {
        prev_b->next = a;
    }
    a->next = next_b;

    return head;
}

void swap_vals(node *a, node *b) {
    int tmp;
    tmp = a->val;
    a->val = b->val;
    b->val = tmp;
}

void print_list(node *head, bool display_addr) {
    node *ptr = head;

    while(ptr) {
        if (display_addr) {
            printf("(Val: %d, Addr: %p) -> ", ptr->val, ptr);
        } else {
            printf("%d -> ", ptr->val);
        }
        ptr = ptr->next;
    }
    printf("NULL.\n");
}

node *dealloc_list(node *head) {
    node *curr = NULL, *prev = NULL;
    if (head == NULL) {
        return head;
    }

    curr = head;

    while(curr) {
        prev = curr;
        curr = curr->next;
        free(prev);
    }

    return NULL;
}

int get_list_len(node *head) {
    int len = 0;
    node *ptr = head;

    while(ptr) {
        len++;
        ptr = ptr->next;
    }

    return len;
}

node *bubble_sort_ll(node *head) {
    int len;
    node *ptr;
    len = get_list_len(head);

    for (int i=0; i<len; i++) {
        ptr = head;
        for (int j=0; j<len-i-1; j++) {
            if (ptr->val > ptr->next->val) {
                head = swap_nodes(head, ptr, ptr->next);
            } else {
                ptr = ptr->next;
            }
        }
    }
    return head;
}

node *insertion_sort_ll(node *head) {
    int len, stack_top, stack_top_iter;
    node *ptr, *ptr2, **stack;

    len = get_list_len(head);

    // not possible to traverse singly linke list in reverse
    // so using stack (push nodes and then pop to simulate reverse traversal)
    stack = malloc(len*sizeof(node *));
    if (stack == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    stack_top = -1;

    ptr = head;
    while (ptr && ptr->next != NULL) {
        stack_top++;
        stack[stack_top] = ptr;
        
        if (ptr->val > ptr->next->val) {
            ptr2 = ptr->next;
            head = swap_nodes(head, ptr, ptr->next);


            stack[stack_top] = ptr2;
            stack_top_iter = stack_top-1;

            // find correct place of elem in sorted subarr
            while (stack_top_iter > -1 && ptr2->val < stack[stack_top_iter]->val) {
                head = swap_nodes(head, ptr2, stack[stack_top_iter]);
                
                // modifying the vals in stack to refelct the change
                stack[stack_top_iter+1] = stack[stack_top_iter];
                stack[stack_top_iter] = ptr2;
                stack_top_iter--;
            }

        } else {
            ptr = ptr->next;
        }
    }
    free(stack);

    return head;
}

node *selection_sort_ll(node *head) {
    node *curr_min_node = NULL, *ptr1 = NULL, *ptr2 = NULL;

    ptr1 = head; // ptr1 denotes end of sorted subarray. 
    // (ptr1 is 1 step outside the sorted subarray. new min element will come in that place)
    while(ptr1 != NULL) {
        curr_min_node = ptr1;
        for(ptr2=ptr1; ptr2!=NULL; ptr2=ptr2->next) {
            if (ptr2->val < curr_min_node->val) {
                curr_min_node = ptr2;
            }
        }
        head = swap_nodes(head, ptr1, curr_min_node);
        ptr1 = curr_min_node; // bring back the pointer variable to prev index

        ptr1 = ptr1->next;
    }
    return head;
}

void bubble_sort(node *head) {
    int len;
    node *ptr;
    len = get_list_len(head);

    for (int i=0; i<len; i++) {
        ptr = head;
        for (int j=0; j<len-i-1; j++) {
            if (ptr->val > ptr->next->val) {
                swap_vals(ptr, ptr->next);
            }
            ptr = ptr->next;
        }
    }
}

void insertion_sort(node *head) {
    int len, stack_top, stack_top_iter;
    node *ptr, *ptr2, **stack;

    len = get_list_len(head);

    // not possible to traverse singly linke list in reverse
    // so using stack (push nodes and then pop to simulate reverse traversal)
    stack = malloc(len*sizeof(node *));
    if (stack == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    stack_top = -1;

    ptr = head;
    while (ptr && ptr->next != NULL) {
        stack_top++;
        stack[stack_top] = ptr;
        
        if (ptr->val > ptr->next->val) {
            swap_vals(ptr, ptr->next);

            stack_top_iter = stack_top-1;
            ptr2 = ptr;

            // find correct place of elem in sorted subarr
            while (stack_top_iter > -1 && ptr2->val < stack[stack_top_iter]->val) {
                // head = swap_nodes(head, ptr2, stack[stack_top_iter]);
                swap_vals(ptr2, stack[stack_top_iter]);

                // modifying the vals in stack to refelct the change
                ptr2 = stack[stack_top_iter];
                stack_top_iter--;
            }
        }
        ptr = ptr->next;
    }
    free(stack);
}

void selection_sort(node *head) {
    node *curr_min_node = NULL, *ptr1 = NULL, *ptr2 = NULL;

    ptr1 = head; // ptr1 denotes end of sorted subarray. 
    // (ptr1 is 1 step outside the sorted subarray. new min element will come in that place)
    while(ptr1 != NULL) {
        curr_min_node = ptr1;
        for(ptr2=ptr1; ptr2!=NULL; ptr2=ptr2->next) {
            if (ptr2->val < curr_min_node->val) {
                curr_min_node = ptr2;
            }
        }
        swap_vals(ptr1, curr_min_node);

        ptr1 = ptr1->next;
    }
}

void swap_pointer_vars(node **a, node **b) {
    node *tmp = *a;
    *a = *b;
    *b = tmp;
}

// node *test_get_ptr_from_indx(node *head, int indx) {
//     node *ptr = head;

//     for (int i=0; i<indx; i++) {
//         if (!ptr) {
//             break; // ptr = NULL
//         }
//         ptr = ptr->next;
//     }
//     return ptr;
// }

// void test() {
//     int indx1, indx2;
//     bool flg = true;
//     node *head = NULL, *ptr1 = NULL, *ptr2 = NULL;
//     head = create_list();
//     print_list(head);

//     while(flg) {
//         printf("Enter index1: ");
//         scanf("%d", &indx1);
//         printf("Enter index2: ");
//         scanf("%d", &indx2);
//         ptr1 = test_get_ptr_from_indx(head, indx1);
//         ptr2 = test_get_ptr_from_indx(head, indx2);
//         // printf("%p\n", ptr);
//         head = swap_nodes(head, ptr1, ptr2);
//         print_list(head);
//     }
// }