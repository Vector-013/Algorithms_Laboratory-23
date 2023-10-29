#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
int mod = 1e9 + 7;
bool pairsort(pair<int, int> p1, pair<int, int> p2)
{
    return p1.second > p2.second;
}

class Solution
{
public:
    int getNumberOfBacklogOrders(vector<vector<int>> &orders)
    {
        priority_queue<vector<int>> buy;
        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> sell;
        for (vector<int> temp : orders)
        {
            int p = temp[0], n = temp[1], t = temp[2];
            if (t == 0)
            {
                while (sell.size() && sell.top()[0] <= p && n)
                {
                    vector<int> cur = sell.top();
                    if (cur[1] > n)
                    {
                        cur[1] -= n;
                        sell.pop();
                        sell.push(cur);
                        n = 0;
                    }
                    else
                    {
                        n -= cur[1];
                        sell.pop();
                    }
                }
                if (n)
                    buy.push({p, n, t});
            }
            else
            {
                while (buy.size() && buy.top()[0] >= p && n)
                {
                    vector<int> cur = buy.top();
                    if (cur[1] > n)
                    {
                        cur[1] -= n;
                        buy.pop();
                        buy.push(cur);
                        n = 0;
                    }
                    else
                    {
                        n -= cur[1];
                        buy.pop();
                    }
                }
                if (n)
                    sell.push({p, n, t});
            }
        }
        long long int res = 0;
        while (buy.size() > 0)
        {
            res += buy.top()[1];
            buy.pop();
        }
        while (sell.size() > 0)
        {
            res += sell.top()[1];
            sell.pop();
        }
        return res % 1000000007;
    }
};