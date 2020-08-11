/*
输入首先给出两个正整数N（≤10^​6​ ）和M（≤10），其中N为总人数，M为需要找出的大富翁数；
接下来一行给出N个人的个人资产值，以百万元为单位，为不超过长整型范围的整数。数字间以空格分隔。
输出格式:
DATE:20200726
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}
int main()
{
    int i, N, M;
    int richman[1000000];
    scanf("%d %d", &N, &M);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &richman[i]);
    }
    qsort(richman, N, sizeof(int), cmpfunc);
    //print
    if (M > N)
        M = N;
    for (i = 0; i < M; i++)
    {
        printf("%d", richman[i]);
        if (i < M - 1)
            printf(" ");
    }
    return (0);
}