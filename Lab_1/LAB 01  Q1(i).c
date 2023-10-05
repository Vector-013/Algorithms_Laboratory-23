/* 22CS30039
OJAS DUBEY
LAB-01 : Q1(i)
MACHINE : 78 */

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, cnt = 0;
    printf("population of country : ");
    scanf("%d", &n); // user input size of array
    int a[n];        // indeices of people
    printf("Enter the FI list for a country: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (a[i] == a[j])
                cnt++;
        }
        if (cnt > n / 2)
        {
            printf("The FI value present in most of the people: %d\n", a[i]);
            break; // only one index can cross n/2 , hence break
        }
        cnt = 0; // reset for next i
    }
}