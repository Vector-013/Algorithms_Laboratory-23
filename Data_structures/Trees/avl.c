#include <stdio.h>
#include <stdlib.h>
// int max(int a, int b)
// {
//     int ans = (a > b) ? a : b;
//     return ans;
// }
typedef struct _node
{
    int data;
    int height;
    struct _node *left;
    struct _node *right;
} node;

node *new_node(int data)
{
    node *new = (node *)malloc(sizeof(node));
    new->data = data;
    new->height = 0;
    new->left = NULL;
    new->right = NULL;
}
int get_height(node *avl)
{
    if (avl == NULL)
        return -1;
    return avl->height;
}

node *right_rotate(node *prt)
{
    node *chd = prt->left;
    prt->left = chd->right;
    prt->height = 1 + max(get_height(prt->left), get_height(prt->right));
    chd->right = prt;
    chd->height = 1 + max(get_height(chd->left), get_height(chd->right));
    prt = chd;
    return prt;
}
node *left_rotate(node *prt)
{
    node *chd = prt->right;
    prt->right = chd->left;
    prt->height = 1 + max(get_height(prt->right), get_height(prt->left));
    chd->left = prt;
    chd->height = 1 + max(get_height(chd->right), get_height(chd->left));
    prt = chd;
    return prt;
}
node *retrace(node *avl)
{
    if (avl == NULL)
        return avl;
    if (get_height(avl->left) - get_heighte(avl->right) > 1)
    {
        if (get_height(avl->left->left) < get_height(avl->left->right))
            avl->left = left_rotate(avl->left);
        avl = right_rotate(avl);
    }
    else if (get_height(avl->right) - get_heighte(avl->left) > 1)
    {
        if (get_height(avl->right->left) > get_height(avl->right->right))
            avl->left = right_rotate(avl->left);
        avl = left_rotate(avl);
    }
    avl->height = 1 + max(get_height(avl->left), get_height(avl->right));
    return avl;
}
node *insert(node *tree, int key)
{
    if (tree == NULL)
        return retrace(new_node(key));
    if (key < tree->data)
        tree->left = insert(tree->left, key);
    else if (key > tree->data)
        tree->right = insert(tree->right, key);
    else
        printf("Key is present already !!");
    tree = retrace(tree);
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
    tree = retrace(tree);
    return tree;
}