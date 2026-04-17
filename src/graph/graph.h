#pragma once

typedef struct Edge {
  int to;
  int weight;
  struct Edge *next;
} Edge;

typedef struct {
  int n;
  Edge **adj;
} Graph;

// Allocates a graph and initializes adjacency lists for n cities
Graph *create_graph(int n);

// Adds a bidirectional road between cities u and v with length w
void add_edge(Graph *graph, int u, int v, int w);

// Recursively frees all edges and the graph structure from memory
void free_graph(Graph *graph);