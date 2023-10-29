#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
bool pairsort(pair<int, int> p1, pair<int, int> p2)
{
    return p1.second > p2.second;
}
class Solution
{
public:
    int ans = -1, sp = 0, eff = 0, temp;
    long long mod = 1e9 + 7;
    int maxPerformance(int n, vector<int> &speed, vector<int> &efficiency, int k)
    {
        vector<pair<int, int>> v(n);
        for (int i = 0; i < n; i++)
            v[i] = {speed[i], efficiency[i]};
        sort(v.begin(), v.end(), pairsort);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        for (int i = 0; i < n; i++)
        {
            if (pq.size() >= k)
            {
                sp -= pq.top().first;
                pq.pop();
            }
            pq.push(v[i]);
            sp += v[i].first;
            ans = max(ans, sp * v[i].second);
        }
        return ans % mod;
    }
};