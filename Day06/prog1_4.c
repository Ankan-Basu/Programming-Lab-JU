#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
	node *head=NULL;
	int **adj_matrix=NULL, n, *vertex_arr, chx, u, v;
	bool flg = true;

	adj_matrix = input_adj_matrix(&n);
	vertex_arr = input_vertex_arr(n);

	head = create_adj_list(adj_matrix, vertex_arr, n);
	print_adj_list(head);

	

	while(flg) {
		printf("\nSelect Option\n");
		printf("1. Add vertex\n");
		printf("2. Add edge\n");
		printf("3. Delete edge\n");
		printf("4. Delete vertex\n");
		printf("0. Exit\n");

		printf("enter choice: ");
		scanf("%d", &chx);

		switch (chx) {
			case 0:
				flg = false;
				break;
			case 1:
				printf("Enter vertex name: ");
				scanf("%d", &v);
				add_vertex(head, v);
				print_adj_list(head);
				break;
			case 2:
				printf("Enter vertices of edge (comma seperated u,v): ");
				scanf("%d,%d", &u, &v);
				add_edge(head, u, v);
				print_adj_list(head);
				break;
			case 3:
				printf("Enter vertices of edge (comma seperated u,v): ");
				scanf("%d,%d", &u, &v);
				del_edge(head, u, v);
				print_adj_list(head);
				break;
			case 4:
				printf("Enter vertex name: ");
				scanf("%d", &v);
				head = del_vertex(head, v);
				print_adj_list(head);
				break;
			default:
				printf("Invalid Input.\n");
		}
	}

	// free mat and list
	return 0;
}