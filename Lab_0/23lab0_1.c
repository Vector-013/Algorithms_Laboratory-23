#include <stdlib.h>
#include <stdio.h>
typedef struct
{
    double x, y, z;
} point;
point dif(point a, point b)
{
    point la = {a.x - b.x, a.y - b.y, a.z - b.z};
    return la;
}
double mnx(point p, point q)
{
    return (p.y * q.z - p.z * q.y);
}
double mny(point p, point q)
{
    return (-p.x * q.z + p.z * q.x);
}
double mnz(point p, point q)
{
    return (-p.y * q.x + p.x * q.y);
}
int main()
{
    FILE *fptr;
    char s[100];
    int pts, tri, a, b, c;
    fptr = fopen("uu.txt", "r+");
    for (int i = 0; i < 3; i++)
        fgets(s, 50, fptr);
    fseek(fptr, 7, SEEK_CUR);
    fscanf(fptr, "%d", &pts);
    fseek(fptr, 10, SEEK_CUR);
    fscanf(fptr, "%d", &tri);
    point arr[pts];
    double nx[tri], ny[tri], nz[tri];
    for (int i = 0; i < pts; i++)
    {
        fscanf(fptr, "%lf %lf %lf", &arr[i].x, &arr[i].y, &arr[i].z);
    }
    for (int i = 0; i < tri; i++)
    {
        fscanf(fptr, "%d %d %d", &a, &b, &c);
        point p, q;
        p = dif(arr[a - 1], arr[b - 1]);
        q = dif(arr[a - 1], arr[c - 1]);
        nx[i] = mnx(p, q);
        ny[i] = mny(p, q);
        nz[i] = mnz(p, q);
    }
    fptr = fopen("ans.txt", "w");
    for (int i = 0; i < tri; i++)
    {
        fprintf(fptr, "%lf %lf %lf \n", nx[i], ny[i], nz[i]);
        printf("%lf %lf %lf \n", nx[i], ny[i], nz[i]);
    }
}