#include "graph/graph.h"
#include "priorityQueue/PriorityQueue.h"
#include <assert.h>
#include <stdio.h>

void test_pq_basic_order() {
  PriorityQueue *pq = create_pq(10);

  push(pq, 100, 1, 1);
  push(pq, 10, 2, 1);
  push(pq, 50, 3, 1);

  assert(pop(pq).dist == 10);
  assert(pop(pq).dist == 50);
  assert(pop(pq).dist == 100);

  free_pq(pq);
}

void test_pq_same_distances() {
  PriorityQueue *pq = create_pq(10);

  push(pq, 20, 1, 1);
  push(pq, 20, 2, 2);
  push(pq, 20, 3, 3);

  assert(pq->size == 3);

  pop(pq);
  pop(pq);
  pop(pq);

  assert(pq->size == 0);

  free_pq(pq);
}

void test_pq_single_element() {
  PriorityQueue *pq = create_pq(5);

  push(pq, 42, 10, 2);

  Node n = pop(pq);

  assert(n.dist == 42);
  assert(n.city == 10);
  assert(n.state_id == 2);

  free_pq(pq);
}

void test_graph_creation() {
  Graph *g = create_graph(100);

  assert(g->n == 100);
  assert(g->adj[1] == NULL);
  assert(g->adj[100] == NULL);

  free_graph(g);
}

void test_graph_edges() {
  Graph *g = create_graph(5);

  add_edge(g, 1, 2, 15);

  assert(g->adj[1]->to == 2 && g->adj[1]->weight == 15);
  assert(g->adj[2]->to == 1 && g->adj[2]->weight == 15);

  free_graph(g);
}

void test_pq_stress() {
  int count = 1000;

  PriorityQueue *pq = create_pq(count);

  for (int i = count; i > 0; i--) {
    push(pq, i, i, 1);
  }

  for (int i = 1; i <= count; i++) {
    Node n = pop(pq);
    assert(n.dist == i);
  }

  free_pq(pq);
}

void test_pq_state_integrity() {
  PriorityQueue *pq = create_pq(10);

  push(pq, 10, 1, 101);
  push(pq, 5, 2, 202);

  Node first = pop(pq);
  assert(first.state_id == 202);
  Node second = pop(pq);
  assert(second.state_id == 101);

  free_pq(pq);
}

int main() {
  test_pq_basic_order();
  test_pq_same_distances();
  test_pq_single_element();
  test_graph_creation();
  test_graph_edges();
  test_pq_stress();
  test_pq_state_integrity();

  return 0;
}