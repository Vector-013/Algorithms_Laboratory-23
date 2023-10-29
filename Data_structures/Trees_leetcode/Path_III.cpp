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
    long long rotpath(TreeNode *root, long long trgt)
    {
        if (root == NULL)
            return 0;
        long long cnt = 0;
        if (root->val == trgt)
            cnt++;
        cnt += rotpath(root->left, trgt - root->val) + rotpath(root->right, trgt - root->val);
        return cnt;
    }
    long long pathSum(TreeNode *root, long long targetSum)
    {
        if (root == NULL)
            return 0;
        long long cnt = 0;
        cnt += rotpath(root, targetSum);
        cnt += pathSum(root->left, targetSum);
        cnt += pathSum(root->right, targetSum);
        return cnt;
    }
};