#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data; // id of the vertex
    struct node *next;
    int wt;
} node;

typedef struct
{
    int front, rear;
    int size;
    int *array;
} Queue;
// --------------------------------------------GRAPH DEFS---------------------------------------------------------
typedef struct graph
{
    int numV;
    node **adjl; // adjacency list
    int *visit;  // visited
} graph;

node *createNode(int val, int wt)
{
    node *newVertex = (node *)malloc(sizeof(node));
    newVertex->data = val;
    newVertex->next = NULL;

    return newVertex;
}

graph *createGraph(int vertices)
{
    graph *g = (graph *)malloc(sizeof(graph));

    g->numV = vertices;
    g->adjl = (node **)malloc((vertices + 1) * sizeof(node *)); // adjacency list
    g->visit = (int *)malloc((vertices + 1) * sizeof(int));     // array to  check visited or not

    for (int i = 1; i <= vertices; i++)
    {
        g->adjl[i] = NULL;
        g->visit[i] = 0;
    }

    return g;
}

void addEdge(graph *g, int src, int dest, int wt)
{
    node *newNode = createNode(dest, wt);
    newNode->next = g->adjl[src];
    g->adjl[src] = newNode;
}

//---------------------------------------------PRIORITY Q-------------------------------------------------------
#define MAX 1000
int size;
typedef struct
{
    int priority; // dist
    int vertex;
} heap;
void swap(heap *a, heap *b)
{
    heap temp = *a;
    *a = *b;
    *b = temp;
}
int get_min(heap h[])
{
    if (size == 0)
    {
        printf("Empty priority queue!!");
        exit(0);
    }
    return h[1].priority;
}
void heap_up(heap h[], int n)
{
    while (n != 1 && (h[n / 2].priority > h[n].priority)) // > for min
    {
        swap(&h[n / 2], &h[n]);
        n = n / 2;
    }
}
void push(heap h[], heap new_element)
{
    if (size == MAX)
    {
        printf("Priority queue is full!!");
        exit(0);
    }
    h[size + 1] = new_element;
    size++;
    heap_up(h, size);
}
void heap_dwn(heap h[], int n) // logn
{
    while (2 * n <= size)
    {
        int child = 2 * n;
        if (2 * n + 1 <= size && (h[2 * n + 1].priority < h[2 * n].priority)) // < for min
            child = 2 * n + 1;

        if (h[n].priority > h[child].priority) // > for min
            swap(&h[n], &h[child]);
        else
            break;
        n = child;
    }
}
void pop(heap h[]) // log n
{
    if (size == 0)
    {
        printf("Empty priority queue!!");
        exit(0);
    }
    h[1] = h[size]; // maintain complete tree
    size--;
    heap_dwn(h, 1);
}
void build_heap(int arr[], heap h[], int n) // n
{
    for (int i = 0; i < n; i++)
        h[i + 1].priority = arr[i];
    size = n;
    for (int i = size / 2; i >= 1; i--)
        heap_dwn(h, i);
}
void heap_sort(int arr[], int n) // nlogn
{
    heap h[MAX + 1];
    int sz = n;
    build_heap(arr, h, n);
    while (n)
    {
        arr[sz - n] = h[1].priority; // n-1 for descending
        pop(h);
        n--;
    };
}

//---------------------------------------------------------TRAVERSALS---------------------------------------------------------

void dijkstra(graph *g, int src, int *dist, int n)
{
    for (int i = 1; i <= n; i++)
        dist[i] = 1e9;

    heap *pq = (heap *)malloc((n + 1) * sizeof(heap));
    size = 0;
    heap src_h = {0, src};
    dist[src] = 0;
    push(pq, src_h);
    heap cur, next_v;
    node *cnct;

    while (size > 0)
    {
        cur = pq[1];
        pop(pq);

        if (g->visit[cur.vertex] == 1)
            continue;
        g->visit[cur.vertex] = 1;
        cnct = g->adjl[cur.vertex];

        while (cnct != NULL)
        {
            if (cur.priority + cnct->wt < dist[cnct->data])
            {
                dist[cnct->data] = cur.priority + cnct->wt;
                next_v = (heap){dist[cnct->data], cnct->data};
                push(pq, next_v);
            }
            cnct = cnct->next;
        }
    }
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
    }

    int *dist = (int *)malloc((n + 1) * sizeof(int));
    node *source = createNode(1, 0);
    dijkstra(g, source->data, dist, n);

    for (i = 1; i <= n; i++)
    {
        printf("%d ", dist[i]);
    }
}