#include <iostream>
#include <vector>
using namespace std;
struct Node
{
    int data;
    struct Node *left, *right;
};
class Solution
{
private:
public:
    vector<int> ans;
    int dist(Node *root, Node *target)
    {
        
    }

    vector<int> KDistanceNodes(Node *root, int target, int k)
    {
        // return the sorted vector of all nodes at k dist
    }
};