#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;

} node;

typedef struct graph
{
    int numV;
    node **adjl; // adjacency list
    int *visit;  // visited
} graph;

node *createNode(int val)
{
    node *newVertex = (node *)malloc(sizeof(node));
    newVertex->data = val;
    newVertex->next = NULL;

    return newVertex;
}

graph *createGraph(int vertices)
{
    graph *g = (graph *)malloc(sizeof(graph *));

    g->numV = vertices;
    g->adjl = (node **)malloc((vertices + 1) * sizeof(node));
    g->visit = (int *)malloc((vertices + 1) * sizeof(int));

    for (int i = 1; i <= vertices; i++)
    {
        g->adjl[i] = NULL;
        g->visit[i] = 0;
    }

    return g;
}

void addEdge(graph *g, int src, int dest)
{
    node *newNode = createNode(dest);
    newNode->next = g->adjl[src];
    g->adjl[src] = newNode;
}