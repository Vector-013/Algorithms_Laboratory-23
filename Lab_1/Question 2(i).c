/* 22CS30039
OJAS DUBEY
LAB-01 : Q1(i)
MACHINE : 78 */
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, sum = 0;
    long long lsum = 0, rsum = 0;
    printf("population of country : ");
    scanf("%d", &n); // user input size of array
    int a[n];        // indices of people
    printf("Enter the FI list for a country: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]); // input
    }
    printf("Stable indices in the list are: ");
    for (int i = 0; i < n; i++)
    {
        lsum = 0;
        rsum = 0;
        for (int j = 0; j < i; j++)
            lsum += a[j]; // sum on left

        for (int j = n - 1; j > i; j--)
            rsum += a[j]; // sum on right

        if (lsum == rsum)
        {                     // check condition
            printf("%d ", i); // print the index
            continue;
        }
    }
    printf("\n"); // newline
}