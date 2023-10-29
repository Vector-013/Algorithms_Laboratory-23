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
    int maxsofar(TreeNode *root, int &maxi)
    {
        if (root == NULL)
            return 0;
        int lfar = maxsofar(root->left, maxi);
        int rfar = maxsofar(root->right, maxi);
        int ans = max(lfar + root->val, max(root->val, rfar + root->val));
        maxi = max(maxi, max(ans, lfar + rfar + root->val));
        return ans;
    }
    int maxPathSum(TreeNode *root)
    {
        int maxi = -2e9;
        int waste = maxsofar(root, maxi);
        return maxi;
    }
};