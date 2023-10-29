#include <iostream>
#include <map>
using namespace std;
#define l root->left
#define ll root->left->left
#define r root->right
#define lr root->left->right
#define rl root->right->left
#define rr root->right->right
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
    map<TreeNode *, int> dp;
    int max(int a, int b)
    {
        int ans = (a > b) ? a : b;
        return ans;
    }
    int robber(TreeNode *root)
    {
        if (dp[root] != 0)
            return dp[root];
        if (root == NULL)
            return 0;
        int ymon = root->val, nmon = robber(l) + robber(r);
        if (l)
            ymon += robber(ll) + robber(lr);
        if (r)
            ymon += robber(rr) + robber(rl);
        dp[root] = max(ymon, nmon);
        return max(ymon, nmon);
    }
    int rob(TreeNode *root)
    {
        if (root == NULL)
            return 0;
        int ans = robber(root);
        return ans;
    }
};