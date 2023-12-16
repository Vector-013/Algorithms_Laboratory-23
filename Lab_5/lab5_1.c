// Ojas Dubey
// 22CS30039
// Machine 78
#include <stdio.h>
#include <stdlib.h>
typedef struct nodep
{
    int data;
    struct nodep *right;
    struct nodep *left;
} node; // tree nodes

typedef struct
{
    int front, back;
    int size;
    node **array;
} Queue; // queue of nodes

node *new_node(int data)
{
    node *newer = (node *)malloc(sizeof(node));
    newer->data = data;
    newer->left = newer->right = NULL;
    return newer;
} // create a new node

Queue *q_init(int size)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));

    queue->front = queue->back = -1;
    queue->size = size;

    queue->array = (node **)malloc((queue->size) * sizeof(node *));
    for (int i = 0; i < size; i++)
        queue->array[i] = NULL;

    return queue;
} // create a new queue

int empty(Queue *queue) // queue functions
{
    if (queue->front == -1)
        return 1;
    return 0;
}

int full(Queue *queue) // queue full
{
    if (queue->back == queue->size - 1)
        return 1;
    return 0;
}

int singlet(Queue *queue) // last item left in the queue
{
    if (queue->front == queue->back)
        return 1;
    return 0;
}

void Enqueue(node *root, Queue *queue) // add a queue element
{
    if (full(queue))
        return;

    queue->array[++queue->back] = root;

    if (empty(queue))
        ++queue->front;
}
node *Dequeue(Queue *queue) // remove element from queue
{
    if (empty(queue))
        return NULL;

    node *temp = queue->array[queue->front];

    if (singlet(queue))
        queue->front = queue->back = -1;
    else
        ++queue->front;

    return temp;
}

node *frontq(Queue *queue) // returns front of a queue
{
    return queue->array[queue->front];
}

int two_child(node *temp) // wether a node has both children
{
    return temp && temp->left && temp->right;
}

void make_tree(node **root, int data, Queue *queue) // insert array into a tree
{
    node *temp = new_node(data);

    if (!*root)
        *root = temp; // if tree empty, put root
    else
    {
        node *front;
        front = frontq(queue); // front element
        while (front->data == -1)
        {
            Dequeue(queue); // if front is null node
            front = frontq(queue);
        }
        if (!front->left)
            front->left = temp;

        else if (!front->right)
            front->right = temp;

        if (two_child(front)) // if both children ,
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
    Enqueue(temp, queue);
}

node *del_min(node *root, int min)
{
    if (root == NULL)
        return NULL;

    if (root->data < min)
    {
        root = del_min(root->right, min);
    }
    else
    {
        root->left = del_min(root->left, min);
    }
    return root;
}

node *del_max(node *root, int max)
{
    if (root == NULL)
        return NULL;

    if (root->data > max)
    {
        root = del_max(root->left, max);
    }
    else
    {
        root->right = del_max(root->right, max);
    }
    return root;
}
void printLevelOrder(node *root) // level ordrr traversal
{
    Queue *queue = q_init(100);
    node *temp = root;
    int a = 0, b = 0;

    while (temp)
    {
        if (!(a && b) && a)
            printf("-1 ");
        printf("%d ", temp->data);
        if (!(a && b) && b)
            printf("-1 ");

        a = 0, b = 0;
        if (temp->left)
            Enqueue(temp->left, queue);
        else
        {
            a = 1;
        }

        if (temp->right)
            Enqueue(temp->right, queue);
        else
        {
            b = 1;
        }

        temp = Dequeue(queue);
    }
}

int main()
{
    int n, min, max;
    printf("input size of arrays(including -1s) : ");
    scanf("%d", &n);
    int a[n];
    printf("give in array of tree :");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    // now we make the tree

    node *root = NULL;
    Queue *queue;
    queue = q_init(100);
    for (int i = 0; i < n; i++)
    {
        make_tree(&root, a[i], queue);
    }
    printf("give min and max : ");
    scanf("%d%d", &min, &max);
    // lnr(root);

    // now root is the tree
    // given tree is a bst

    del_min(root, min);
    del_max(root, max);
    printf("Level order traversal is : ");
    printLevelOrder(root);
    printf("\n");
}