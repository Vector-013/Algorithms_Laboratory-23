#include <iostream>
typedef struct TreeNode_
{
    int val;
    TreeNode_ *left;
    TreeNode_ *right;
    TreeNode_() : val(0), left(nullptr), right(nullptr) {}
    TreeNode_(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode_(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
} TreeNode;

class Solution
{
public:
    int max(int a, int b)
    {
        int ans = (a > b) ? a : b;
        return ans;
    }
    int maxi = 1;
    int curpath;
    int long_path(TreeNode *root)
    {
        if (root == NULL)
            return 0;
        int ans;
        int lpath = long_path(root->left);
        int rpath = long_path(root->right);
        bool a = (root->left && (root->val == root->left->val));
        bool b = (root->right && (root->val == root->right->val));
        if (a && b)
        {
            maxi = max(lpath + rpath + 1, maxi);
            ans = max(lpath, rpath) + 1;
        }
        else if (a)
        {
            ans = lpath + 1;
            maxi = max(ans, maxi);
        }
        else if (b)
        {
            ans = rpath + 1;
            maxi = max(ans, maxi);
        }
        else
        {
            ans = 1;
        }
        return ans;
    }
    int longestUnivaluePath(TreeNode *root)
    {
        int k = long_path(root);
        return maxi - 1;
    }
};