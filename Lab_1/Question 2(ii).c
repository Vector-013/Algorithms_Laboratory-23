/* 22CS30039
OJAS DUBEY
LAB-01 : Q1(i)
MACHINE : 78 */
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int n, sum = 0;
    printf("population of country : ");
    scanf("%d", &n); // user input size of array
    int a[n];        // indices of people
    printf("Enter the FI list for a country: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &a[i]); // input
    }

    // we will maintain two continous sum array from left and right side,
    // then in a single traversal will tell wether lsum = rsum
    // O(n) complexity.

    long long lsum[n], rsum[n];
    lsum[0] = 0;
    rsum[n - 1] = 0; // initialise for end values
    for (int i = 0; i < n - 1; i++)
    {
        lsum[i + 1] = lsum[i] + a[i]; // adding left
    }

    for (int i = n - 1; i > 0; i--)
    {
        rsum[i - 1] = rsum[i] + a[i]; // adding right
    }

    printf("Stable indices in the list are: ");
    for (int i = 0; i < n; i++)
    {
        if (lsum[i] == rsum[i]) // ccheck condition
        {
            printf("%d ", i);
        }
    }
    printf("\n");
}