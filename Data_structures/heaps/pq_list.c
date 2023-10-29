#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _node
{
    int priority;
    struct _node *next;
} node;

node *newNode(int p)
{
    node *temp = (node *)malloc(sizeof(node));
    temp->priority = p;
    temp->next = NULL;
    return temp;
}

bool isEmpty(node *head)
{
    return head == NULL;
}

int getMin(node *head) // highest priority ,min element
{
    if (isEmpty(head))
    {
        printf("Empty priority queue!!\n");
        exit(0);
    }
    return head->priority;
}

node *pop(node *head)
{
    if (isEmpty(head))
    {
        printf("Empty priority queue!!\n");
        exit(0);
    }
    node *temp = head;
    head = head->next;
    free(temp);
    return head;
}

node *push(node *head, int p)
{
    node *new_node = newNode(p);
    if (head->priority > p)
    {
        new_node->next = head;
        return new_node;
    }
    else
    {
        node *start = head;
        node *startPrev = head;
        while (p > start->priority)
        {
            if (start->next != NULL)
            {
                startPrev = start;
                start = start->next;
            }
            else
            {
                start->next = new_node;
                return head;
            }
        }
        new_node->next = startPrev->next;
        startPrev->next = new_node;
        return head;
    }
}