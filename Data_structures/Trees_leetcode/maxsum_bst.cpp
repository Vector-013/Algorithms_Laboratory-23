#include <iostream>
#include <map>
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
    map<TreeNode *, int> dp;
    map<TreeNode *, int> bst;
    int maxi = 0;
    int get_max(TreeNode *tree)
    {
        while (tree->right != NULL)
            tree = tree->right;
        return tree->val;
    }
    int get_min(TreeNode *tree)
    {
        while (tree->left != NULL)
            tree = tree->left;
        return tree->val;
    }
    int check_bst(TreeNode *root)
    {
        if (bst[root] != 0)
            return bst[root];
        if (root->left == NULL && root->right == NULL)
        {
            bst[root] = 1;
            return 1;
        }
        if (root->left && root->right)
        {
            int lc = check_bst(root->left);
            int rc = check_bst(root->right);
            if (lc == 1 && rc == 1)
            {

                if ((root->val > get_max(root->left)) && (root->val < get_min(root->right)))
                {

                    bst[root] = 1;
                    return 1;
                }
                cout << (root->val) << "\n";
                bst[root] = -1;
                return -1;
            }
            bst[root] = -1;
            return -1;
        }
        else if (root->left)
        {
            int lc = check_bst(root->left);
            if (lc == 1)
            {
                if (root->val > get_max(root->left))
                {
                    bst[root] = 1;
                    return 1;
                }
            }
            bst[root] = -1;
            return -1;
        }
        else
        {
            if (check_bst(root->right) == 1)
            {
                if (root->val < get_min(root->right))
                {
                    bst[root] = 1;
                    return 1;
                }
            }
            bst[root] = -1;
            return -1;
        }
        bst[root] = -1;
        return -1;
    }
    int summer(TreeNode *root)
    {
        if (root == NULL)
            return 0;
        int sum = 0;
        sum = root->val + summer(root->left) + summer(root->right);
        dp[root] = sum;
        return sum;
    }
    int find_maxi(TreeNode *root)
    {
        if (root == NULL)
            return 0;
        int l = 0, r = 0, m = 0;
        if (bst[root] == 1)
            m = dp[root];
        r = find_maxi(root->right);
        l = find_maxi(root->left);
        return max(max(r, l), m);
    }
    int maxSumBST(TreeNode *root)
    {
        bool p = check_bst(root);
        int k = summer(root);
        cout << bst[root] << " " << bst[root->left] << " " << bst[root->right];
        return find_maxi(root);
    }
};