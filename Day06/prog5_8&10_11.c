#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main() {
	node *head=NULL;
	int **adj_matrix=NULL, n, *vertex_arr, chx, start_vertex;
	bool flg = true, found=false;

	adj_matrix = input_adj_matrix(&n);
	vertex_arr = input_vertex_arr(n);

	head = create_adj_list(adj_matrix, vertex_arr, n);
	print_adj_list(head);

	printf("Enter start vertex (BFS, DFS, Dijkstra): ");
	scanf("%d", &start_vertex);
	for (int i=0; i<n; i++) {
		if(vertex_arr[i] == start_vertex) {
			found = true;
			break;
		}
	}
	if(!found) {
		printf("Invalid start vertex.\n");
		exit(-1);
	}

	while(flg) {
		printf("\nSelect Option\n");
		printf("1. BFS\n");
		printf("2. DFS\n");
		printf("3. Dijkstra's Algorithm\n");
		printf("4. Floyd's Algorithm\n");
		printf("5. Kruskal's Algorithm\n");
		printf("6. Prim's Algorithm\n");
		printf("0. Exit\n");

		printf("enter choice: ");
		scanf("%d", &chx);

		switch (chx) {
			case 0:
				flg = false;
				break;
			case 1:
				bfs(head, n, start_vertex);
				break;
			case 2:
				dfs(head, n, start_vertex);
				break;
			case 3:
				dijkstra(head, n, start_vertex);
				break;
			case 4:
				floyd_shortest_path(adj_matrix, n);
				break;
			case 5:
				kruskal_mst(head, n);
				break;
			case 6:
				prim_mst(head, n);
				break;
			default:
				printf("Invalid Input.\n");
		}
	}

	// free mat and list
	return 0;
}