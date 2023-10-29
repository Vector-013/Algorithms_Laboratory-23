#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 1000
int size;
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
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int get_min(int heap[])
{
    if (size == 0)
    {
        printf("Empty priority queue!!");
        exit(0);
    }
    return heap[root()];
}
void heap_up(int heap[], int n)
{
    while (has_parent(n) && (heap[parent(n)] < heap[n])) // > for min
    {
        swap(&heap[parent(n)], &heap[n]);
        n = parent(n);
    }
}
void push(int heap[], int new_int)
{
    if (size == MAX)
    {
        printf("Priority queue is full!!");
        exit(0);
    }
    heap[size + 1] = new_int;
    size++;
    heap_up(heap, size);
}
void heap_dwn(int heap[], int n) // logn
{
    while (is_node(lchild(n)))
    {
        int child = lchild(n);
        if (is_node(rchild(n)) && (heap[rchild(n)] > heap[lchild(n)])) // < for min
            child = rchild(n);

        if (heap[n] < heap[child]) // > for min
            swap(&heap[n], &heap[child]);
        else
            break;
        n = child;
    }
}
void pop(int heap[]) // log n
{
    if (size == 0)
    {
        printf("Empty priority queue!!");
        exit(0);
    }
    heap[root()] = heap[size]; // maintain complete tree
    size--;
    heap_dwn(heap, root());
}
void build_heap(int arr[], int heap[], int n) // n
{
    for (int i = 0; i < n; i++)
        heap[i + 1] = arr[i];
    size = n;
    for (int i = size / 2; i >= 1; i--)
        heap_dwn(heap, i);
}
void heap_sort(int arr[], int n) // nlogn
{
    int temp_heap[MAX + 1];
    int sz = n;
    build_heap(arr, temp_heap, n);
    while (n)
    {
        arr[sz - n] = temp_heap[root()]; // n-1 for descending
        pop(temp_heap);
        n--;
    };
}

int main()
{
    int n, k, sum = 0, eat = 0;
    int container[n], heap[n + 1];
    scanf("%d%d", &n, &k);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &container[i]);
        sum += container[i];
    }
    build_heap(container, heap, n);
    while (heap[root()] && k--)
    {
        eat += heap[root()] / 2;
        heap[root()] -= heap[root()] / 2;
        heap_dwn(heap, root());
    }
    printf("ans = %d\n", sum - eat);
}