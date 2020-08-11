/*
作为一个城市的应急救援队伍的负责人，你有一张特殊的全国地图。
在地图上显示有多个分散的城市和一些连接城市的快速道路。
每个城市的救援队数量和每一条连接两个城市的快速道路长度都标在地图上。
当其他城市有紧急求助电话给你的时候，你的任务是带领你的救援队尽快赶往事发地，同时，一路上召集尽可能多的救援队。
DATE:20200729
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Cutoff 50
typedef struct node *pnode;
struct node
{
    int NO;
    int distance;
    pnode next;
};
struct Graph
{
    int nv, ne;
    pnode head; //head
};
struct PATH
{
    int NO;       //上一次的路径
    int shortNum; //shortest path Num数目
};

// quick sort
void swap(int A[], int i, int j)
{
    int tmp;
    tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
    return;
}
void insert_sort(int A[], int left, int right, int (*cmpfunc)(const void *, const void *, int *, int *), int shortDis[], int selected[])
{
    int i, j, k;
    int tmp;
    for (i = left + 1; i <= right; i++)
    {
        j = i - 1;
        while (j >= left && cmpfunc(A + j, A + i, shortDis, selected) > 0)
            j--;
        tmp = A[i];
        for (k = i; k > j + 1; k--)
            A[k] = A[k - 1];
        A[j + 1] = tmp;
    }
    return;
}
void quick_sort(int A[], int left, int right, int (*cmpfunc)(const void *, const void *, int *, int *), int shortDis[], int selected[])
{
    int i, j, center = (left + right) / 2;
    if (right <= left)
        return;
    if (right - left < Cutoff)
        insert_sort(A, left, right, cmpfunc, shortDis, selected);
    else
    {
        //search pivot
        if (cmpfunc(A + left, A + center, shortDis, selected) > 0)
            swap(A, left, center);
        if (cmpfunc(A + left, A + right, shortDis, selected) > 0)
            swap(A, left, right);
        if (cmpfunc(A + center, A + right, shortDis, selected) > 0)
            swap(A, center, right);
        swap(A, center, right - 1);
        //quick sort
        i = left + 1;
        j = right - 2;
        while (1)
        {
            while (cmpfunc(A + i, A + right - 1, shortDis, selected) < 0)
                i++;
            while (cmpfunc(A + j, A + right - 1, shortDis, selected) > 0)
                j--;
            if (i < j)
            {
                swap(A, i, j);
                i++;
                j--;
            }
            else
                break;
        }
        swap(A, i, right - 1);
        quick_sort(A, left, i - 1, cmpfunc, shortDis, selected);
        quick_sort(A, i + 1, right, cmpfunc, shortDis, selected);
    }
    return;
}
int cmpfunc(const void *a, const void *b, int shortDis[], int selected[])
{
    int *c1 = (int *)a;
    int *c2 = (int *)b;
    if (selected[*c1] != selected[*c2])
        return (selected[*c1] - selected[*c2]);
    else if (selected[*c1] == 0)
        return (shortDis[*c1] - shortDis[*c2]);
    else
        return (0);
}
//Dijkstra
void dijkstra(struct Graph GG, int begin, int end, int selected[], int shortDis[], int people[], int teampeople[], struct PATH path[], int *maxV)
{
    int i, curNode, nextNode, N = GG.nv;
    int *queue = (int *)malloc(GG.nv * sizeof(int));
    pnode cur;
    for (i = 0; i < GG.nv; i++)
        queue[i] = i;
    shortDis[begin] = 0;
    curNode = begin;
    while (curNode != -1 && curNode != end)
    {
        selected[curNode] = 1;
        cur = GG.head[curNode].next;
        while (cur)
        {
            nextNode = cur->NO;
            if (shortDis[curNode] + cur->distance < shortDis[nextNode])
            {
                path[nextNode].shortNum = path[curNode].shortNum;
                path[nextNode].NO = curNode;
                shortDis[nextNode] = shortDis[curNode] + cur->distance;
                teampeople[nextNode] = teampeople[curNode] + people[nextNode];
            }
            else if (shortDis[curNode] + cur->distance == shortDis[nextNode])
            {
                path[nextNode].shortNum += path[curNode].shortNum;
                if (teampeople[nextNode] < teampeople[curNode] + people[nextNode])
                {
                    teampeople[nextNode] = teampeople[curNode] + people[nextNode];
                    path[nextNode].NO = curNode;
                }
            }
            cur = cur->next;
        }
        //find next node
        quick_sort(queue, 0, N - 1, cmpfunc, shortDis, selected);
        N--;
        if (selected[queue[0]])
            curNode = -1;
        else
            curNode = queue[0];
    }
    return;
}
void insert_node(struct Graph GG, int n1, int n2, int dist)
{
    pnode cur, next;
    next = (pnode)malloc(sizeof(struct node));
    next->NO = n2;
    next->distance = dist;
    cur = &(GG.head[n1]);
    while (cur->next && cur->next->NO < n2)
        cur = cur->next;
    next->next = cur->next;
    cur->next = next;
    return;
}
int main()
{
    int i, j, node1, node2, dist;
    int begin, end, maxDis = 0;
    int selected[500] = {0}, people[500], teampeople[500], shortDis[500];
    struct PATH path[500] = {-1, 0};
    struct Graph GG;
    scanf("%d %d %d %d", &GG.nv, &GG.ne, &begin, &end);
    //init
    GG.head = (pnode)malloc(GG.nv * sizeof(struct node));
    for (i = 0; i < GG.nv; i++)
    {
        scanf("%d", &people[i]);
        teampeople[i] = people[i];
        (GG.head + i)->NO = i;
        (GG.head + i)->next = NULL;
    }
    for (i = 0; i < GG.ne; i++)
    {
        scanf("%d %d %d", &node1, &node2, &dist);
        maxDis += dist;
        insert_node(GG, node1, node2, dist);
        insert_node(GG, node2, node1, dist);
    }
    maxDis++;
    for (i = 0; i < GG.nv; i++)
        shortDis[i] = maxDis;
    path[begin].shortNum = 1;
    dijkstra(GG, begin, end, selected, shortDis, people, teampeople, path, &maxDis);

    //print result
    printf("%d %d\n", path[end].shortNum, teampeople[end]);
    i = 0;
    people[i] = end; //路径queue
    while (path[end].NO != -1)
    {
        end = path[end].NO;
        people[++i] = end;
    }
    for (j = i; j > 0; j--)
        printf("%d ", people[j]);
    printf("%d", people[0]);
    return (0);
}