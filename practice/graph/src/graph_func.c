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



