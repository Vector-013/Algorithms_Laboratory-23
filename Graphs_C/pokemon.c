#include <stdlib.h>
#include <stdio.h>
#define SIZE 100
int hsize = 0;
int cnt = 0;
typedef struct vertex
{
    int val;
    struct vertex *next;
} vertex;

vertex *make_vertex(int val)
{
    vertex *temp = (vertex *)malloc(sizeof(vertex));
    temp->val = val;
    temp->next = NULL;
    return temp;
}

typedef struct graph
{
    int gsize;
    int *visited;
    vertex **adj;
} graph;

graph *make_graph(int size)
{
    graph *temp = (graph *)malloc(sizeof(graph));
    temp->gsize = size;
    temp->visited = (int *)malloc((size) * sizeof(int));
    temp->adj = (vertex **)malloc((size) * sizeof(vertex *));
    int i;
    for (i = 0; i < size; i++)
    {
        temp->visited[i] = 0;
        temp->adj[i] = NULL;
    }
    return temp;
}

void add_edge(graph *graph, int src, int dest)
{
    vertex *vnew = make_vertex(dest);
    vnew->next = graph->adj[src];
    graph->adj[src] = vnew;
}
typedef struct queue
{
    int front, rear;
    int size;
    int *array;
} queue;

queue *createQueue(int size)
{
    queue *Q = (queue *)malloc(sizeof(queue));

    Q->front = Q->rear = -1;
    Q->size = size;

    Q->array = (int *)malloc(Q->size * sizeof(int));

    int i;
    for (i = 0; i < size; ++i)
        Q->array[i] = 0;

    return Q;
}

int isEmpty(queue *Q)
{
    return Q->front == -1;
}

int isFull(queue *Q)
{
    return Q->rear == Q->size - 1;
}

int hasOnlyOneItem(queue *Q)
{
    return Q->front == Q->rear;
}

void enqueue(int n, queue *Q)
{
    if (isFull(Q))
        return;

    Q->array[++Q->rear] = n;

    if (isEmpty(Q))
        ++Q->front;
}

void dequeue(queue *Q)
{
    if (isEmpty(Q))
        return;

    if (hasOnlyOneItem(Q))
        Q->front = Q->rear = -1;
    else
        ++Q->front;
}

int getFront(queue *Q)
{
    return Q->array[Q->front];
}

void bfs(graph *graph, int src, int *opp)
{
    graph->visited[src] = 1;
    queue *Q = createQueue(SIZE);
    enqueue(src, Q);
    while (!isEmpty(Q))
    {
        int curr_val = getFront(Q);
        opp[cnt++] = curr_val;
        dequeue(Q);
        vertex *vnext = graph->adj[curr_val];
        while (vnext != NULL)
        {
            if (graph->visited[vnext->val] != 1)
            {
                graph->visited[vnext->val] = 1;
                enqueue(vnext->val, Q);
            }
            vnext = vnext->next;
        }
    }
}

int dfs(int v, int *visit,
        int *path, graph *graph)
{
    if (visit[v] == 0)
    {
        visit[v] = 1;
        path[v] = 1;
        vertex *vnext = graph->adj[v];
        while (vnext != NULL)
        {
            if (visit[vnext->val] == 0 && dfs(vnext->val, visit, path, graph))
                return 1;
            else if (path[vnext->val])
                return 1;
            vnext = vnext->next;
        }
    }
    path[v] = 0;
    return 0;
}

int isCyclic(graph *graph)
{
    int *visit = (int *)malloc((graph->gsize) * sizeof(int));
    int *path = (int *)malloc((graph->gsize) * sizeof(int));
    for (int i = 0; i < graph->gsize; i++)
    {
        visit[i] = 0;
        path[i] = 0;
    }

    for (int i = 0; i < graph->gsize; i++)
        if (visit[i] == 0 && dfs(i, visit, path, graph))
            return 1;

    return 0;
}
int main()
{
    int v, e, i, x, y, wt;

    scanf("%d %d", &v, &e);

    graph *graph = make_graph(v);

    for (i = 0; i < e; i++)
    {
        scanf("%d %d", &x, &y);
        add_edge(graph, y, x); // src defeats dest
    }
    if (isCyclic(graph))
    {
        printf("unconquerable\n");
        return 0;
    }
    int *opp = (int *)malloc((v) * sizeof(int));
    for (i = 0; i < v; i++)
    {
        if (graph->visited[i] != 0)
            continue;
        bfs(graph, i, opp);
    }
    for (i = v - 1; i >= 0; i--)
    {
        printf("%d ", opp[i]);
    }
}

// 4 4 1 0 2 0 3 1 3 2