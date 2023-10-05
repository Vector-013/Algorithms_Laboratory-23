// 22CS30039 OJAS DUBEY
// MACHINE 78

#include <stdio.h>
#include <stdlib.h>
int l, m;
int lcs(int dp[l + 1][m + 1], char s[], char t[], int l, int m)
{
    int ans = 0;
    for (int i = 1; i <= l; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s[i - 1] == t[j - 1])
            {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            }
            else
            {
                dp[i][j] = (dp[i - 1][j] > dp[i][j - 1]) ? dp[i - 1][j] : dp[i][j - 1];
            }
        }
    }
    return dp[l][m];
}
void lcsprinter(int dp[l + 1][m + 1], int l, int m, char s[], char t[], char ans[], int cnt)
{
    int i = l, j = m;
    while (i > 0 && j > 0)
    {
        if (s[i - 1] == t[j - 1])
        {
            ans[cnt] = s[i - 1];
            s[i - 1] = '?';
            t[j - 1] = '?';
            i--;
            j--;
            cnt--;
        }
        else if (dp[i - 1][j] > dp[i][j - 1])
            i--;
        else
            j--;
    }
}
int main()
{
    printf("first string len : ");
    scanf("%d", &l);
    printf("second string len : ");
    scanf("%d", &m);

    if (l == 0 || m == 0)
    {
        if (l == 0)
        {
            printf("first empty, give second string : ");
            char q[m];
            scanf("%s", q);
            for (int i = 0; i < m; i++)
            {
                printf(" +%c ", q[i]);
            }
        }
        else
        {
            printf("second empty, give first string");
            char w[l];
            scanf("%s", w);
            for (int i = 0; i < l; i++)
            {
                printf(" -%c ", w[i]);
            }
        }
        printf("\n");
        return 0;
    }

    printf("first string : ");
    char s[l + 1];
    scanf("%s", s);
    printf("second string : ");
    char t[m + 1];
    scanf("%s", t);
    int dp[l + 1][m + 1];
    for (int i = 0; i <= l; i++)
        dp[i][0] = 0;
    for (int i = 0; i <= m; i++)
        dp[0][i] = 0;

    int len = lcs(dp, s, t, l, m) + 1;
    char ans[len];
    ans[len] = '\0';
    len--;
    // printf("%d\n", len);
    lcsprinter(dp, l, m, s, t, ans, len - 1);
    // printf("lcs is : %s\n", ans);

    int zx = l + m - len;
    // printf("%d\n", zx);
    int ptr = 0, i = 0, j = 0;
    while (i < l && j < m)
    {
        while (s[i] != '?')
        {
            printf(" -%c ", s[i]);
            i++;
        }
        while (t[j] != '?')
        {
            printf(" +%c ", t[j]);
            j++;
        }
        if (ptr < len)
        {
            printf(" %c ", ans[ptr]);
            ptr++;
            j++;
            i++;
        }
    }
    if (i == l)
        while (j < m)
        {
            printf(" +%c ", t[j]);
            j++;
        }
    if (j == m)
        while (i < l)
        {
            printf(" -%c ", s[i]);
            i++;
        }
    printf("\n");
}