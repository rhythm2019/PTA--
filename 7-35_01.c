/*
作为一个城市的应急救援队伍的负责人，你有一张特殊的全国地图。
在地图上显示有多个分散的城市和一些连接城市的快速道路。
每个城市的救援队数量和每一条连接两个城市的快速道路长度都标在地图上。
当其他城市有紧急求助电话给你的时候，你的任务是带领你的救援队尽快赶往事发地，同时，一路上召集尽可能多的救援队。
DATE:20200801
*/
/*
此处注意，堆的删除操作会发生问题，主要为堆的数据是动态变动的......
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxDis 250001
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
    int NO;       //上一个节点
    int shortNum; //shortest path Num数目
};
//heap sort
typedef struct HNode *Heap; /* 堆的类型定义 */
typedef Heap MinHeap;       /* 最小堆 */
struct HNode
{
    int *Data;    /* 存储元素的数组 ,shortDis*/
    int Size;     /* 堆中当前元素个数 */
    int Capacity; /* 堆的最大容量 */
};
MinHeap init_heap(int N)
{
    MinHeap H;
    if (N)
    {
        H = (MinHeap)malloc(sizeof(struct HNode));
        H->Data = (int *)malloc((N + 1) * sizeof(int));
        H->Size = 0;
        H->Capacity = N;
        return (H);
    }
    else
        return (NULL);
}
int IsFull(MinHeap H)
{
    return (H->Size == H->Capacity);
}
int IsEmpty(MinHeap H)
{
    return (H->Size == 0);
}
void PercDown(MinHeap H, int index, int *P)
{
    int tmp;
    if (2 * index + 1 <= H->Size && P[H->Data[2 * index + 1]] < P[H->Data[2 * index]] && P[H->Data[2 * index + 1]] < P[H->Data[index]])
    {
        tmp = H->Data[2 * index + 1];
        H->Data[2 * index + 1] = H->Data[index];
        H->Data[index] = tmp;
        PercDown(H, 2 * index + 1, P);
    }
    else if (2 * index <= H->Size && P[H->Data[2 * index]] < P[H->Data[index]])
    {
        tmp = H->Data[2 * index];
        H->Data[2 * index] = H->Data[index];
        H->Data[index] = tmp;
        PercDown(H, 2 * index, P);
    }
    else
        return;
}
int delete_min(MinHeap H, int *P)
{
    if (H->Size > 1)
    {
        H->Data[1] = H->Data[H->Size--];
        PercDown(H, 1, P);
        return (1);
    }
    else
        return (0);
}
int build_heap(MinHeap H, int *P)
{
    int i;
    for (i = H->Size / 2; i > 0; i--)
        PercDown(H, i, P);
    return (1);
}

//Dijkstra
void dijkstra(struct Graph GG, int begin, int end, int selected[], int shortDis[], int people[], int teampeople[], struct PATH path[])
{
    int i, curNode, nextNode;
    MinHeap H = init_heap(GG.nv);
    pnode cur;
    for (i = 0; i < GG.nv; i++)
        H->Data[i + 1] = i;
    shortDis[begin] = 0;
    H->Size = GG.nv;
    build_heap(H, shortDis);
    while (H->Size)
    {
        curNode = H->Data[1];
        selected[curNode] = 1;
        if (curNode == end)
            break;
        cur = GG.head[curNode].next;
        while (cur)
        {
            nextNode = cur->NO;
            if (selected[nextNode] == 0)
            {
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
            }
            cur = cur->next;
        }
        //find next node in shprtDis;
        if (H->Size > 1)
            H->Data[1] = H->Data[H->Size--];
        build_heap(H, shortDis);
    }
    return;
}
void insert_node(struct Graph GG, int n1, int n2, int dist)
{
    pnode cur, next = (pnode)malloc(sizeof(struct node));
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
    int begin, end;
    int selected[500] = {0}, people[500], teampeople[500], shortDis[500];
    struct PATH path[500];
    struct Graph GG;
    //input and init
    scanf("%d %d %d %d", &GG.nv, &GG.ne, &begin, &end);
    GG.head = (pnode)malloc(GG.nv * sizeof(struct node));
    for (i = 0; i < GG.nv; i++)
    {
        scanf("%d", &people[i]);
        teampeople[i] = people[i];
        (GG.head + i)->NO = i;
        (GG.head + i)->next = NULL;
        shortDis[i] = maxDis;
        path[i].NO = -1;
        path[i].shortNum = 0;
    }
    for (i = 0; i < GG.ne; i++)
    {
        scanf("%d %d %d", &node1, &node2, &dist);
        insert_node(GG, node1, node2, dist);
        insert_node(GG, node2, node1, dist);
    }
    path[begin].shortNum = 1;
    dijkstra(GG, begin, end, selected, shortDis, people, teampeople, path);
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