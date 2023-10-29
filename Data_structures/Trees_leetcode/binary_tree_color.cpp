#include <iostream>
#include <vector>
using namespace std;
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    int size(TreeNode *root)
    {
        if (root == NULL)
            return 0;
        return 1 + size(root->left) + size(root->right);
    }
    TreeNode *xer(TreeNode *root, int x)
    {
        if (root == NULL)
            return NULL;
        if (root->val == x)
            return root;
        if (xer(root->left, x))
            return xer(root->left, x);
        if (xer(root->right, x))
            return xer(root->right, x);
        return NULL;
    }
    bool btreeGameWinningMove(TreeNode *root, int n, int x)
    {
        TreeNode *popo = xer(root, x);
        root = popo;
        int l = size(root->left), r = size(root->right);
        int m = n - 1 - l - r;
        if (l + r + 1 < m)
            return true;
        if (m + r + 1 < l)
            return true;
        if (l + m + 1 < r)
            return true;
        return false;
    }
};