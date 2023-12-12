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
    int *array;
} Queue;

void reverse_arr(int *arr, int n)
{
    int i = 0, j = n - 1, t;

    while (i < j)
    {
        t = arr[i];
        arr[i] = arr[j];
        arr[j] = t;
        i++;
        j--;
    }
}

// --------------------------------------------GRAPH DEFS---------------------------------------------------------
typedef struct graph
{
    int numV;
    node **adjl; // adjacency list
    int *visit;  // visited
    int *previd;
} graph;

node *createNode(int value)
{
    node *Vertex = (node *)malloc(sizeof(node));
    Vertex->data = value;
    Vertex->next = NULL;

    return Vertex;
}

graph *createGraph(int vertices)
{
    graph *g = (graph *)malloc(sizeof(graph));

    g->numV = vertices;
    g->adjl = (node **)malloc((vertices + 1) * sizeof(node *)); // adjacency list
    g->visit = (int *)malloc((vertices + 1) * sizeof(int));     // array to  check visited or not
    g->previd = (int *)malloc((vertices + 1) * sizeof(int));

    for (int i = 0; i < vertices; i++)
    {
        g->adjl[i] = NULL;
        g->visit[i] = 0;
        g->previd[i] = 0;
    }

    return g;
}

void addEdge(graph *g, int src, int dest)
{
    node *newNode = createNode(dest);
    newNode->next = g->adjl[src]; // access the latest addition in the adjacency list
    g->adjl[src] = newNode;
    g->previd[dest]++;
}

//-------------------------------------------------QUEUE--------------------------------------------------------------
// A utility function to create a new Queue
Queue *createQueue(int size)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    queue->front = queue->rear = -1;
    queue->size = size;

    queue->array = (int *)malloc(queue->size * sizeof(int));

    int i;
    for (i = 0; i < size; ++i)
        queue->array[i] = 0;

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

void Enqueue(int root, Queue *queue)
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

    int temp = queue->array[queue->front];

    if (hasOnlyOneItem(queue))
        queue->front = queue->rear = -1;
    else
        ++queue->front;

    return queue;
}

int getFront(Queue *queue)
{
    return queue->array[queue->front];
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

//---------------------------------------------------------TRAVERSALS-------------------------------------------------------//
void BFS(graph *g, int src, int *dist, int vertices)
{
    dist[src] = 0;
    g->visit[src] = 1;

    Queue *q = createQueue(vertices + 1);
    Enqueue(src, q);

    int cur, child;

    while (!isEmpty(q))
    {
        cur = getFront(q);
        q = Dequeue(q);
        printf("%d\n", cur);
        node *cnct = g->adjl[cur];
        while (cnct != NULL)
        {
            child = cnct->data;
            if (g->visit[child] != 1)
            {
                g->visit[child] = 1;
                dist[child] = dist[cur] + 1;
                Enqueue(child, q);
            }
            cnct = cnct->next;
        }
    }
}

void DFS(graph *g, int v)
{
    g->visit[v] = 1;
    int child;
    node *cnct = g->adjl[v];
    printf("%d\n", v);
    while (cnct != NULL)
    {
        child = cnct->data;
        if (g->visit[child] != 1)
        {
            DFS(g, child);
        }
        cnct = cnct->next;
    }
}

void topological(graph *g, int *order, int vertices)
{
    Queue *Q = createQueue(vertices + 1);
    for (int i = 0; i < g->numV; i++) // add all courses with no pre requisites
    {
        if (g->previd[i] == 0)
        {
            Enqueue(i, Q);
        }
    }
    int cur, nxt, pos = 0;
    while (!isEmpty(Q))
    {
        cur = getFront(Q);
        Q = Dequeue(Q);
        order[pos++] = cur;
        node *cnct = g->adjl[cur];
        while (cnct != NULL)
        {
            nxt = cnct->data;
            g->previd[nxt]--;
            if (g->previd[nxt] == 0)
            {
                Enqueue(nxt, Q);
            }
            cnct = cnct->next;
        }
    }
}

//-----------------------------------------------------------------------------------------------------------//

int main()
{
    int n, m, x, y;
    printf("Give number of vertices and edges , respectively : "); // user inpiut
    scanf("%d %d", &n, &m);

    graph *g = createGraph(n);

    printf("enter edges in form : SOURCE DESTINATION\n"); // input edges
    for (int i = 0; i < m; i++)
    {
        scanf("%d %d", &x, &y);
        addEdge(g, x, y);
    }
    int *order = (int *)malloc((n + 1) * sizeof(int));
    for (int i = 0; i <= n; i++)
    {
        order[i] = -1;
    }

    topological(g, order, n); // main function to perform topological and check loops

    int boolean = 0; // bool to check

    for (int i = 0; i < n; i++)
    {
        if (order[i] == -1)
        {
            boolean = 1;
            break;
        }
    }

    if (!boolean)
    {
        printf("TRUE\n");
        printf("course ordering is : ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", order[i]);
        }
        printf("\n");
    }
    else
    {
        printf("FALSE\n");
    }
}

/*
8 8
1 2
8 2
2 3
3 7
4 5
3 4
3 6
6 5
*/
