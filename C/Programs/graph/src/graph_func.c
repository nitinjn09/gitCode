#include "graph.h"

Graph* create_graph (int num_node)
{
    Graph *graph = (Graph*) malloc (sizeof(Graph));
    if (!graph) {
        printf("create graph failed in malloc\n");
        return NULL;
    }

    graph->v = num_node;
    graph->array = (List*) malloc (graph->v * sizeof(List));

    for (int i = 0; i < num_node; i++) {
        graph->array[i].head = NULL;
    }

    return graph;

}

void add_edge (Graph *graph, int src, int dest)
{
    lNode *new_node = (lNode*) malloc (sizeof(lNode));
    if (!new_node) {
        printf("Error in malloc \n");
    }
    
    new_node->dest = dest;
    new_node->next = graph->array[src].head;
    graph->array[src].head = new_node;

}

void print_graph (Graph *graph) 
{
    int index;
    if (graph == NULL) {
        printf("Graph is empty\n");
    }
    printf("Graph::\n");
    for (index = 0; index < graph->v; index++) {
        lNode *temp = graph->array[index].head;
        while (temp != NULL) {
            printf("Edge: (%d, %d)\n",index, temp->dest);
            temp = temp->next;
        }
    }
}

GMatrix* adjMatrixOfGraph(int V) {
    int i, j;
    GMatrix *graph = (GMatrix*) malloc (sizeof(GMatrix));
    if (!graph) {
        printf("%s : Eror in malloc\n",__FUNCTION__);
        return NULL;
    }
    graph->V = V;
    graph->matrix = (int**) malloc (graph->V * graph->V * sizeof(int));
    if(!graph->matrix) { 
        printf("%s : Error in malloc\n",__FUNCTION__);
        free(graph);
    }
    for(i = 0; i < graph->V; i++) {
        graph->matrix[i] = (int*) malloc (graph->V * sizeof(int));
        if (!graph->matrix[i])  {
            printf("%s Error in malloc\n",__FUNCTION__);
        }
    }

    for (i = 0; i < graph->V; i++) {
        for (j = 0; j < graph->V; j++) {
            graph->matrix[i][j] = i+j;
        }
    }

    return graph;
}

void printAdjMatrixOfGraph(GMatrix *graph) {
    int i, j;
    for (i = 0; i < graph->V; i++) {
        for (j = 0; j < graph->V; j++) {
            printf("%d ",graph->matrix[i][j]);
        }
        printf("\n");
    }
}
