#ifndef SIMPLIFY_H
#define SIMPLIFY_H

#include <stddef.h>

typedef struct AdjNode {
    int vertex;
    struct AdjNode* next;
} AdjNode;

typedef struct {
    int numVertices;
    AdjNode** adjLists;
} Graph;

Graph* createGraph(int vertices);
void addEdge(Graph* graph, int src, int dest);
void simplifyGraph(Graph* graph);
void freeGraph(Graph* graph);
void printGraph(const Graph* graph);

#endif
