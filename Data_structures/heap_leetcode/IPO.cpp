#include <iostream>
#include <vector>
#include <queue>
using namespace std;
bool pairsort(pair<int, int> p1, pair<int, int> p2)
{
    return p1.second < p2.second;
}
class Solution
{
public:
    priority_queue<pair<int, int>> pq;
    vector<pair<int, int>> v;

    int findMaximizedCapital(int k, int w, vector<int> &profits, vector<int> &capital)
    {
        int n = profits.size();
        for (int i = 0; i < n; i++)
            v.push_back({profits[i], capital[i]});
        int ptr = 0;
        sort(v.begin(), v.end(), pairsort);
        while (k--)
        {
            while (ptr < n && v[ptr].second <= w)
            {
                pq.push(v[ptr]);
                ptr++;
            }
            if (!pq.empty())
            {
                w += pq.top().first;
                pq.pop();
            }
        }
        return w;
    }
};