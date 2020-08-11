/*
某学校有N个学生，形成M个俱乐部。每个俱乐部里的学生有着一定相似的兴趣爱好，形成一个朋友圈。
一个学生可以同时属于若干个不同的俱乐部。根据“我的朋友的朋友也是我的朋友”这个推论可以得出，如果A和B是朋友，且B和C是朋友，则A和C也是朋友。
请编写程序计算最大朋友圈中有多少人。
DATE:20200717
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 30000
void Union(int Array[][2], int node1, int node2)
{

    node1 = find_parent(Array, node1);
    node2 = find_parent(Array, node2);
    if (node1 != node2)
    {
        Array[node2][0] = node1;
        Array[node1][1] += Array[node2][1];
        Array[node2][1] = 0;
    }
    return;
}
int find_parent(int Array[][2], int node)
{
    while (Array[node][0] != node)
        node = Array[node][0];
    return (node);
}
int main()
{
    int i, j, k, n1, n2, N, M, Maxcount = 0;
    int student[MAXSIZE + 1][2];
    scanf("%d %d", &N, &M);
    for (i = 0; i < N; i++)
    {
        student[i + 1][0] = i + 1;
        student[i + 1][1] = 1;
    }
    for (i = 0; i < M; i++)
    {
        scanf("%d", &j);
        scanf("%d", &n1);
        for (k = 1; k < j; k++)
        {
            scanf("%d", &n2);
            Union(student, n1, n2);
        }
    }
    for (i = 1; i < N + 1; i++)
    {
        if (student[i][1] > Maxcount)
            Maxcount = student[i][1];
    }
    printf("%d", Maxcount);
    return (0);
}