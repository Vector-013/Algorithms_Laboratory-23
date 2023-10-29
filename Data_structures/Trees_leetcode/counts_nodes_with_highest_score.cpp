#include <iostream>
#include <vector>
using namespace std;

long long max(long long a, long long b)
{
    long long ans = (a > b) ? a : b;
    return ans;
}
int sizes(int k, vector<vector<int>> &lr, vector<vector<int>> &sz, int n, vector<int> &dp)
{
    if (dp[k] != -1)
        return dp[k];
    if (lr[k].size() == 0)
    {
        dp[k] = 1;
        sz[k].push_back(n - 1);
        return 1;
    }
    int ptree = n - 1;
    for (auto q : lr[k])
    {
        if (dp[q] == -1)
        {
            sz[k].push_back(sizes(q, lr, sz, n, dp));
            ptree -= sizes(q, lr, sz, n, dp);
        }
        else
        {
            sz[k].push_back(dp[q]);
            ptree -= dp[q];
        }
    }
    sz[k].push_back(ptree);
    dp[k] = n - ptree;
    return n - ptree;
}
int countHighestScoreNodes(vector<int> &parents)
{
    int n = parents.size();
    vector<vector<int>> lr(n);
    for (int i = 1; i < n; i++)
        lr[parents[i]].push_back(i);
    vector<vector<int>> sz(n, vector<int>());
    vector<int> dp(n, -1);
    int l = sizes(0, lr, sz, n, dp);
    // for (int i = 0; i < dp.size(); i++)
    // {
    //     cout << dp[i] << " ";
    // }
    vector<long long> prods(n);
    long long maxi = -1e18;
    long long prod;
    for (int j = 0; j < n; j++)
    {
        prod = 1;
        for (auto i : sz[j])
        {
            if (i != 0)
            {
                prod *= i;
            }
        }
        maxi = max(prod, maxi);
        prods[j] = prod;
    }
    // for (int i = 0; i < n; i++)
    // {
    //     cout << prods[i] << '\n';
    // }
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        if (prods[i] == maxi)
            cnt++;
    }
    return cnt;
}

int main()
{
    int n;
    cin >> n;
    vector<int> parents(n);
    for (int i = 0; i < n; i++)
        cin >> parents[i];
    int ans = countHighestScoreNodes(parents);
    cout << ans << '\n';
}