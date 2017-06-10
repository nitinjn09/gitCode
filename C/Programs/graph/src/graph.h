#include <stdio.h>
#include <stdlib.h>

typedef struct list_node {
    int dest;
    struct list_node *next;
} lNode;

typedef struct ad_list {
    struct list_node *head;
} List;

typedef struct ad_matrix {
    int V;
    int E;
    int **matrix;
} GMatrix;

typedef struct graph {
    int v;
    struct ad_list *array;
} Graph;



/*
graph->array = list
List->head = lNode 
*/
Graph* create_graph(int);
void add_edge(Graph*, int, int);
void print_graph(Graph*);
GMatrix* adjMatrixOfGraph(int);
void printAdjMatrixOfGraph(GMatrix*);
