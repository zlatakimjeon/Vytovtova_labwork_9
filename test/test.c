#include <stdio.h>
#include <stdlib.h>
#include "simplify.h"

static int hasEdge(Graph* graph, int u, int w) {
    AdjNode* temp = graph->adjLists[u];
    while (temp) {
        if (temp->vertex == w) return 1;
        temp = temp->next;
    }
    return 0;
}

static int getDegree(Graph* graph, int v) {
    if (!graph->adjLists[v]) return 0;
    int deg = 0;
    AdjNode* temp = graph->adjLists[v];
    while (temp) {
        deg++;
        temp = temp->next;
    }
    return deg;
}

int test_basic_graph() {
    Graph* g = createGraph(4);
    addEdge(g,0,1);
    addEdge(g,1,2);
    addEdge(g,2,3);
    simplifyGraph(g);
    int pass = 1;
    if (getDegree(g,0) != 1) pass = 0;
    if (g->adjLists[1] != NULL) pass = 0;
    if (g->adjLists[2] != NULL) pass = 0;
    if (getDegree(g,3) != 1) pass = 0;
    if (!hasEdge(g,0,3) || !hasEdge(g,3,0)) pass = 0;
    freeGraph(g);
    printf("test_basic_graph %s\n", pass ? "passed" : "failed"); fflush(stdout);
    return pass;
}

int test_cycle_graph() {
    Graph* g = createGraph(4);
    addEdge(g,0,1);
    addEdge(g,1,2);
    addEdge(g,2,3);
    addEdge(g,3,0);
    simplifyGraph(g);
    int pass = 1;
    if (g->adjLists[0] != NULL) pass = 0;
    if (g->adjLists[1] != NULL) pass = 0;
    if (getDegree(g,2) != 1 || !hasEdge(g, 2, 3)) pass = 0;
    if (getDegree(g,3) != 1) pass = 0;
    freeGraph(g);
    printf("test_cycle_graph %s\n", pass ? "passed" : "failed"); fflush(stdout);
    return pass;
}

int test_disconnected_graph() {
    Graph* g = createGraph(6);
    addEdge(g,0,1);
    addEdge(g,1,2);
    addEdge(g,3,4);
    simplifyGraph(g);
    int pass = 1;
    if (g->adjLists[1] != NULL) pass = 0;
    if (getDegree(g,0) != 1 || !hasEdge(g, 0, 2)) pass = 0;
    if (getDegree(g,2) != 1) pass = 0;
    if (getDegree(g,3) != 1 || !hasEdge(g, 3, 4)) pass = 0;
    if (getDegree(g,4) != 1) pass = 0;
    if (getDegree(g,5) != 0) pass = 0; 
    freeGraph(g);
    printf("test_disconnected_graph %s\n", pass ? "passed" : "failed"); fflush(stdout);
    return pass;
}

int test_self_loops() {
    Graph* g = createGraph(3);
    addEdge(g,0,0);
    addEdge(g,1,2);
    simplifyGraph(g);
    int pass = 1;
    if(getDegree(g,1)!=1 || getDegree(g,2)!=1) pass=0;
    if(!hasEdge(g,1,2)) pass=0;
    freeGraph(g);
    printf("test_self_loops %s\n", pass ? "passed" : "failed"); fflush(stdout);
    return pass;
}

int test_empty_graph() {
    Graph* g = createGraph(0);
    simplifyGraph(g);
    freeGraph(g);
    printf("test_empty_graph passed\n"); fflush(stdout);
    return 1;
}

int test_single_vertex() {
    Graph* g = createGraph(1);
    simplifyGraph(g);
    freeGraph(g);
    printf("test_single_vertex passed\n"); fflush(stdout);
    return 1;
}

int test_chain_graph() {
    Graph* g = createGraph(5);
    addEdge(g,0,1);
    addEdge(g,1,2);
    addEdge(g,2,3);
    addEdge(g,3,4);
    simplifyGraph(g);
    int pass=1;
    if(!hasEdge(g,0,4) || !hasEdge(g,4,0)) pass=0;
    if(getDegree(g,0)!=1 || getDegree(g,4)!=1) pass=0;
    if(g->adjLists[1]!=NULL || g->adjLists[2]!=NULL || g->adjLists[3]!=NULL) pass=0;
    freeGraph(g);
    printf("test_chain_graph %s\n", pass ? "passed" : "failed"); fflush(stdout);
    return pass;
}

int test_duplicate_edges() {
    Graph* g = createGraph(3);
    addEdge(g,0,1);
    addEdge(g,0,1);
    addEdge(g,1,2);
    simplifyGraph(g);
    int pass=1;
    if(!hasEdge(g,1,2) || !hasEdge(g,2,1)) pass=0;
    if(g->adjLists[0]!=NULL) pass=0;
    if(getDegree(g,1)!=1 || getDegree(g,2)!=1) pass=0;
    freeGraph(g);
    printf("test_duplicate_edges %s\n", pass ? "passed" : "failed"); fflush(stdout);
    return pass;
}

int test_triangle() {
    Graph* g = createGraph(3);
    addEdge(g,0,1);
    addEdge(g,1,2);
    addEdge(g,0,2);
    simplifyGraph(g);
    int pass=1;
    if(!hasEdge(g,1,2) || !hasEdge(g,2,1)) pass=0;
    if(g->adjLists[0]!=NULL) pass=0;
    if(getDegree(g,1)!=1 || getDegree(g,2)!=1) pass=0;
    freeGraph(g);
    printf("test_triangle %s\n", pass ? "passed" : "failed"); fflush(stdout);
    return pass;
}

int main() {
    int passed=0;
    int total=0;

    total++; passed+=test_basic_graph();
    total++; passed+=test_cycle_graph();
    total++; passed+=test_disconnected_graph();
    total++; passed+=test_self_loops();
    total++; passed+=test_empty_graph();
    total++; passed+=test_single_vertex();
    total++; passed+=test_chain_graph();
    total++; passed+=test_duplicate_edges();
    total++; passed+=test_triangle();

    printf("\n%d / %d tests passed.\n", passed, total);
    return (passed==total) ? 0 : 1;
}
