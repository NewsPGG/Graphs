#include "graph/graph.h"
#include "priorityQueue/PriorityQueue.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        perror("Ошибка при открытии файла");
        return 1;
    }

    int n, m, k;
    if (fscanf(file, "%d %d", &n, &m) != 2) {
        fclose(file);
        return 0;
    }

    Graph* g = create_graph(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        if (fscanf(file, "%d %d %d", &u, &v, &w) == 3) {
            add_edge(g, u, v, w);
        }
    }

    if (fscanf(file, "%d", &k) != 1) {
        fclose(file);
        return 0;
    }

    int* capitals = malloc(k * sizeof(int));
    int* owner = calloc(n + 1, sizeof(int));
    PriorityQueue* pq = create_pq(m * 2 + k);

    for (int i = 0; i < k; i++) {
        if (fscanf(file, "%d", &capitals[i]) == 1) {
            owner[capitals[i]] = i + 1;
        }
    }

    fclose(file);

    for (int i = 0; i < k; i++) {
        int cap = capitals[i];
        for (Edge* e = g->adj[cap]; e; e = e->next) {
            if (!owner[e->to])
                push(pq, e->weight, e->to, i + 1);
        }
    }

    int assigned = k;
    while (pq->size > 0 && assigned < n) {
        Node top = pop(pq);
        if (owner[top.city]) continue;

        owner[top.city] = top.state_id;
        assigned++;

        for (Edge* e = g->adj[top.city]; e; e = e->next) {
            if (!owner[e->to]) {
                push(pq, e->weight, e->to, top.state_id);
            }
        }
    }

    for (int i = 1; i <= k; i++) {
        printf("Государство %d: ", i);
        int first = 1;
        for (int c = 1; c <= n; c++) {
            if (owner[c] == i) {
                if (!first) printf(" ");
                printf("%d", c);
                first = 0;
            }
        }
        printf("\n");
    }

    free(capitals);
    free(owner);
    if (pq->data) {
        free(pq->data);
    }

    free(pq);
    free_graph(g);

    return 0;
}