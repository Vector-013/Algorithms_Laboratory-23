/* OJAS DUBEY
  22CS30039
  MACHINE 78*/
#include <stdio.h>
#include <stdlib.h>

int max(int a, int b)
{
    int ans = (a > b) ? a : b;
    return ans;
}

int divi(int p, int mid)
{
    int kids;
    if ((p % mid) == 0)        // this function returns number of kids getting prize p (p is a type of prize)
        kids = (int)(p / mid); // if n is the maximum prizes to a kid in the binary seach
    else
    {
        kids = (int)(p / mid) + 1;
    }
    return kids;
}
int num_kids(int mid, int p[], int m)
{
    int ans = 0;
    for (int i = 0; i < m; i++)
    {
        ans += divi(p[i], mid); // counts total kids getting rewards by traversing array
    }
    return ans;
}

int main()
{
    int n, m, pmax = 0;
    printf("give the number of students : ");
    scanf("%d", &n);
    printf("size of prizes array : ");
    scanf("%d", &m);
    printf("give prizes numbers array : ");
    int p[m]; // prizes array
    for (int i = 0; i < m; i++)
    {
        scanf("%d", &p[i]);
        // storing upper limit of binary search, maximum a kid can get is single type prize maximum
    }
    for (int i = 0; i < m; i++)
    {
        pmax = max(pmax, p[i]);
    }

    // we will assume some maximum and check its validity while awarding prizes to students accordinglt
    // then we will use binary search based on the validity check to look for better prize distributions.

    int mid; // binary search mid

    int s = 1, e = pmax;
    while (s <= e)
    {
        mid = (s + e) / 2;
        if (s == e)
            break;
        if (num_kids(mid, p, m) <= n)
        { // too less people will be awarded, reduce max award
            e = mid;
        }
        else
        {
            s = mid + 1; // increase award
        }
    }

    printf("maximum prize is : %d\n", mid);
}