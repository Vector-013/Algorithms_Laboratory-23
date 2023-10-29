#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 1000
int size;
typedef struct
{
    int priority;
    int i;
    int j;
} node;
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
    return n != 1;
}
bool is_node(int n)
{
    return n <= size;
}
void swap(node *a, node *b)
{
    node temp = *a;
    *a = *b;
    *b = temp;
}
int get_min(node heap[])
{
    if (size == 0)
    {
        printf("Empty priority queue!!");
        exit(0);
    }
    return heap[1].priority;
}
void heap_up(node heap[], int n)
{
    while (has_parent(n) && (heap[parent(n)].priority > heap[n].priority)) // > for min
    {
        swap(&heap[parent(n)], &heap[n]);
        n = parent(n);
    }
}
void push(node heap[], node new_node)
{
    if (size == MAX)
    {
        printf("Priority queue is full!!");
        exit(0);
    }
    heap[size + 1] = new_node;
    size++;
    heap_up(heap, size);
}
void heap_dwn(node heap[], int n) // logn
{
    while (is_node(lchild(n)))
    {
        int child = lchild(n);                                                           // index of left child
        if (is_node(rchild(n)) && (heap[rchild(n)].priority < heap[lchild(n)].priority)) // < for min
            child = rchild(n);

        if (heap[n].priority > heap[child].priority) // > for min
            swap(&heap[n], &heap[child]);
        else
            break;
        n = child;
    }
}
void pop(node heap[]) // log n
{
    if (size == 0)
    {
        printf("Empty priority queue!!");
        exit(0);
    }
    heap[1] = heap[size]; // maintain complete tree
    size--;
    heap_dwn(heap, 1);
}
void build_heap(int arr[], node heap[], int n) // n
{
    for (int i = 0; i < n; i++)
        heap[i + 1].priority = arr[i];
    size = n;
    for (int i = size / 2; i >= 1; i--)
        heap_dwn(heap, i);
}
void heap_sort(int arr[], int n) // nlogn
{
    node temp_heap[MAX + 1];
    int sz = n;
    build_heap(arr, temp_heap, n);
    while (n)
    {
        arr[sz - n] = temp_heap[1].priority; // n-1 for descending
        pop(temp_heap);
        n--;
    };
}

int main()
{
    int a[64] = {647, 225, 200, 820, 789, 338, 72, 274, 407, 577, 306, 167, 928, 40, 417, 86, 751, 384, 697, 144, 137, 823, 241, 986, 665, 468, 225, 121, 372, 143, 86, 737, 86, 4, 557, 874, 341, 628, 148, 748, 923, 173, 633, 852, 212, 50, 656, 681, 153, 353, 824, 8, 176, 783, 993, 559, 970, 936, 399, 61, 797, 203, 797, 882};
    int b[60] = {206, 354, 757, 547, 700, 623, 14, 623, 514, 646, 194, 444, 414, 849, 125, 566, 202, 948, 292, 96,
                 732, 285, 374, 702, 940, 772, 762, 737, 974, 559, 620, 898, 631, 96, 445, 331, 437, 177, 672, 951,
                 822, 866, 395, 955, 715, 520, 240, 636, 187, 532, 731, 637, 535, 823, 339, 475, 314, 819, 931, 7};
    int m, n;
    int k = 10;
    heap_sort(a, 64);
    heap_sort(b, 60);

    for (int i = 0; i < 64; i++)
        printf("%d ", a[i]);
    printf("\n");
    for (int i = 0; i < 60; i++)
        printf("%d ", b[i]);

    size = 0;
    node heap[MAX];
    int check[64][60];
    for (int i = 0; i < 64; i++)
        for (int j = 0; j < 60; j++)
            check[i][j] = 0;
    node z = {a[0] + b[0], 0, 0};
    check[0][0] = 1;
    push(heap, z);
    node push1, push2;
    while (k--)
    {
        int x = heap[1].i;
        int y = heap[1].j;
        push1.priority = a[x + 1] + b[y];
        push1.i = x + 1;
        push1.j = y;
        push2.priority = a[x] + b[y + 1];
        push2.i = x;
        push2.j = y + 1;
        printf("%d %d %d\n", heap[1].priority, heap[1].i, heap[1].j);
        pop(heap);
        if (check[x + 1][y] == 0)
        {
            push(heap, push1);
            check[x + 1][y] = 1;
        }
        if (check[x][y + 1] == 0)
        {
            push(heap, push2);
            check[x][y + 1] = 1;
        }
    }
}