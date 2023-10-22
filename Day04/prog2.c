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
void print_list(node *head);
node *dealloc_list(node *head);
void swap_pointer_vars(node **a, node **b);
node *swap_nodes(node *head, node *a, node *b);
node *test_get_ptr_from_indx(node *head, int indx);
void test();

int main() {
    // node *head = NULL;
    // head = create_list();
    // print_list(head);
    test();

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


void print_list(node *head) {
    node *ptr = head;

    while(ptr) {
        printf("(Val: %d, Ptr: %p) -> ", ptr->val, ptr);
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

void swap_pointer_vars(node **a, node **b) {
    node *tmp = *a;
    *a = *b;
    *b = tmp;
}

node *test_get_ptr_from_indx(node *head, int indx) {
    node *ptr = head;

    for (int i=0; i<indx; i++) {
        if (!ptr) {
            break; // ptr = NULL
        }
        ptr = ptr->next;
    }
    return ptr;
}

void test() {
    int indx1, indx2;
    bool flg = true;
    node *head = NULL, *ptr1 = NULL, *ptr2 = NULL;
    head = create_list();
    print_list(head);

    while(flg) {
        printf("Enter index1: ");
        scanf("%d", &indx1);
        printf("Enter index2: ");
        scanf("%d", &indx2);
        ptr1 = test_get_ptr_from_indx(head, indx1);
        ptr2 = test_get_ptr_from_indx(head, indx2);
        // printf("%p\n", ptr);
        head = swap_nodes(head, ptr1, ptr2);
        print_list(head);
    }
}