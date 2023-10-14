#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
};
typedef struct node node;

node *create_list();
node *insert_after_k(node *head, int k, int val);
node *insert_before_k(node *head, int k, int val);
node *delete_node_k(node *head, int k);
node *delete_node_with_val(node *head, int val);
node *insert_before_val(node *head, int target_val, int val_to_add);
node *insert_after_val(node *head, int target_val, int val_to_add);
node *concatenate(node *head1, node *head2);
node *merge(node *head1, node *head2);
node *reverse(node *head);
int equals(node *head1, node *head2);
void print_list(node *head);
node *free_list(node *head);

int main() {
    int flg = 1, x, k, val, val2, eql;
    node *head = NULL, *head2 = NULL, *head_tmp = NULL;

    while(flg) {
        printf("\nLINKED LIST\n");
        printf("1. Create\n");
        printf("2. Print\n");
        printf("3. Insert after kth node\n");
        printf("4. Insert after node with value\n");
        printf("5. Insert before kth node\n");
        printf("6. Insert before node with value\n");
        printf("7. Delete kth node\n");
        printf("8. Delete node with value\n");
        printf("9. Find if equal\n");
        printf("10. Reverse list\n");
        printf("11. Concatenate lists\n");
        printf("12. Merge lists\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &x);

        switch(x) {
            case 0:
                flg = 0;
                break;

            case 1:
                head = create_list();
                print_list(head);
                break;

            case 2:
                print_list(head);
                break;

            case 3:
                printf("Enter value of k: ");
                scanf("%d", &k);
                printf("Enter value to insert: ");
                scanf("%d", &val);
                head = insert_after_k(head, k, val);
                print_list(head);
                break;

            case 4:
                printf("Enter value of node: ");
                scanf("%d", &val);
                printf("Enter value to add: ");
                scanf("%d", &val2);
                head = insert_after_val(head, val, val2);
                print_list(head);
                break;

            case 5:
                printf("Enter value of k: ");
                scanf("%d", &k);
                printf("Enter value to insert: ");
                scanf("%d", &val);
                head = insert_before_k(head, k, val);
                print_list(head);
                break;

            case 6:
                printf("Enter value of node: ");
                scanf("%d", &val);
                printf("Enter value to add: ");
                scanf("%d", &val2);
                head = insert_before_val(head, val, val2);
                print_list(head);
                break;

            case 7:
                printf("Enter value of k: ");
                scanf("%d", &k);
                head = delete_node_k(head, k);
                print_list(head);
                break;

            case 8:
                printf("Enter value: ");
                scanf("%d", &val);

                head = delete_node_with_val(head, val);
                print_list(head);
                break;

            case 9:
                if (!head) {
                    printf("Create List1.\n");
                    head = create_list();
                }
                if (!head2) {
                    printf("Create List2.\n");
                    head2 = create_list();
                }

                eql = equals(head, head2);
                if (eql) {
                    printf("EQUALS.\n");
                } else {
                    printf("NOT EQUALS.\n");
                }
                
                head2 = free_list(head2);
                break;

            case 10:
                head = reverse(head);
                print_list(head);
                break;

            case 11:
                if (!head) {
                    printf("Create List1.\n");
                    head = create_list();
                }
                if (!head2) {
                    printf("Create List2.\n");
                    head2 = create_list();
                }
                head = concatenate(head, head2);
                head2 = NULL;
                print_list(head);
                break;

            case 12:
                if (!head) {
                    printf("Create List1.\n");
                    head = create_list();
                }
                if (!head2) {
                    printf("Create List2.\n");
                    head2 = create_list();
                }
                head_tmp = merge(head, head2);
                if (head_tmp) { // merge successful
                    head = head_tmp;
                    head2 = NULL;
                    print_list(head);
                } else {
                    head2 = free_list(head2);
                }
                break;

            default:
                printf("Invalid Input.\n");
                break;
        }
    }

    head = free_list(head);
    return 0;
}

node *create_list() {
    int flg = 1, z, y, x;
    node *head = NULL, *ptr = NULL, *tmp;

    printf("Enter array elements: ");
    while(flg) {
        z = scanf("%d", &x);
        y = getchar();
        
        if (y == '\n') {
            flg=0;
        }

        if (z == 0 && (y!='\n' || y !=',' || y != ' ')) {
            printf("Invalid Input\n");
            break;
        }
        
        tmp = malloc(sizeof(node));
        if (!tmp) { // tmp == NULL
            printf("MEMORY ALLOCATION ERROR\n");
            exit(-1);
        }
        tmp->next = NULL;
        tmp->val = x;

        if (!head) {
            head = tmp;
            ptr = head;
        } else {
            ptr->next = tmp;
            ptr = ptr->next;
        }
    }
    return head;
}

node *insert_after_k(node *head, int k, int val) {
    node *curr = head, *tmp;

    if (k < 0) {
        printf("Invalid List index.\n");
        return head;
    }

    if (!head) {
        printf("List is empty\n");
        return head;
    }

    if (k == 0) {
        // insert at beginning
        tmp = malloc(sizeof(node));
        if (!tmp) {
            printf("MEMORY ALLOCATION ERROR\n");
            exit(-1);
        }
        tmp->val = val;
        tmp->next = head;
        head = tmp;

        return head;
    }

    curr = head;
    for (int i=1; i<k; i++) {
        curr = curr->next;
        if (!curr) {
            printf("List index out of bounds\n");
            return head;
        }
    }

    tmp = malloc(sizeof(node));
    if (!tmp) {
        printf("MEMORY ALLOCATION ERROR\n");
        exit(-1);
    }
    tmp->val = val;
    tmp->next = curr->next;
    curr->next = tmp;

    return head;
}

node *insert_before_k(node *head, int k, int val) {
    node *curr = head, *prev = NULL, *tmp;

    if (k < 1) {
        printf("Invalid List index.\n");
        return head;
    }

    if (!head) {
        printf("List is empty\n");
        return head;
    }

    if (k == 1) { // insert at beginning
        tmp = malloc(sizeof(node));
        if (!tmp) {
            printf("MEMORY ALLOCATION ERROR\n");
            exit(-1);
        }
        tmp->val = val;
        tmp->next = head;
        head = tmp;

        return head;
    }

    curr = head->next;
    prev = head;
    for (int i=2; i<k; i++) {
        if (!curr) {
            printf("List index out of range.\n");
            return head;
        }
        curr = curr->next;
        prev = prev->next;
    }

    tmp = malloc(sizeof(node));
    if (!tmp) {
        printf("MEMORY ALLOCATION ERROR\n");
        exit(-1);
    }
    tmp->val = val;
    tmp->next = curr;
    prev->next = tmp;

    return head;
}

node *delete_node_k(node *head, int k) {
    node *curr = head, *prev = NULL, *tmp;

    if (k <= 0) {
        printf("Invalid List index.\n");
        return head;
    }

    if (!head) {
        printf("List is empty\n");
        return head;
    }

    if (k == 1) {
        // delete head
        tmp = head;
        head = head->next;
        free(tmp);
        return head;
    }

    curr = head->next;
    prev = head;

    for (int i=2; i<k; i++) { // k==1 case already done before
        if (!curr) {
            printf("List index out of range.\n");
            return head;
        }
        curr = curr->next;
        prev = prev->next;
    }

    if (!curr) { // if k == len of list +1
        printf("List index out of range.\n");
        return head;
    }

    prev->next = curr->next;
    free(curr);

    return head;
}

node *insert_before_val(node *head, int target_val, int val_to_add) {
    node *curr = head, *prev = NULL, *tmp = NULL;

    if (!head) {
        printf("List is empty\n");
        return head;
    }

    if (head->val == target_val) {
        // insert at beginning
        tmp = malloc(sizeof(node));
        if (!tmp) { // tmp == NULL
            printf("MEMORY ALLOCATION ERROR\n");
            exit(-1);
        }
        tmp->val = val_to_add;
        tmp->next = head;
        head = tmp;
        return head; // new head
    }

    curr = head->next;
    prev = head;

    while(curr) {
        if (curr->val == target_val) {
            break;
        }
        curr = curr->next;
        prev = prev->next;
    }

    if (!curr) {
         // curr == NULL
        printf("Element %d not found.\n", target_val);
        return head;
    }

    tmp = malloc(sizeof(node));
    if (!tmp) { // tmp == NULL
        printf("MEMORY ALLOCATION ERROR\n");
        exit(-1);
    }
    tmp->val = val_to_add;
    tmp->next = prev->next;
    prev->next = tmp;
    
    return head;
}

node *insert_after_val(node *head, int target_val, int val_to_add) {
    node *curr  = NULL, *tmp = NULL;

    if (!head) {
        printf("List is empty\n");
        return head;
    }

    curr = head;
    while(curr) {
        if (curr->val == target_val) {
            break;
        }
        curr = curr->next;
    }

    if (!curr) {
        // curr == NULL
        printf("Element %d not found.\n", target_val);
        return head;
    }

    tmp = malloc(sizeof(node));
    if (!tmp) {
        printf("MEMORY ALLOCATION ERROR\n");
        exit(-1);
    }
    tmp->val = val_to_add;
    tmp->next = curr->next;
    curr->next = tmp;
    
    return head;
}

node *delete_node_with_val(node *head, int val) {
    node *curr = head, *prev = NULL, *tmp = NULL;
    
    if (!head) { // head == NULL
        printf("List is empty\n");
        return head;
    }

    if (head->val == val) {
        // val found at first node
        tmp = head;
        head = head->next;
        free(tmp);

        return head;
    }

    curr = head->next;
    prev = head;
    while(curr) {
        if (curr->val == val) {
            break;
        }
        curr = curr->next;
        prev = prev->next;
    }

    if (!curr) {
        // curr == NULL
        printf("Element %d not found.\n", val);
        return head;
    }

    // delete the node
    tmp = curr;
    prev->next = curr->next;
    free(tmp);

    return head;
}

node *concatenate(node *head1, node *head2) {
    node *curr = head1;

    while(curr->next) {
        curr = curr->next;
    }
    curr->next = head2;

    return head1;
}

int equals(node *head1, node *head2) {
    node *curr1 = head1, *curr2 = head2;
    
    if (!head1 && !head2) {
        return 1;
    }

    if (!head1 || !head2) {
        return 0;
    }

    while(curr1 && curr2) {
        if (curr1->val != curr2->val) {
            return 0;
        }
        curr1 = curr1->next;
        curr2 = curr2->next;
    }

    if (!curr1 && !curr2) {
        // both null
        return 1;
    } else {
        // list of different length
        return 0;
    }
}

int sorted(node *head) {
    node *curr = NULL, *prev = NULL;

    if (!head) {
        return 1;
    }

    curr = head->next;
    prev = head;

    while(curr) {
        if (prev->val > curr->val) {
            // not sorted
            return 0;
        }
        curr = curr->next;
        prev = prev->next;
    }
    return 1;
}

node *merge(node *head1, node *head2) {
    node *head = NULL, *curr = NULL, *curr1 = head1, *curr2 = head2;

    if (!sorted(head1) || !sorted(head2)) {
        printf("Lists are not sorted.\n");
        return NULL;
    }

    // merge
    if (head1->val < head2->val) {
        head = head1;
        curr1 = head1->next;
    } else {
        head = head2;
        curr2 = head2->next;
    }
    curr = head;

    while(curr1 && curr2) {
        if (curr1->val < curr2->val) {
            curr->next = curr1;
            curr1 = curr1->next;
        } else {
            curr->next = curr2;
            curr2 = curr2->next;
        }
        curr = curr->next;
    }

    if (curr2) {
        curr->next = curr2;
    } else if (curr1) {
        curr->next = curr1;
    }

    return head;
}

node *reverse(node *head) {
    node *curr = NULL, *prev = NULL, *nxt = NULL;
    if (!head) {
        printf("List is empty.\n");
        return head;
    }

    curr = head;
    nxt = curr->next;

    while(curr) {
        curr->next = prev;
        prev = curr;
        curr = nxt;
        if (!curr) {
            break;
        }
        nxt = curr->next;
    }
    
    return prev; // new head
}

void print_list(node *head) {
    node *ptr = head;

    printf("LIST: ");
    while(ptr) {
        printf("%d -> ", ptr->val);
        ptr = ptr->next;
    }
    printf("NULL\n");
}

node *free_list(node *head) {
    node *curr = head, *tmp = NULL;

    while(curr) {
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }
    return NULL;
}