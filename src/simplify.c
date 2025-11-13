#include <stdio.h>
#include <stdlib.h>
#include "simplify.h"

static void removeEdge(Graph* graph, int src, int dest) {
    AdjNode* prev = NULL;
    AdjNode* curr = graph->adjLists[src];
    while (curr) {
        if (curr->vertex == dest) {
            if (prev) prev->next = curr->next;
            else graph->adjLists[src] = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

static void freeAdjList(AdjNode* head) {
    AdjNode* curr = head;
    while (curr) {
        AdjNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
}

static int degree(const Graph* graph, int v) {
    int deg = 0;
    AdjNode* temp = graph->adjLists[v];
    while (temp) {
        deg++;
        temp = temp->next;
    }
    return deg;
}

Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    if (!graph) return NULL;
    graph->numVertices = vertices;
    graph->adjLists = calloc(vertices, sizeof(AdjNode*));
    if (!graph->adjLists) {
        free(graph);
        return NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    AdjNode* newNode = malloc(sizeof(AdjNode));
    if (!newNode) return;
    newNode->vertex = dest;
    newNode->next = graph->adjLists[src];
    graph->adjLists[src] = newNode;
    
    newNode = malloc(sizeof(AdjNode));
    if (!newNode) return;
    newNode->vertex = src;
    newNode->next = graph->adjLists[dest];
    graph->adjLists[dest] = newNode;
}

void freeGraph(Graph* graph) {
    if (!graph) return;
    for (int i = 0; i < graph->numVertices; i++) freeAdjList(graph->adjLists[i]);
    free(graph->adjLists);
    free(graph);
}

void printGraph(const Graph* graph) {
    for (int v = 0; v < graph->numVertices; v++) {
        printf("%d:", v);
        AdjNode* temp = graph->adjLists[v];
        while (temp) {
            printf(" %d", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
}

void simplifyGraph(Graph* graph) {
    int changed;
    do {
        changed = 0;
        for (int v = 0; v < graph->numVertices; v++) {
            if (degree(graph, v) == 2) {
                AdjNode* first = graph->adjLists[v];
                AdjNode* second = first->next; 
                if (!first || !second) continue;                 
                int u = first->vertex;
                int w = second->vertex;
                removeEdge(graph, u, v);                
                removeEdge(graph, w, v);
                freeAdjList(graph->adjLists[v]); 
                graph->adjLists[v] = NULL;
                
                if (u != w) {
                    int exists_u_w = 0;
                    AdjNode* temp = graph->adjLists[u];
                    while (temp) {
                        if (temp->vertex == w) {
                            exists_u_w = 1;
                            break;
                        }
                        temp = temp->next;
                    }
                    if (!exists_u_w) addEdge(graph, u, w);
                }
                changed = 1;
                break;
            }
        }
    } while (changed);
}