#include "graph.h"
#include <stdlib.h>

Graph* create_graph(int n) {
    Graph* gpaph = malloc(sizeof(Graph));
    gpaph->n = n;
    gpaph->adj = calloc(n + 1, sizeof(Edge*));
    return gpaph;
}

void add_edge(Graph* graph, int u, int v, int w) {
    Edge* e1 = malloc(sizeof(Edge));
    e1->to = v; e1->weight = w; e1->next = graph->adj[u];
    graph->adj[u] = e1;

    Edge* e2 = malloc(sizeof(Edge));
    e2->to = u; e2->weight = w; e2->next = graph->adj[v];
    graph->adj[v] = e2;
}

void free_graph(Graph* graph) {
    for (int i = 1; i <= graph->n; i++) {
        Edge* e = graph->adj[i];
        while (e) {
            Edge* tmp = e;
            e = e->next;
            free(tmp);
        }
    }
    free(graph->adj);
    free(graph);
}