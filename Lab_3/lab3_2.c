#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 100

typedef struct
{
    int top;
    int a[MAXLEN];
} stack;

stack init_stack()
{
    stack S;
    S.top = -1;
    return S;
}
int isEmpty(stack S)
{
    if (S.top == -1)
        return 1;
    return 0;
}
int isFull(stack S)
{
    if (S.top == MAXLEN - 1)
        return 1;
    return 0;
}
char TopStack(stack S)
{
    if (isEmpty(S))
    {
        printf("stack is empty\n");
        return '\0';
    }
    return S.a[S.top];
}
stack push(stack S, char ch)
{
    if (isFull(S))
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
    if (isEmpty(S))
    {
        printf("stacks empty!!\n");
        return S;
    }
    --S.top;
    return S;
}
void print(stack S)
{
    int i;
    for (i = S.top; i >= 0; i--)
        printf("%c", S.a[i]);
    printf("\n");
}
int get_min(char *c, int s, int n)
{
    int z = s;
    for (int i = s; i < n; i++)
    {
        if (c[i] < c[z])
            z = i;
    }
    return z;
}

int main()
{
    int n;
    printf("intput size of string and string : ");
    scanf("%d", &n);
    char *s = (char *)malloc((sizeof(char)) * n);
    scanf("%s", s);
    stack r = init_stack();
    int ptr = 0;
    int mini = get_min(s, ptr, n);
    for (int i = ptr; i <= mini; i++)
    {
        r = push(r, s[i]);
        ptr++;
    }
    while (ptr < n)
    {
        mini = get_min(s, ptr, n);
        while (!isEmpty(r) && (TopStack(r) <= s[mini]))
        {
            printf("%c", TopStack(r));
            r = pop(r);
        }
        for (int i = ptr; i <= mini; i++)
        {
            r = push(r, s[i]);
            ptr++;
        }
    }
    print(r);
}