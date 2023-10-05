// 22CS30039 OJAS DUBEY
// MACHINE 78

#include <stdio.h>
#include <stdlib.h>
int chooser(int dp[], int pt[], int sk[], int n, int m)
{
    if (m > n - 1)
        return 0;
    if (dp[m] != -1)
        return dp[m];
    int cur = pt[m] + chooser(dp, pt, sk, n, m + sk[m] + 1);
    int alt = chooser(dp, pt, sk, n, m + 1);
    int ret = (cur > alt) ? cur : alt;
    dp[m] = ret;
    return ret;
}

int main()
{
    printf("no of machines : ");
    int n;
    scanf("%d", &n);
    int pt[n], sk[n];
    printf("Give pair wise input of each machine data : \n");
    for (int i = 0; i < n; i++)
    {
        printf("machine %d : ", i);
        scanf("%d%d", &pt[i], &sk[i]);
    }
    int dp[n];
    for (int i = 0; i < n; i++)
        dp[i] = -1;

    int ans = chooser(dp, pt, sk, n, 0);
    printf("ans  = %d\n", ans);
}