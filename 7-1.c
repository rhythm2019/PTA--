/*
7-1 最大子列和问题 (20分)
*/
#include <stdio.h>
#include <stdlib.h>
#define ERROR NULL
int main()
{
    
    int num, Array[100000];
    int i = 0, MAX, SUM;
    scanf("%d", &num);
    while (i < num)
        scanf("%d", &Array[i++]);
    MAX = Array[0];
    SUM = 0;
    i = 0;
    while (i < num)
    {
        SUM = SUM + Array[i++];
        if (SUM < 0)
            SUM = 0;
        else if (SUM > MAX)
        {
            MAX = SUM;
        }
    }
    printf("%d", MAX);
    return (0);
}