/* 22CS30039
OJAS DUBEY
LAB-02 : Q1
MACHINE : 78 */

#include <stdio.h>
#include <stdlib.h>

int location(int n, int m) // let this return sole survvor index. assume 0 indexing.
{
    if (n == 1)
    {
        return 0; // index of solo person
    }
    return ((location(n - 1, m) + m % n) % n); // mods to ensure circular
} // add m%n to get to "new" start of the game.keeps adding shifts

int main()
{
    int n, m;
    printf("input parameters n m: ");
    scanf("%d %d", &n, &m);
    printf("survivor is %d\n", location(n, m) + 1); //+1 to get original position
}