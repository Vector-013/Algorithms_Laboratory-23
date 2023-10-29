#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 1000000
int size;

typedef struct
{
    int priority; // add cost
    int PID;
    int d;
    int t;
} node;

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
    while (n != 1 && ((heap[n / 2].priority < heap[n].priority) || (heap[n / 2].priority == heap[n].priority && heap[n].PID < heap[n / 2].PID))) // > for min
    {
        swap(&heap[n / 2], &heap[n]);
        n = n / 2;
    }
}
void push(node heap[], node newer)
{
    if (size == MAX)
    {
        printf("Priority queue is full!!");
        exit(0);
    }
    heap[size + 1] = newer;
    size++;
    heap_up(heap, size);
}
void heap_dwn(node heap[], int n) // logn
{
    while (2 * n <= size)
    {
        int child = 2 * n;
        if (2 * n + 1 <= size && ((heap[2 * n + 1].priority > heap[2 * n].priority) || ((heap[2 * n + 1].priority == heap[2 * n].priority) && heap[2 * n + 1].PID < heap[2 * n].PID))) // < for min
            child = 2 * n + 1;

        if (heap[n].priority < heap[child].priority || heap[n].priority == heap[child].priority && heap[n].PID > heap[child].PID) // > for min
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

void merge(node a[], int start, int mid, int end)
{
    int n1, n2, i, j, k;
    node large;
    n1 = mid - start + 1;
    n2 = end - mid;
    node b[n1 + 1], c[n2 + 1];
    for (i = 0; i < n1; i++)
    {
        b[i] = a[start + i];
    }
    for (i = 0; i < n2; i++)
    {
        c[i] = a[mid + 1 + i];
    }
    large = ((b[n1 - 1].d > c[n2 - 1].d) ? b[n1 - 1] : c[n2 - 1]);
    b[n1] = large;
    c[n2] = large;
    i = 0;
    j = 0;
    for (k = start; k <= end; k++) // main merging step
    {
        if (b[i].d < c[j].d)
        {
            a[k] = b[i];
            i++;
        }
        else
        {
            a[k] = c[j];
            j++;
        }
    }
}
void merge_sort(node a[], int start, int end) // sort by y coordinates
{
    if (start == end)
        return;
    int mid = (start + end) / 2;
    merge_sort(a, mid + 1, end);
    merge_sort(a, start, mid);
    merge(a, start, mid, end);
}

int main()
{
    int N, D;
    scanf("%d%d", &N, &D);
    node f[N];
    for (int i = 0; i < N; i++)
    {
        scanf("%d%d%d%d", &f[i].PID, &f[i].d, &f[i].t, &f[i].priority);
    }
    merge_sort(f, 0, N - 1);
    // for (int i = 0; i < N; i++)
    // {
    //     printf("%d %d %d %d\n", f[i].PID, f[i].d, f[i].t, f[i].priority);
    // }

    node heap[N + 1];
    int ans[D];
    int sz_ans = 0;
    size = 0;
    int ptr = 0;
    for (int i = 1; i <= D; i++)
    {
        while (ptr < N && f[ptr].d == i)
        {
            push(heap, f[ptr]);
            ptr++;
        }

        if (size > 0 && heap[1].t == 0)
            pop(heap);
        // printf("size = %d %d\n", size, heap[1].PID);
        if (size > 0 && heap[1].t > 0)
        {
            heap[1].t--;
            ans[sz_ans] = heap[1].PID;
            sz_ans++;
        }
    }

    int sum = 0;
    for (int i = 1; i <= size; i++)
    {
        sum += (heap[i].t) * (heap[i].priority);
    }
    printf("%d\n", sum);
    for (int i = 0; i < sz_ans; i++)
    {
        printf("%d ", ans[i]);
    }
    printf("\n");
}