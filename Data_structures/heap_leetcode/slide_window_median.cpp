#include <iostream>
#include <vector>
using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 1000
int sz;
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
    return n <= sz;
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
int get_min(int heap[])
{
    if (sz == 0)
    {
        printf("Empty priority queue!!");
        exit(0);
    }
    return heap[root()];
}
void heap_up(int heap[], int n)
{
    while (has_parent(n) && (heap[parent(n)] > heap[n]))
    {
        swap(&heap[parent(n)], &heap[n]);
        n = parent(n);
    }
}
void push(int heap[], int new_int)
{
    if (sz == MAX)
    {
        printf("Priority queue is full!!");
        exit(0);
    }
    heap[sz + 1] = new_int;
    sz++;
    heap_up(heap, sz);
}
void heap_dwn(int heap[], int n) // logn
{
    while (is_node(lchild(n)))
    {
        int child = lchild(n);
        if (is_node(rchild(n)) && (heap[rchild(n)] < heap[lchild(n)]))
            child = rchild(n);

        if (heap[n] > heap[child])
            swap(&heap[n], &heap[child]);
        else
            break;
        n = child;
    }
}
void pop(int heap[]) // log n
{
    if (sz == 0)
    {
        printf("Empty priority queue!!");
        exit(0);
    }
    heap[root()] = heap[sz]; // maintain complete tree
    sz--;
    heap_dwn(heap, root());
}
void build_heap(int arr[], int heap[], int n) // n
{
    for (int i = 0; i < n; i++)
        heap[i + 1] = arr[i];
    sz = n;
    for (int i = sz / 2; i >= 1; i--)
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
class Solution
{
public:
    double report_median(int heap[], vector<int> &nums, int s) {}
    vector<double> medianSlidingWindow(vector<int> &nums, int k)
    {
        int s = 0;
        int heap[k + 2];
        int arr[k];
        for (int i = 0; i < k; i++)
            arr[i] = nums[i];
        build_heap(arr, heap, k);
    }
};