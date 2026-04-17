#include "graph/graph.h"
#include "priorityQueue/priorityQueue.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
  int n, m, k;
  if (scanf("%d %d", &n, &m) != 2) {
    return 0;
  }

  Graph *g = create_graph(n);
  for (int i = 0; i < m; i++) {
    int u, v, w;
    scanf("%d %d %d", &u, &v, &w);
    add_edge(g, u, v, w);
  }

  scanf("%d", &k);
  int *capitals = malloc(k * sizeof(int));
  int *owner = calloc(n + 1, sizeof(int));
  PriorityQueue *pq = create_pq(m * 2 + k);

  for (int i = 0; i < k; i++) {
    scanf("%d", &capitals[i]);
    owner[capitals[i]] = i + 1;
  }

  for (int i = 0; i < k; i++) {
    int cap = capitals[i];
    for (Edge *e = g->adj[cap]; e; e = e->next) {
      if (!owner[e->to])
        push(pq, e->weight, e->to, i + 1);
    }
  }

  int assigned = k;
  while (pq->size > 0 && assigned < n) {
    Node top = pop(pq);
    if (owner[top.city]) {
      continue;
    }

    owner[top.city] = top.state_id;
    assigned++;

    for (Edge *e = g->adj[top.city]; e; e = e->next) {
      if (!owner[e->to]) {
        push(pq, e->weight, e->to, top.state_id);
      }
    }
  }

  for (int i = 1; i <= k; i++) {
    printf("Государство %d: ", i);
    for (int c = 1; c <= n; c++) {
      if (owner[c] == i)
        printf("%d ", c);
    }
    printf("\n");
  }

  free(capitals);
  free(owner);
  free(pq->data);
  free(pq);
  free_graph(g);

  return 0;
}