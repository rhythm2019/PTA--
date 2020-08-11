/*
已知有两个等长的非降序序列S1, S2, 设计函数求S1与S2并集的中位数。
DATE:20200804
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main()
{
    int i, j, N;
    int *S1, *S2;
    scanf("%d", &N);
    S1 = (int *)malloc(N * sizeof(int));
    S2 = (int *)malloc(N * sizeof(int));
    for (i = 0; i < N; i++)
        scanf("%d", S1 + i);
    for (i = 0; i < N; i++)
        scanf("%d", S2 + i);
    if (S1[N - 1] <= S2[0])
    {
        printf("%d", S1[N - 1]);
        return (0);
    }
    else if (S2[N - 1] <= S1[0])
    {
        printf("%d", S2[N - 1]);
        return (0);
    }
    i = 0;
    j = 0;
    while (i + j + 1 < N)
    {
        if (S1[i] < S2[j])
            i++;
        else
            j++;
    }
    if (S1[i] <= S2[j])
        printf("%d", S1[i]);
    else
        printf("%d", S2[j]);
    return (0);
}
