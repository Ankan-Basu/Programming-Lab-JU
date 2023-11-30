#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "tree.h"

node *create_bst();
node *insert_bst(node *head, int val);
bool search_bst(node *head, int key);
node *delete_bst(node *head, int key);

int main() {
    bool flg = true, found;
    int chx, val;
    node *head = NULL;

    while(flg) {
        printf("\nBST\n");
        printf("1. Create\n");
        printf("2. Insert\n");
        printf("3. Delete\n");
        printf("4. Search\n");
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
                head = create_bst();
                inorder(head);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &val);
                head = insert_bst(head, val);
                inorder(head);
                break;
            case 3:
                printf("Enter value: ");
                scanf("%d", &val);
                head = delete_bst(head, val);
                inorder(head);
                break;
            case 4:
                printf("Enter value: ");
                scanf("%d", &val);
                found = search_bst(head, val);
                if (found) {
                    printf("%d FOUND.\n", val);
                } else {
                    printf("%d NOT FOUND.\n", val);
                }
                break;
            default:
                printf("Invalid Input.\n");
        }
    
    }

    head = dealloc_tree(head);
    return 0;
}

node *create_bst() {
    node *head = NULL;
    int size, *buffer = NULL;

    printf("Enter the elements: ");
    buffer = input(&size);

    for (int i=0; i<size; i++) {
        head = insert_bst(head, buffer[i]);
    }
    free(buffer);

    return head;
}

node *insert_bst(node *head, int val) {
    node *ptr = head, *ptr_paren = NULL;

    if (head == NULL) {
        head = create_node(val);
        return head;
    }

    // search
    while(ptr) {
        ptr_paren = ptr;
        if (ptr->val == val) {
            printf("%d already exists in the BST.\n", val);
            return head;
        } else if (ptr->val < val) {
            ptr = ptr->right;
        } else {
            ptr = ptr->left;
        }
    }

    if (ptr_paren->val > val) {
        ptr_paren->left = create_node(val);
    } else {
        ptr_paren->right = create_node(val);
    }

    return head;
}

bool search_bst(node *head, int key) {
    node *ptr = head;
    
    if (ptr == NULL) {
        return false;
    }

    if (ptr->val == key) {
        return true;
    } else if (ptr->val < key) {
        return search_bst(ptr->right, key);
    } else {
        return search_bst(ptr->left, key);
    }
}

node *delete_bst(node *head, int key) {
    node *ptr = head, *ptr2 = NULL, *ptr_paren = NULL;
    int tmp;
    
    // search
    while(ptr) {
        if (ptr->val == key) {
            break;
        } else if (ptr->val < key) {
            ptr_paren = ptr;
            ptr = ptr->right;
        } else {
            ptr_paren = ptr;
            ptr = ptr->left;
        }
    }

    if (ptr == NULL) {
        printf("%d not found in BST\n", key);
        return head;
    }

    // if (ptr_paren == ptr) {
    //     ptr_paren = NULL; // ptr is head node
    // }

    //  delete
    if (ptr->left == NULL && ptr->right == NULL) { // leaf node
        free(ptr);
        if (ptr_paren == NULL) {
            // deleting head node
            return NULL;
        }
        if (ptr_paren->left == ptr) {
            ptr_paren->left = NULL;
        } else {
            ptr_paren->right = NULL;
        }
        return head;
    } 
    if (ptr->left != NULL && ptr->right == NULL) {
        if (ptr_paren == NULL) {
            // deleting head node
            head = ptr->left;
            // return head;
        } else {
            // connect paren to left subtree of ptr
            if (ptr_paren->left == ptr) {
                ptr_paren->left = ptr->left;
            } else {
                ptr_paren->right = ptr->left;
            }
        }
        free(ptr);
        return head;
    } 
    if (ptr->left == NULL && ptr->right != NULL) {
        if (ptr_paren == NULL) {
            // deleting head node
            head = ptr->right;
            // return head;
        } else {
            // connect paren to right subtree of ptr
            if (ptr_paren->left == ptr) {
                ptr_paren->left = ptr->right;
            } else {
                ptr_paren->right = ptr->right;
            }
        }
        free(ptr);
        return head;
    } 
    if (ptr->left != NULL && ptr->right != NULL) {
        // both left and right subtree present
        // find inorder successor. i.e. least elem in right subtree

        ptr2 = ptr->right;
        ptr_paren = ptr; // initilaisation

        while(ptr2) {
            ptr_paren = ptr2;
            ptr2 = ptr2->left;
        }

        //  swap. ptr_paren will have inorder successor of ptr 

        tmp = ptr->val;
        ptr->val = ptr_paren->val;
        ptr_paren->val = tmp;

        // delete the paren_ptr node
        ptr = delete_bst(head, key); 

    }
    
    return head;
}
