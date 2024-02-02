#include "str_func.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// enum bool {
//     false = 0,
//     true = 1
// };
// typedef enum bool bool;

struct tree_node {
    char data;  // Token or operator
    struct tree_node *left;
    struct tree_node *right;
};
typedef struct tree_node tree_node;

// Function to create a new node
tree_node *create_node(char data) {
    struct tree_node *new_node = (struct tree_node*)malloc(sizeof(struct tree_node));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    return new_node;
}

// Function to build the parse tree
tree_node *build_parse_tree(char *expression, int start, int end) {
    if (start > end) {
        return NULL;
    }

    tree_node *root = create_node(expression[start]);

    // Check for operators
    if (start + 1 <= end && expression[start + 1] == '/' || expression[start + 1] == '*' ||
        expression[start + 1] == '+' || expression[start + 1] == '-') {

        root->left = create_node(expression[start + 1]);
        root->right = build_parse_tree(expression, start + 2, end);
    } else {
        // Operand case
        root->left = build_parse_tree(expression, start + 1, end);
    }

    return root;
}

// Function to print the parse tree in an inorder traversal
void print_parse_tree_in(tree_node *root) {
    if (root != NULL) {
        print_parse_tree_in(root->left);
        printf("%c, ", root->data);
        print_parse_tree_in(root->right);
    }
}

// Function to print the parse tree in an preorder traversal
void print_parse_tree_pre(tree_node *root) {
    if (root != NULL) {
        printf("%c, ", root->data);
        print_parse_tree_pre(root->left);
        print_parse_tree_pre(root->right);
    }
}

bool is_operator(char x) {
    return (x == '*' || x == '/' || x == '+' || x == '-' || x == '=');
}

char **lexicial_analyser(char *expression, int *no_of_op, int *no_of_id) {
    char *operators = NULL, *identifiers = NULL, **res = NULL;
    int len = strlen(expression);

    for (int i=0; i<len; i++) {
        if(is_operator(expression[i])) {
            // append to operators array
            (*no_of_op)++;
            operators = realloc(operators, (*no_of_op)*(sizeof(char)));
            if (operators == NULL) {
                printf("MEMORY ALLOCATION ERROR.\n");
                exit(-1);
            }
            operators[(*no_of_op) - 1] = expression[i];
        } else {
            if (expression[i] == ' ') {
                continue;
            }
            (*no_of_id)++;
            identifiers = realloc(identifiers, (*no_of_id)*(sizeof(char)));
            if (identifiers == NULL) {
                printf("MEMORY ALLOCATION ERROR.\n");
                exit(-1);
            }
            identifiers[(*no_of_id) - 1] = expression[i];
        }
    }
    res = malloc(2*sizeof(char *));
    if (res == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    res[0] = operators;
    res[1] = identifiers;

    return res;
}

char *trim_spaces(char *expression) {
    int len, new_len = 0;
    char *res = NULL;
    len = strlen(expression);

    for (int i=0; i<len+1; i++) {
        if (expression[i] == ' ') {
            continue;
        }

        new_len++;
        res = realloc(res, new_len*sizeof(char));
        if (res == NULL) {
            printf("MEMORY ALLOCATION ERROR.\n");
            exit(-1);
        }
        res[new_len - 1] = expression[i];
    }
    return res;
}

int search_symbols(char query) {
    int indx = -1;
    bool found = false;
    char symbols[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    for (int i=0; i<10; i++) {
        if (symbols[i] == query) {
            indx = i;
            found = true;
            break;
        }
    }

    if (!found) {
        indx = -1;
    }

    return indx;
}

void semantic_analyser(char **res, int no_of_id, int no_of_op) {
    int idf;
    
    // printf("operator: ");
    for (int i=0; i<no_of_id; i++) {
        idf = search_symbols(res[1][i]);
        
        if (idf == -1) {
            printf("Undefined Symbol: %c\n", res[1][i]);
        } else {
            printf("Int Symbol Detected: %c\n", res[1][i]);
        }
    }
}


int main() {
    char *expression = input_str();
    // int length = sizeof(expression) / sizeof(expression[0]);
    int no_of_op, no_of_id;
    char **res;

    char *exp = trim_spaces(expression);

    res = lexicial_analyser(exp, &no_of_op, &no_of_id);
    printf("Output of Lexical Analysis:\n");

    printf("operator: ");
    for (int i=0; i<no_of_op; i++) {
        printf("%c, ", res[0][i]);
    }
    printf("\n");
    printf("ids: ");
    for (int i=0; i<no_of_id; i++) {
        printf("%c, ", res[1][i]);
    }
    printf("\n");
    
    tree_node *root = build_parse_tree(exp, 0, strlen(exp) - 1);
    printf("\nOutput of Syntactic Analysis:\n");
    printf("Parse Tree (Inorder Traversal):\n");
    print_parse_tree_in(root);
    printf("\n");
    printf("Parse Tree (Preorder Traversal):\n");
    print_parse_tree_pre(root);
    printf("\n");

    printf("\nOutput of Semantic Analysis:\n");
    semantic_analyser(res, no_of_id, no_of_op);

    return 0;
}
