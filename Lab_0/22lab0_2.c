#include <stdio.h>
#include <stdlib.h>

typedef struct list
{
    int data, row, col;
    struct list *nxtrow;
    struct list *nxtcol;
} node;
typedef node *link;

link create(int key, int r, int c, link ptr)
{
    ptr->data = key;
    ptr->row = r;
    ptr->col = c;
    ptr->nxtcol = NULL;
    ptr->nxtrow = NULL;
    return ptr;
}

int main()
{
    int m, n, a;
    printf("enter row and cols : ");
    scanf("%d %d", &m, &n);
    link rowptr[n], curr;
    link colptr[m];
    link prevcol[m];
    for (int i = 0; i < n; i++)
        rowptr[i] = NULL;
    for (int i = 0; i < m; i++)
    {
        colptr[i] = NULL;
        prevcol[i] = NULL;
    }
    for (int i = 0; i < n; i++)
    {
        rowptr[i] = (link)malloc(sizeof(node));
        link head = rowptr[i];
        link tail;
        int start = -1;
        for (int j = 0; j < m; j++)
        {
            scanf("%d", &a);
            if (a == 0)
                continue;
            else
            {
                start = j;
                break;
            }
        }
        if (start >= 0)
        {
            head = create(a, i, start, head);
            if (prevcol[start] == NULL)
            {
                colptr[start] = head;
                prevcol[start] = head;
            }
            else
            {
                prevcol[start]->nxtrow = head;
                prevcol[start] = head;
            }
            tail = head;
            for (int j = start + 1; j < m; j++)
            {
                scanf("%d", &a);
                if (a == 0)
                    continue;
                else
                {
                    tail->nxtcol = (link)malloc(sizeof(node));
                    tail = tail->nxtcol;
                    tail = create(a, i, j, tail);
                    if (prevcol[j] == NULL)
                    {
                        colptr[j] = tail;
                        prevcol[j] = tail;
                    }
                    else
                    {
                        prevcol[j]->nxtrow = tail;
                        prevcol[j] = tail;
                    }
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (rowptr[i] == NULL)
        {
            for (int j = 0; j < m; j++)
                printf("0 ");
        }
        else
        {
            curr = rowptr[i];
            for (int j = 0; j < m; j++)
            {
                if (j != curr->col)
                    printf("0 ");

                else
                {
                    printf("%d ", curr->data);
                    if (curr->nxtcol != NULL)
                        curr = curr->nxtcol;
                }
            }
        }
        printf("\n");
    }
    for (int i = 0; i < m; i++)
    {
        if (colptr[i] == NULL)
        {
            for (int j = 0; j < n; j++)
                printf("0 ");
        }
        else
        {
            curr = colptr[i];
            for (int j = 0; j < n; j++)
            {
                if (j != curr->row)
                    printf("%dp%d ", curr->row, j);

                else
                {
                    printf("%d ", curr->data);
                    if (curr->nxtrow != NULL)
                        curr = curr->nxtrow;
                }
            }
        }
        printf("\n");
    }
}