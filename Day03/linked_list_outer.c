#include <stdio.h>
#include <stdlib.h>
#include "linked_list_outer.h"

node_ll *create_node_ll() {
    node_ll *tmp = malloc(sizeof(node_ll));
    if (tmp == NULL) {
        printf("MEMORY ALLOCATION ERROR.\n");
        exit(-1);
    }
    tmp->next = NULL;
    
    return tmp;
}