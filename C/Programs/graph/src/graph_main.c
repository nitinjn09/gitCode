#include "graph.h"

int main ()
{
    /*
    Graph *graph;
    int v = 5;
    graph = create_graph(v);
    add_edge(graph, 0, 1);
    add_edge(graph, 0, 4);
    add_edge(graph, 1, 4);
    add_edge(graph, 1, 2);
    add_edge(graph, 1, 3);
    add_edge(graph, 2, 3);
    add_edge(graph, 3, 4);
*/
    GMatrix *graph = adjMatrixOfGraph(4);
    printAdjMatrixOfGraph(graph);

    return 0;
}


