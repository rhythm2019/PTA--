/*
给定公司N名员工的工龄，要求按工龄增序输出每个工龄段有多少员工。
DATE:20200711
*/
#include <stdio.h>
#include <stdlib.h>
int main()
{
    int i, N, count[51] = {0}, workage;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &workage);
        count[workage] += 1;
    }
    for (i = 0; i < 51; i++)
    {
        if (count[i])
            printf("%d:%d\n", i, count[i]);
    }
    return (0);
}