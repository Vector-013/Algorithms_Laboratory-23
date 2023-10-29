#include <stdio.h>
#include <stdlib.h>

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

void print_tree(node *root)
{
    if (root == NULL)
        return;
    print_tree(root->left);
    printf("%d ", root->data);
    print_tree(root->right);
}

int bst(node *root, int val)
{
    if (root == NULL)
        return 0;
    if (root->data == val)
        return 1;
    else if (root->data > val)
        return bst(root->left, val);
    else
        return bst(root->right, val);
    return 0;
}

node *find_rendezvous(node *root, int luk, int lia)
{
    if (root == NULL)
    {
        return NULL;
    }
    node *ans;
    if ((luk > lia && bst(root->right, luk) && bst(root->left, lia)) || (luk < lia && bst(root->right, lia) && bst(root->left, luk)))
        ans = root;
    else if (bst(root->right, luk) && bst(root->right, lia))
        ans = find_rendezvous(root->right, luk, lia);
    else if (bst(root->left, luk) && bst(root->left, lia))
        ans = find_rendezvous(root->left, luk, lia);
    return ans;
}

void lvler(node *root, int lvl)
{
    if (root == NULL)
        return;
    root->lvl = lvl;
    MAXLVL = max(MAXLVL, lvl);
    lvler(root->left, lvl + 1);
    lvler(root->right, lvl + 1);
}

void sum_maker(node *root, int LVLSUM[])
{
    if (root == NULL)
        return;
    LVLSUM[root->lvl] += root->data;
    sum_maker(root->left, LVLSUM);
    sum_maker(root->right, LVLSUM);
}

void parenter(node *root)
{
    if (root == NULL)
        return;
    if (root->left)
        root->left->parent = root;
    if (root->right)
        root->right->parent = root;
    parenter(root->left);
    parenter(root->right);
}

void final(node *root, node *curr, int t, int LVLSUM[])
{
    if (curr == root)
    {
        if (t >= curr->data)
        {
            printf("Escaped! %d\n", curr->data);
            return;
        }
        else
        {
            printf("Trapped!\n");
            return;
        }
    }

    if (t >= LVLSUM[curr->lvl])
    {
        printf("Escaped! %d\n", curr->data);
        return;
    }
    else
    {
        final(root, curr->parent, t, LVLSUM);
        return;
    }
}

void solve()
{
    int n, luk, lia, t;
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &a[i]);
    scanf("%d%d%d", &luk, &lia, &t);
    node *root = NULL;
    Queue *q = createQueue(n);
    for (int i = 0; i < n; i++)
        insert(&root, a[i], q);

    if (!bst(root, luk) || !bst(root, lia))
    {
        printf("-1\n");
        return;
    }

    parenter(root);
    lvler(root, 0);
    int *LVLSUM = (int *)malloc(sizeof(int) * (MAXLVL + 1));
    for (int i = 0; i < MAXLVL + 1; i++)
        LVLSUM[i] = 0;
    sum_maker(root, LVLSUM);

    node *meet = find_rendezvous(root, luk, lia);
    printf("%d %d %d ", meet->data, meet->lvl, LVLSUM[meet->lvl]);

    final(root, meet, t, LVLSUM);
}

int main()
{
    // Read the inputs from stdin and print output to stdout.
    // For creating the tree, initialize a struct node called root.
    // struct node* root = NULL;
    // struct Queue* queue = createQueue(SIZE);
    // insert each element of array into tree by using this: insert(&root, array[i], queue)

    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; i++)
    {
        printf("Case #%d: ", i);
        solve();
    }
}