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

///  STACK ---------------------------------------------------------------------------
typedef struct
{
    int top;
    node *a[MAXLEN];
} stack;

void swap_stack(stack *a, stack *b)
{
    stack temp = *a;
    *a = *b;
    *b = temp;
}

stack init_stack()
{
    stack S;
    S.top = -1;
    return S;
}
int isEmpty_stack(stack S)
{
    if (S.top == -1)
        return 1;
    return 0;
}
int isFull_stack(stack S)
{
    if (S.top == MAXLEN - 1)
        return 1;
    return 0;
}
node *TopStack(stack S)
{
    if (isEmpty_stack(S))
    {
        printf("stack is empty\n");
        return '\0';
    }
    return S.a[S.top];
}
stack push(stack S, node *ch)
{
    if (isFull_stack(S))
    {
        printf("no morem stacks full\n");
        return S;
    }
    ++S.top;
    S.a[S.top] = ch;
    return S;
}
stack pop(stack S)
{
    if (isEmpty_stack(S))
    {
        printf("stacks empty!!\n");
        return S;
    }
    --S.top;
    return S;
}

///   STACK  ------------------------------------------------------------------------------------

// Function to insert a new node in complete binary tree
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

void print_by_lvl(node *root, int n)
{
    Queue *q = createQueue(n);
    Enqueue(root, q);
    int curlvl = -1;

    while (!isEmpty(q))
    {
        node *front = getFront(q);
        if (front->left)
            Enqueue(front->left, q);
        if (front->right)
            Enqueue(front->right, q);
        if (front->lvl != curlvl)
        {
            if (curlvl != -1)
                printf("\n");
            printf("LEVEL %d : ", front->lvl);
            curlvl = front->lvl;
        }
        printf("%d ", front->data);
        Dequeue(q);
    }
}

void print_lvl_2(node *root, int n) // with -1
{
    Queue *q = createQueue(n);
    Enqueue(root, q);
    int curlvl = -1;

    while (!isEmpty(q))
    {
        node *front = getFront(q);
        if (front->data != -1)
        {
            if (front->left)
                Enqueue(front->left, q);
            else
            {
                node *temp = newNode(-1);
                temp->lvl = front->lvl + 1;
                Enqueue(temp, q);
            }
            if (front->right)
                Enqueue(front->right, q);
            else
            {
                node *temp = newNode(-1);
                temp->lvl = front->lvl + 1;
                Enqueue(temp, q);
            }
        }
        if (front->lvl != curlvl)
        {
            if (curlvl != -1)
                printf("\n");
            printf("LEVEL %d : ", front->lvl);
            curlvl = front->lvl;
        }
        printf("%d ", front->data);
        Dequeue(q);
    }
}

void zigzag(node *root, int n)
{
    stack cur = init_stack();
    stack nxt = init_stack();
    cur = push(cur, root);

    int lr = 1;
    int cnt = 0, curlvl = -1;

    while (1)
    {
        if (cnt == n)
            break;
        node *temp = cur.a[cur.top];
        cur = pop(cur);

        if (temp->lvl != curlvl)
        {
            if (curlvl != -1)
                printf("\n");
            printf("LEVEL %d : ", temp->lvl);
            curlvl = temp->lvl;
        }
        printf("%d ", temp->data);
        cnt++;

        if (temp->data != -1)
        {
            if (lr)
            {
                if (temp->left)
                    nxt = push(nxt, temp->left);
                else
                {
                    node *pla = newNode(-1);
                    pla->lvl = temp->lvl + 1;
                    nxt = push(nxt, pla);
                }
                if (temp->right)
                    nxt = push(nxt, temp->right);
                else
                {
                    node *pla = newNode(-1);
                    pla->lvl = temp->lvl + 1;
                    nxt = push(nxt, pla);
                }
            }
            else
            {
                if (temp->right)
                    nxt = push(nxt, temp->right);
                else
                {
                    node *pla = newNode(-1);
                    pla->lvl = temp->lvl + 1;
                    nxt = push(nxt, pla);
                }
                if (temp->left)
                    nxt = push(nxt, temp->left);
                else
                {
                    node *pla = newNode(-1);
                    pla->lvl = temp->lvl + 1;
                    nxt = push(nxt, pla);
                }
            }
        }

        if (isEmpty_stack(cur))
        {
            lr = 1 - lr;
            swap_stack(&cur, &nxt);
        }
    }
}

void find_lvl(node *root, int lvl)
{
    if (root == NULL)
        return;
    root->lvl = lvl;
    find_lvl(root->left, lvl + 1);
    find_lvl(root->right, lvl + 1);
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
    zigzag(root, n);
}

// 13 3 5 7 6 -1 8 9 -1  4 2 1 -1 3
