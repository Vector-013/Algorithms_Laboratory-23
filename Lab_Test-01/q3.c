/* OJAS DUBEY
  22CS30039
  MACHINE 78*/
#include <stdio.h>
#include <stdlib.h>

double max(double a, double b)
{
    double ans = (a > b) ? a : b;
    return ans;
}

double op(double a, double b, int pos, int ops[])
{
    if (ops[pos] == 1)
    {
        return a * b;
    }
    else
    {
        return a + b;
    }
}

int main()
{
    int n;
    printf("Number of integers : ");
    scanf("%d", &n);
    printf("Enter %d numbers from left to right : ", n);
    double nums[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%lf", &nums[i]);
    }
    int ops[n - 1]; // 0 1 aray telling about operator
    char *ch;
    printf("Enter %d operators left to right (no spaces): ", n - 1);
    scanf("%s", ch);

    for (int i = 0; i < n - 1; i++)
    {
        if (ch[i] == '*')
            ops[i] = 1;
        else
            ops[i] = 0;
    }

    double dp[n][n]; // dp[i][j] stores optimal answer for pos i to j , will give final ans as dp[0][n-1]

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            dp[i][j] = -1;

    for (int i = 0; i < n; i++)
    {
        dp[i][i] = nums[i]; // base case
    }

    // traverse dp array diagnol wise in upper half of the dp array
    int i = 0, j = 0, x, y;
    for (int dif = 1; dif < n; dif++)
    {
        i = 0;
        j = i + dif;
        while (j < n)
        {
            dp[i][j] = max(op(dp[i][j - 1], nums[j], j - 1, ops), op(dp[i + 1][j], nums[i], i, ops)); // finding max based on operations performed.
            j++;
            i++;
        }
    }

    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = 0; j < n; j++)
    //     {
    //         printf("%lf ", dp[i][j]);
    //     }
    //     printf("\n");
    // }

    printf(" ans = %lf\n", dp[0][n - 1]);
}
