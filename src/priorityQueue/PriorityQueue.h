#pragma once

typedef struct {
    int dist;
    int city;
    int state_id;
} Node;

typedef struct {
    Node* data;
    int size;
    int capacity;
} PriorityQueue;

// Creates an empty priority queue with a fixed maximum capacity
PriorityQueue* create_pq(int cap);

// Inserts a new expansion candidate and maintains heap order
void push(PriorityQueue* pq, int d, int c, int s);

// Extracts the node with the minimum distance from the queue
Node pop(PriorityQueue* pq);

// Releases the memory allocated for the priority queue array and struct
void free_pq(PriorityQueue* pq);