#include <vector>
#include <iostream>
#include <algorithm>
typedef struct Node
{
    int data;
    struct Node *left;
    struct Node *right;

    Node(int x)
    {
        data = x;
        left = right = NULL;
    }
} Node;
class Solution
{
public:
    int req = -2e9;
    Node *top;
    int max(int a, int b)
    {
        int ans = a > b ? a : b;
    }
    int deepsum(Node *root)
    {
        if (root->left == NULL && root->right == NULL)
            return root->data;

        int lsum = -1e9, rsum = -1e9, temp = 0;
        if (root->left)
        {
            lsum = deepsum(root->left);
            temp += lsum;
        }
        if (root->right)
        {
            rsum = deepsum(root->right);
            temp += rsum;
        }
        temp += root->data;

        if (root == top)
        {
            req = max(req, temp);
        }
        else if (root->left && root->right)
            req = max(req, temp);

        return max(lsum, rsum) + root->data;
    }

    int maxPathSum(Node *root)
    {
        if (root == NULL)
            return 0;
        top = root;
        int ans = deepsum(root);
        return req;
    }
    // int deepsum(Node *root)
    // {
    //     if (root->left == NULL && root->right == NULL)
    //         return root->data;

    //     int lsum = -1e9, rsum = -1e9;
    //     if (root->left)
    //         lsum = deepsum(root->left);
    //     if (root->right)
    //         rsum = deepsum(root->right);

    //     return max(lsum, rsum) + root->data;
    // }
};