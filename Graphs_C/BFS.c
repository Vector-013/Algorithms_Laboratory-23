#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data; // id of the vertex
    struct node *next;

} node;

typedef struct
{
    int front, rear;
    int size;
    node **array;
} Queue;
// --------------------------------------------GRAPH DEFS---------------------------------------------------------
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
    g->adjl = (node **)malloc((vertices + 1) * sizeof(node)); // adjacency list
    g->visit = (int *)malloc((vertices + 1) * sizeof(int));   // array to  check visited or not

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
    newNode->next = g->adjl[src]; // access the latest addition in the adjacency list
    g->adjl[src] = newNode;
}
//-------------------------------------------------QUEUE--------------------------------------------------------------
// A utility function to create a new Queue
Queue *createQueue(int size)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    queue->front = queue->rear = -1;
    queue->size = size;

    queue->array = (node **)malloc(queue->size * sizeof(node *));

    int i;
    for (i = 0; i < size; ++i)
        queue->array[i] = NULL;

    return queue;
}

int isEmpty(Queue *queue)
{
    return queue->front == -1;
}

int isFull(Queue *queue)
{
    return queue->rear == queue->size - 1;
}

int hasOnlyOneItem(Queue *queue)
{
    return queue->front == queue->rear;
}

void Enqueue(node *root, Queue *queue)
{
    if (isFull(queue))
        return;

    queue->array[++queue->rear] = root;

    if (isEmpty(queue))
        ++queue->front;
}

Queue *Dequeue(Queue *queue)
{
    if (isEmpty(queue))
        return NULL;

    node *temp = queue->array[queue->front];

    if (hasOnlyOneItem(queue))
        queue->front = queue->rear = -1;
    else
        ++queue->front;

    return queue;
}

node *getFront(Queue *queue)
{
    return queue->array[queue->front];
}

//---------------------------------------------PRIORITY Q-------------------------------------------------------
#define MAX 1000
int size;
typedef struct
{
    int priority; // dist
    node *vertex;
} heap;
int root()
{
    return 1;
}
int parent(int n)
{
    return n / 2;
}
int lchild(int n)
{
    return 2 * n;
}
int rchild(int n)
{
    return 2 * n + 1;
}
bool has_parent(int n)
{
    return n != root();
}
bool is_node(int n)
{
    return n <= size;
}
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
    return h[root()].priority;
}
void heap_up(heap h[], int n)
{
    while (has_parent(n) && (h[parent(n)].priority > h[n].priority)) // > for min
    {
        swap(&h[parent(n)], &h[n]);
        n = parent(n);
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
    while (is_node(lchild(n)))
    {
        int child = lchild(n);
        if (is_node(rchild(n)) && (h[rchild(n)].priority < h[lchild(n)].priority)) // < for min
            child = rchild(n);

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
    heap_dwn(h, root());
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
        arr[sz - n] = h[root()].priority; // n-1 for descending
        pop(h);
        n--;
    };
}
//---------------------------------------------------------TRAVERSALS---------------------------------------------------------
void BFS(graph *g, node *src, int *dist, int vertices)
{
    dist[src->data] = 0;
    g->visit[src->data] = 1;

    Queue *q = createQueue(vertices + 1);
    Enqueue(src, q);

    node *cur, *child;

    while (!isEmpty(q))
    {
        cur = getFront(q);
        q = Dequeue(q);
        printf("%d\n", cur->data);
        node *cnct = g->adjl[cur->data];
        while (cnct != NULL)
        {
            child = cnct;
            if (g->visit[child->data] != 1)
            {
                g->visit[child->data] = 1;
                dist[child->data] = dist[cur->data] + 1;
                Enqueue(child, q);
            }
            cnct = cnct->next;
        }
    }
}

void DFS(graph *g, node *v)
{
    g->visit[v->data] = 1;
    node *child;
    node *cnct = g->adjl[v->data];

    while (cnct != NULL)
    {
        child = cnct;
        if (g->visit[child->data] != 1)
        {
            DFS(g, child);
        }
        cnct = cnct->next;
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
        scanf("%d %d", &x, &y);
        addEdge(g, x, y);
    }

    int *dist = (int *)malloc((n + 1) * sizeof(int));
    node *source = createNode(1);
    BFS(g, source, dist, n);
}
