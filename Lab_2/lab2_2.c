#include <stdio.h>
#include <stdlib.h>
int max(int a, int b)
{
    if (a > b)
        return a;
    else
        return b;
}

typedef struct
{
    double x, y; // coordinates
    int idx;     // index in input. need this to print out in correct order
    int dom;     // points dominated
} point;

void merge_y(point a[], int start, int mid, int end)
{
    int n1, n2, i, j, k;
    point large;
    n1 = mid - start + 1;
    n2 = end - mid;
    point b[n1 + 1], c[n2 + 1];
    for (i = 0; i < n1; i++)
    {
        b[i] = a[start + i];
    }
    for (i = 0; i < n2; i++)
    {
        c[i] = a[mid + 1 + i];
    }
    large = ((b[n1 - 1].y > c[n2 - 1].y) ? b[n1 - 1] : c[n2 - 1]);
    b[n1] = large;
    c[n2] = large;
    i = 0;
    j = 0;
    for (k = start; k <= end; k++) // main merging step
    {
        if (b[i].y < c[j].y)
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
void merge_sort_y(point a[], int start, int end) // sort by y coordinates
{
    if (start == end)
        return;
    int mid = (start + end) / 2;
    merge_sort_y(a, mid + 1, end);
    merge_sort_y(a, start, mid);
    merge_y(a, start, mid, end);
}

void merge_x(point a[], int start, int mid, int end, int cnt[])
{
    int n1, n2, i, j, k;
    point large;
    n1 = mid - start + 1;
    n2 = end - mid;
    point b[n1 + 1], c[n2 + 1];
    for (i = 0; i < n1; i++)
    {
        b[i] = a[start + i];
    }
    for (i = 0; i < n2; i++)
    {
        c[i] = a[mid + 1 + i];
    }

    int j = 0;

    for (int i = 0; i < n1; i++) /* COUNT INVERSIONS HERE
                                         use this to count x dominted by each point in right array.

                                     only elements in right array can dominate those in left as y sorted initially.*/

        cnt[a[mid + 1].idx] += j; // add dominate for first element in right array. add over preexisting domination count in recursion

    for (int i = 1; i < n2; i++)
    {
        }
    large = ((b[n1 - 1].x > c[n2 - 1].x) ? b[n1 - 1] : c[n2 - 1]);
    b[n1] = large;
    c[n2] = large;
    i = 0;
    j = 0;
    for (k = start; k <= end; k++) // main merging step
    {
        if (b[i].x > c[j].x)
        {
            // cnt[a[mid + 1 + j].idx] += (n1 - i + 1);
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
void merge_sort_x(point a[], int start, int end, int cnt[]) // sort by x coordinates
{
    if (start == end)
        return;
    int mid = (start + end) / 2;
    merge_sort_x(a, mid + 1, end, cnt);
    merge_sort_x(a, start, mid, cnt);
    merge_x(a, start, mid, end, cnt);
}

int main()
{
    int n, i = 0;
    scanf("%d", &n);
    point a[n];
    printf("original points, input x y coordinates with a space :\n");
    for (i = 0; i < n; i++)
    {
        scanf("%lf %lf", &a[i].x, &a[i].y);
        a[i].idx = i;
        a[i].dom = 0;
    }

    int *cnt = (int *)calloc(n, sizeof(int));
    merge_sort_y(a, 0, n - 1);
    // for (i = 0; i < n; i++)
    // {
    //     printf("%lf %lf %d %d\n", a[i].x, a[i].y, a[i].idx, a[i].dom);
    // }

    // printf("\n");

    merge_sort_x(a, 0, n - 1, cnt);
    // for (i = 0; i < n; i++)
    // {
    //     printf("%lf %lf %d %d\n", a[i].x, a[i].y, a[i].idx, a[i].dom);
    // }
    // printf("\n");

    for (int i = 0; i < n; i++)
    {
        printf("%d ", cnt[i]);
    }
    printf("\n");
}