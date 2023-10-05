/* OJAS DUBEY
  22CS30039
  MACHINE 78*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct
{
    int x, y;
} city;

int min(int a, int b)
{
    int ans = (a < b) ? a : b;
    return ans;
}

double dist(city a, city b)
{
    double ans;
    ans = sqrt(((a.x - b.x) * (a.x - b.x)) + ((a.y - b.y) * (a.y - b.y)));
    return ans;
}

int main()
{
    int n;
    printf("number of cities : ");
    scanf("%d", &n);
    city cty[n]; // array of cities
    printf("give city coordinates as -> x y : \nx   y\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &cty[i].x, &cty[i].y);
    }

    double distance[n][n];
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            distance[i][j] = dist(cty[i], cty[j]);
        }
    }

    int path[n + 1]; // trace out path
    path[0] = 0, path[n] = 0;
    double cost = 0;
    int cnt = 1;                    // number of cities gone past
    int cur_city = 0, nxt_city = 0; // current city number, starts from 0
    int visit[n];                   // visited or not
    double closest;
    for (int i = 0; i < n; i++)
    {
        visit[i] = 0; // 0 means not visit, 1 means visited
    }

    visit[0] = 1;

    while (cnt < n)
    {
        closest = 2000000; // initiales to value more than rt2*1000 as going to minimise
        for (int i = 0; i < n; i++)
        {
            if (i != cur_city && visit[i] == 0)
            {
                if (distance[cur_city][i] < closest)
                {
                    closest = distance[cur_city][i]; // cost of closest city
                    nxt_city = i;
                }
            }
        }
        path[cnt] = nxt_city; // mark as next city
        visit[nxt_city] = 1;  // mark as visited
        cur_city = nxt_city;  // now moving
        cost += closest;      // add costs
        cnt++;
    }
    cost += distance[nxt_city][0]; // going back

    for (int i = 0; i < n; i++)
    {
        printf("%d -> ", path[i]);
    }
    printf("0\n");
    printf("%lf\n", cost);
}