#include <iostream>

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
    int cnt = 0;
    int status(TreeNode *root)
    {
        if (root == NULL)
            return 1;
        int stat;
        // 1 = monitored , 2 = not monitored , 3 = camera
        int lcam = status(root->left);
        int rcam = status(root->right);
        if (lcam == 2 || rcam == 2)
        {
            stat = 3;
            cnt++;
        }
        else if (lcam == 1 && rcam == 1)
            stat = 2;
        else
            stat = 1;
        return stat;
    }
    int minCameraCover(TreeNode *root)
    {
        int stat = status(root);
        if (stat == 2)
            cnt++;
        return cnt;
    }
};