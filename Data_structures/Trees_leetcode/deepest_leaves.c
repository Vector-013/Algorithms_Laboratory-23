#include <stdio.h>
#include <stdlib.h>
typedef struct _node
{
    int data;
    struct _node *left;
    struct _node *right;
} node;

node *new_node(int data)
{
    node *new = (node *)malloc(sizeof(node));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
}
void nlr(node *tree)
{
    if (tree == NULL)
        return;
    printf("%d ", tree->data);
    nlr(tree->left);
    nlr(tree->right);
}
void lnr(node *tree)
{
    if (tree == NULL)
        return;
    nlr(tree->left);
    printf("%d ", tree->data);
    nlr(tree->right);
}
void lrn(node *tree)
{
    if (tree == NULL)
        return;
    nlr(tree->left);
    nlr(tree->right);
    printf("%d ", tree->data);
}
node *search(node *tree, int query)
{
    if (tree->data == query || tree == NULL)
        return tree;
    if (tree->data > query)
        search(tree->left, query);
    else
        search(tree->right, query);
}
node *insert(node *tree, int key)
{
    if (tree == NULL)
        return new_node(key);
    if (key < tree->data)
        tree->left = insert(tree->left, key);
    else if (key > tree->data)
        tree->right = insert(tree->right, key);
    else
        printf("Key is present already !!");
    return tree;
}
void print_tree(node *tree, int lvl)
{
    if (tree == NULL)
        return;
    print_tree(tree->left, lvl + 1);
    printf("%d [%d]", tree->data, lvl);
    print_tree(tree->right, lvl + 1);
}
int get_max(node *tree)
{
    while (tree->right != NULL)
        tree = tree->right;
    return tree->data;
}
int get_min(node *tree)
{
    while (tree->left != NULL)
        tree = tree->left;
    return tree->data;
}
node *get_min_ptr(node *tree)
{
    if (tree->left != NULL)
        return get_min_ptr(tree->left);
    else
        return tree;
}
node *get_max_ptr(node *tree)
{
    if (tree->right != NULL)
        return get_min_ptr(tree->right);
    else
        return tree;
}
node *delete(node *tree, int key)
{
    if (tree == NULL)
        return NULL;
    if (key > tree->data)
        tree->left = delete (tree->left, key);
    else if (key < tree->data)
        tree->right = delete (tree->right, key);
    else
    {
        if ((tree->left == NULL) && (tree->right == NULL))
        {
            free(tree);
            return NULL;
        }
        else if ((tree->left != NULL) && (tree->right == NULL))
        {
            node *temp = tree->right;
            free(tree);
            return temp;
        }
        else if ((tree->left == NULL) && (tree->right != NULL))
        {
            node *temp = tree->left;
            free(tree);
            return temp;
        }
        if ((tree->left != NULL) && (tree->right != NULL))
        {
            node *temp = get_min_ptr(tree->right);
            tree->data = temp->data;
            tree->right = delete (tree->right, temp->data);
        }
    }
    return tree;
}

int main()
{
}