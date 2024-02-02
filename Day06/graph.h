#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    int weight;
    struct node *ptr1;
    struct node *ptr2;
};
typedef struct node node;

enum bool {
    false = 0,
    true = 1
};
typedef enum bool bool;

typedef struct prim_node {
    int vertex;
    int pred;
    int length;
    bool perm_status;
} prim_node;

typedef struct kruskal_edge {
    int u;
    int v;
    int weight;
} kruskal_edge;



void fill_indeg_arr(node *adj_list, int *indeg_arr, int n);
int find_zero_indeg(int *indeg_arr, int n);
bool check_all_vertex_removed(int *indeg_arr, int n);
void topo_sort(node *adj_list, int n);
void floyd_shortest_path(int **adj_matrix, int n);
void dijkstra(node *adj_list, int n, int start_vertex);
void swap(kruskal_edge *a, kruskal_edge *b);
int partition(kruskal_edge *arr,int low,int high);           
void quick_sort(kruskal_edge *arr,int low,int high);
kruskal_edge *create_edge_arr(node *adj_list, int n, int *no_edges);
void union_set(int *disjoint_set, int len, int u, int v);
int find_set(int *disjoint_set, int len, int u);
void kruskal_mst(node *adj_list, int n);
int find_least_len(prim_node *arr, int len);
bool check_all_reached(prim_node *arr, int len);
void prim_mst(node *adj_list, int n);
void bfs(node *adj_list, int n, int start_vertex);
void dfs(node *adj_list, int n, int start_vertex);
node *create_node(int val, int weight);
node *create_adj_list(int **adj_matrix, int *vertex_list, int n);
void print_adj_list(node *adj_list_head);
int **input_adj_matrix(int *n);
int *input_vertex_arr(int n);
void add_vertex(node *head, int n);
void add_edge(node *head, int u, int v);
void del_edge(node *head, int u, int v);
node *del_vertex(node *head, int n);
void clr_buffr();

#endif


