/* 22CS30039
OJAS DUBEY
LAB-01 : Q1(i)
MACHINE : 78 */

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n;
    printf("population of country : ");
    scanf("%d", &n); // user input size of array
    int a[n];        // indeices of people
    printf("Enter the FI list for a country: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }

    int num = a[0];
    int cnt = 1;
    // as we tarverse , cnt keeps track wether a[i] matches num or not, if so cnt++, or else decrease cnt.
    // if cnt =0, change num to current a[i]. as ans would be greater than n/2,cnt of ans never goes zero,
    // while cnt of all else goes to zro.

    for (int i = 1; i < n; i++)
    {
        if (a[i] == num)
        {
            cnt++;
        }
        else
        {
            cnt--;
        }
        if (cnt == 0)
        {
            cnt = 1;
            num = a[i];
        }
    }

    printf("The FI value present in most of the people: %d\n", num);
}