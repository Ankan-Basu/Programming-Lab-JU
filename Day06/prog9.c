#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
	node *head=NULL;
	int **adj_matrix=NULL, n, *vertex_arr, chx, start_vertex;
	bool flg = true, found=false;

    printf("Enter Directed Acyclic Graph:\n");
	adj_matrix = input_adj_matrix(&n);
	vertex_arr = input_vertex_arr(n);

	head = create_adj_list(adj_matrix, vertex_arr, n);
	print_adj_list(head);

	topo_sort(head, n);

	// free mat and list
	return 0;
}