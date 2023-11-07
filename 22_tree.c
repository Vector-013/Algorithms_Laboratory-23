#include <stdio.h>
#include <stdlib.h>
#define MAXLEN 100
// For Queue Size
#define SIZE 5000
int MAXLVL = -2e9;

int max(int a, int b)
{
    int ans = (a > b) ? a : b;
    return ans;
}

// A tree node
typedef struct node_
{
    int data;
    int lvl;
    struct node_ *right, *left, *parent;
    int *a;
} node;

// A queue node
typedef struct
{
    int front, rear;
    int size;
    node **array;
} Queue;

// A utility function to create a new tree node
node *newNode(int data)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->data = data;
    temp->left = temp->right = NULL;
    return temp;
}

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

// Standard Queue Functions
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

node *Dequeue(Queue *queue)
{
    if (isEmpty(queue))
        return NULL;

    node *temp = queue->array[queue->front];

    if (hasOnlyOneItem(queue))
        queue->front = queue->rear = -1;
    else
        ++queue->front;

    return temp;
}

node *getFront(Queue *queue)
{
    return queue->array[queue->front];
}

// A utility function to check if a tree node
// has both left and right children
int hasBothChild(node *temp)
{
    return temp && temp->left && temp->right;
}

void insert(node **root, int data, Queue *queue)
{
    // Create a new node for given data
    node *temp = newNode(data);

    // If the tree is empty, initialize the root with new node.
    if (!*root)
        *root = temp;
    else
    {
        // get the front node of the queue.
        node *front;
        front = getFront(queue);
        while (front->data == -1)
        {
            Dequeue(queue);
            front = getFront(queue);
        }
        // If the left child of this front node doesnt exist, set the
        // left child as the new node
        if (!front->left)
            front->left = temp;

        // If the right child of this front node doesnt exist, set the
        // right child as the new node
        else if (!front->right)
            front->right = temp;

        // If the front node has both the left child and right child,
        // Dequeue() it.
        if (hasBothChild(front))
        {
            if (front->left->data == -1)
            {
                front->left = NULL;
            }
            if (front->right->data == -1)
            {
                front->right = NULL;
            }
            Dequeue(queue);
        }
    }

    // Enqueue() the new node for later insertions
    Enqueue(temp, queue);
}

void find_lvl(node *root, int lvl)
{
    if (root == NULL)
        return;
    root->lvl = lvl;
    MAXLVL = max(MAXLVL, lvl);
    find_lvl(root->left, lvl + 1);
    find_lvl(root->right, lvl + 1);
}

void init_arr(node *root)
{
    if (root == NULL)
        return;
    root->a = realloc(root->a, (MAXLVL + 1) * sizeof(int));
    for (int i = 0; i < MAXLVL; i++)
        root->a[i] = 0;
    init_arr(root->left);
    init_arr(root->right);
}

void solve(node *root)
{
    if (root == NULL)
        return;
    if (root->left == NULL && root->right == NULL)
    {
        root->a[0] = 1;
        return;
    }
    solve(root->left);
    solve(root->right);
    for (int i = 0; i < MAXLVL; i++)
    {
        if (root->right)
        {
            if (root->right->a[i] == 1)
            {
                root->a[i + 1] = 1;
            }
        }
        if (root->left)
        {
            if (root->left->a[i] == 1)
            {
                root->a[i + 1] = 1;
            }
        }
    }
}

void printer(node *root, int i)
{
    if (root == NULL)
        return;
    if (root->a[i] == 1)
        printf("%d ", root->data);
    printer(root->left, i);
    printer(root->right, i);
}

int main()
{
    int n;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    node *root = NULL;
    Queue *q = createQueue(n);
    for (int i = 0; i < n; i++)
        insert(&root, a[i], q);

    find_lvl(root, 0);
    init_arr(root);
    solve(root);
    for (int i = 1; i <= MAXLVL; i++)
    {
        printf("LEVEL %d : ", i - 1);
        printer(root, i);
        printf("\n");
    }
}

// 13   10 7 2 11 -1 5 16 -1 17 -1 -1 9 21