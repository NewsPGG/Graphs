#include "PriorityQueue.h"
#include <stdlib.h>

PriorityQueue* create_pq(int cap)
{
  PriorityQueue* pq = malloc(sizeof(PriorityQueue));
  pq->data = malloc(sizeof(Node) * (cap + 1));
  pq->size = 0;
  pq->capacity = cap;
  return pq;
}

void push(PriorityQueue* pq, int d, int c, int s)
{
  int i = ++pq->size;
  while (i > 1 && d < pq->data[i / 2].dist) {
    pq->data[i] = pq->data[i / 2];
    i /= 2;
  }
  pq->data[i] = (Node){d, c, s};
}

Node pop(PriorityQueue *pq)
{
  Node min = pq->data[1];
  Node last = pq->data[pq->size--];
  int i = 1, child;
  while (i * 2 <= pq->size) {
    child = i * 2;
    if (child != pq->size && pq->data[child + 1].dist < pq->data[child].dist) {
      child++;
    }
    if (last.dist > pq->data[child].dist) {
      pq->data[i] = pq->data[child];
    }
    else {
      break;
    }
    i = child;
  }
  pq->data[i] = last;
  return min;
}

void free_pq(PriorityQueue* pq)
{
  free(pq->data);
  free(pq);
}