#include <stdlib.h>
#include <stdio.h>
#define SIZE 100
int hsize = 0;
int cnt;
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
    int *visited, *enter;
    vertex **adj;
} graph;

graph *make_graph(int size)
{
    graph *temp = (graph *)malloc(sizeof(graph));
    temp->gsize = size;
    temp->visited = (int *)malloc((size) * sizeof(int));
    temp->adj = (vertex **)malloc((size) * sizeof(vertex *));
    temp->enter = (int *)malloc((size) * (sizeof(int)));

    int i;
    for (i = 0; i < size; i++)
    {
        temp->visited[i] = 0;
        temp->adj[i] = NULL;
        temp->enter[i] = 0;
    }
    return temp;
}

void add_edge(graph *graph, int src, int dest)
{
    vertex *vnew = make_vertex(dest);
    vnew->next = graph->adj[src];
    graph->adj[src] = vnew;
    graph->enter[dest]++;
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

int check(int v, int *visit,
          int *path, graph *graph)
{
    if (visit[v] == 0)
    {
        visit[v] = 1;
        path[v] = 1;
        vertex *vnext = graph->adj[v];
        while (vnext != NULL)
        {
            if (visit[vnext->val] == 0 && check(vnext->val, visit, path, graph))
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
        if (visit[i] == 0 && check(i, visit, path, graph))
            return 1;

    return 0;
}
void reverse(int *arr, int n)
{
    int i = 0, j = n - 1, temp;

    while (i < j)
    {
        temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
        i++;
        j--;
    }
}
void topo_kahn(graph *graph, int *ans)
{
    if (isCyclic(graph))
    {
        printf("\ncycle-invalid\n");
        return;
    }

    queue *Q = createQueue(SIZE);
    int i;

    int idx = 0;

    for (i = 1; i <= graph->gsize; i++)
    {
        if (graph->enter[i] == 0)
        {
            enqueue(i, Q);
        }
    }

    int curr_val, next_val;
    while (!isEmpty(Q))
    {
        curr_val = getFront(Q);
        dequeue(Q);
        ans[idx++] = curr_val;
        // printf("%d\n", curr_val);
        vertex *vnext = graph->adj[curr_val];
        while (vnext != NULL)
        {
            next_val = vnext->val;
            graph->enter[next_val]--;
            if (graph->enter[next_val] == 0)
            {
                enqueue(next_val, Q);
            }
            vnext = vnext->next;
        }
    }
}
void dfs(graph *graph, int src, int *ans)
{
    // printf("%d\n", src);
    graph->visited[src] = 1;
    vertex *vnext = graph->adj[src];
    while (vnext != NULL)
    {
        if (graph->visited[vnext->val] != 1)
        {
            dfs(graph, vnext->val, ans);
        }
        vnext = vnext->next;
    }
    ans[cnt++] = src;
}
void topo_dfs(graph *graph, int *ans)
{
    if (isCyclic(graph))
    {
        printf("\ncycle-invalid\n");
        return;
    }

    int i, cnt = 0;
    for (i = 1; i <= graph->gsize; i++)
        graph->visited[i] = 0;

    for (i = 1; i <= graph->gsize; i++)
    {
        if (graph->visited[i] == 0)
            dfs(graph, i, ans);
    }
    reverse(ans, graph->gsize);
}

int main()
{
    int v, e, i, x, y;

    scanf("%d %d", &v, &e);

    graph *graph = make_graph(v);

    for (i = 0; i < e; i++)
    {
        scanf("%d %d", &x, &y);
        add_edge(graph, x, y); // src defeats dest
    }

    int *ans = (int *)malloc((v + 1) * sizeof(int));
    // topo_kahn(graph, ans);
    topo_dfs(graph, ans);

    for (i = 0; i < v; i++)
    {
        printf("%d ", ans[i]);
    }
}
