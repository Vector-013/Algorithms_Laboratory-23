#include <stdio.h>
#include <stdlib.h>

// Weighted Graph Implementation
typedef struct node
{
    int data;
    int weight;
    struct node *next;

} node;

typedef struct graph
{
    int vnum;
    node **adjList;
    int *taken;
    int *posInHeap;
} graph;

node *createNode(int val, int wt);
graph *createGraph(int vertices);
void addEdge(graph *g, int src, int dest, int weight);

// Min-Heap Implementation

typedef struct
{
    int vertex;
    int w;
} pair;

void swap(pair *x, pair *y)
{
    pair tmp = *x;
    *x = *y;
    *y = tmp;
}

int size = 0;
int Root() { return 1; }
int parent(int i) { return i / 2; }
int leftChild(int i) { return 2 * i; }
int rightChild(int i) { return 2 * i + 1; }
int hasParent(int i) { return i != Root(); }
int isValidNode(int i) { return i <= size; }
pair front(pair H[]) { return H[Root()]; }
void shiftUp(pair H[], int idx, graph *g);
void shiftDown(pair H[], int idx, graph *g);
void pop(pair H[], graph *g);
void changePriority(pair H[], pair changePair, graph *g);

// Prim's Algorithm to find MST
const int INF = 1e9;

void process(int v, graph *g, pair *pq)
{
    g->taken[v] = 1;

    node *trav = g->adjList[v];
    int child_v, wt;

    while (trav != NULL)
    {
        child_v = trav->data;
        wt = trav->weight;

        if (g->taken[child_v] == 0)
            changePriority(pq, (pair){child_v, wt}, g);

        trav = trav->next;
    }
}

int prim(graph *g, int n)
{
    int mst_cost = 0;
    pair *pq = (pair *)malloc((n + 1) * sizeof(pair));

    pq[1] = (pair){1, 0};
    g->posInHeap[1] = 1;
    for (int i = 2; i <= n; i++)
    {
        pq[i] = (pair){i, INF};
        g->posInHeap[i] = i;
    }
    size = n;

    pair tmp;
    int v, wt;

    while (size > 0)
    {
        tmp = front(pq);
        v = tmp.vertex, wt = tmp.w;
        pop(pq, g);

        if (wt == INF)
            break;

        mst_cost += wt;
        process(v, g, pq);
    }

    free(pq);
    return mst_cost;
}

int main()
{
    int n, m, i;
    int x, y, wt;

    scanf("%d %d", &n, &m);

    graph *g = createGraph(n);

    for (i = 0; i < m; i++)
    {
        scanf("%d %d %d", &x, &y, &wt);
        addEdge(g, x, y, wt);
        addEdge(g, y, x, wt);
    }

    int mst_cost = prim(g, n);

    for (i = 1; i <= n; i++)
    {
        if (g->taken[i] == 0)
        {
            printf("Spanning Tree not possible");
            return 0;
        }
    }

    printf("%d ", mst_cost);
}

node *createNode(int val, int wt)
{
    node *vertex = (node *)malloc(sizeof(node));
    vertex->data = val;
    vertex->weight = wt;
    vertex->next = NULL;

    return vertex;
}

graph *createGraph(int vertices)
{
    graph *g = (graph *)malloc(sizeof(graph));

    g->vnum = vertices;
    g->adjList = (node **)malloc((vertices + 1) * sizeof(node *));
    g->taken = (int *)malloc((vertices + 1) * sizeof(int));
    g->posInHeap = (int *)malloc((vertices + 1) * sizeof(int));

    int i;
    for (i = 1; i <= vertices; i++)
    {
        g->adjList[i] = NULL;
        g->taken[i] = 0;
        g->posInHeap[i] = 0;
    }

    return g;
}

void addEdge(graph *g, int src, int dest, int weight)
{
    node *newNode = createNode(dest, weight);
    newNode->next = g->adjList[src];
    g->adjList[src] = newNode;
}

void shiftUp(pair H[], int idx, graph *g)
{
    while (hasParent(idx) && (H[parent(idx)].w > H[idx].w))
    {
        swap(&H[parent(idx)], &H[idx]);
        g->posInHeap[H[idx].vertex] = idx;
        g->posInHeap[H[parent(idx)].vertex] = parent(idx);
        idx = parent(idx);
    }
}

void shiftDown(pair H[], int idx, graph *g)
{
    while (isValidNode(leftChild(idx)))
    {
        int child = leftChild(idx);

        if (isValidNode(rightChild(idx)) && H[rightChild(idx)].w < H[leftChild(idx)].w)
            child = rightChild(idx);

        if (H[idx].w > H[child].w)
        {
            swap(&H[idx], &H[child]);
            g->posInHeap[H[idx].vertex] = idx;
            g->posInHeap[H[child].vertex] = child;
        }
        else
            break;

        idx = child;
    }
}

void pop(pair H[], graph *g)
{
    H[Root()] = H[size--];
    g->posInHeap[H[Root()].vertex] = Root();
    shiftDown(H, Root(), g);
}

void changePriority(pair H[], pair changePair, graph *g)
{
    int v = changePair.vertex;
    int newP = changePair.w;
    int idx = g->posInHeap[v];

    if (H[idx].w <= newP)
        return;

    H[idx].w = newP;
    shiftUp(H, idx, g);
}