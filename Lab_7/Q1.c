#include <stdlib.h>
#include <stdio.h>
#define INF 1e6
#define MAXSIZE 1000

//-----------------------------------------------GRAPH DEFS-------------------------------------------------------------
typedef struct node
{
    int data;
    int wt;
    struct node *next;
} node;
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
    newVertex->wt = wt;

    return newVertex;
}

graph *CreateGraph(int vertices)
{
    graph *g = (graph *)malloc(sizeof(graph));
    g->numV = vertices;
    g->adjl = (node **)malloc((vertices + 1) * sizeof(node *));
    for (int i = 0; i <= vertices; i++)
    {
        g->adjl[i] = NULL;
    }
    return g;
}

void addEdge(graph *g, int src, int dest, int wt)
{
    node *dest_node = createNode(dest, wt);
    dest_node->next = g->adjl[src];
    g->adjl[src] = dest_node;
    return;
}

//-------------------------------------------------QUEUE--------------------------------------------------------------
// A utility function to create a new Queue

typedef struct qnode
{
    int data;
    int cost;
    int deep;

} qnode;
qnode QcreateNode(int cost, int deep, int data)
{
    qnode newQNode;
    newQNode.cost = cost;
    newQNode.deep = deep;
    newQNode.data = data;
    return newQNode;
}
typedef struct queue
{
    int front, rear;
    int size;
    qnode *arr;
} queue;

queue *createQueue(int size)
{
    queue *q = (queue *)malloc(sizeof(queue));

    q->front = -1;
    q->rear = -1;
    q->size = size;
    q->arr = (qnode *)malloc(q->size * sizeof(qnode));
    for (int i = 0; i < size; i++)
        q->arr[i] = QcreateNode(0, 0, 0);

    return q;
}

int Empty(queue *q)
{
    return q->front == -1;
}

int Full(queue *q)
{
    return q->rear == q->size - 1;
}

int singlet(queue *q)
{
    return q->front == q->rear;
}
qnode Front(queue *q)
{
    return q->arr[q->front];
}

void Enqueue(qnode n, queue *q)
{
    if (Full(q))
        return;

    q->arr[++q->rear] = n;

    if (Empty(q))
        ++q->front;
}

void Dequeue(queue *q)
{
    if (Empty(q))
        return;

    if (singlet(q))
        q->front = q->rear = -1;
    else
        ++q->front;
}

//---------------------------------------------PRIORITY Q-------------------------------------------------------//
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
        printf("priority queue IS EMPTY");
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
        printf("Priority queue is full");
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

//---------------------------------------------------------TRAVERSALS-------------------------------------------------------//

int bfs(graph *g, int src, int dest, int maxdeep)
{
    int ans = INF;
    queue *q = createQueue(MAXSIZE);
    qnode nsrc = QcreateNode(0, 0, 0);
    Enqueue(nsrc, q);
    qnode cur, nxt;
    int adj_val, adj_cost, adj_dist;
    while (!Empty(q))
    {
        cur = Front(q);
        Dequeue(q);
        node *cnct = g->adjl[cur.data];
        while (cnct != NULL)
        {
            adj_val = cnct->data;
            if (cur.deep < maxdeep)
            {
                adj_dist = cur.deep + 1;
                adj_cost = cur.cost + cnct->wt;
                if ((adj_val == dest) && (adj_dist == maxdeep) && (adj_cost < ans))
                {
                    ans = adj_cost;
                }
                qnode next_node = QcreateNode(adj_cost, adj_dist, adj_val);
                Enqueue(next_node, q);
            }
            cnct = cnct->next;
        }
    }
    return ans;
}

int main()
{
    int edge_wts[13][3] = {{0, 6, -1}, {0, 1, 5}, {1, 6, 3}, {1, 5, 5}, {1, 2, 7}, {2, 3, 8}, {3, 4, 10}, {5, 2, -1}, {5, 3, 9}, {5, 4, 1}, {6, 5, 2}, {7, 6, 9}, {7, 1, 6}};
    int n = 8, m = 13, x, y, wt;
    int src = 0, dest = 3, maxdeep = 4;

    graph *graph = CreateGraph(n);

    for (int i = 0; i < m; i++)
    {
        addEdge(graph, edge_wts[i][0], edge_wts[i][1], edge_wts[i][2]);
    }

    int req = bfs(graph, src, dest, maxdeep);

    printf("minimum cost of travel is: %d\n", req);
}
