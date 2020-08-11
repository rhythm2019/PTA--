/*
哥尼斯堡是位于普累格河上的一座城市，它包含两个岛屿及连接它们的七座桥，如下图所示。
可否走过这样的七座桥，而且每桥只走过一次？瑞士数学家欧拉(Leonhard Euler，1707—1783)最终解决了这个问题，并由此创立了拓扑学。
这个问题如今可以描述为判断欧拉回路是否存在的问题。欧拉回路是指不令笔离开纸面，可画过图中每条边仅一次，且可以回到起点的一条回路。现给定一个无向图，问是否存在欧拉回路？
DATE:20200723
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct node *pnode;
struct node
{
    int NO;
    pnode next;
};
struct Graph
{
    int nv, ne;
    pnode head; //head
    pnode *rear;
};
void dfs(struct Graph GG, int root, int visit[])
{
    int node;
    pnode cur;
    if (visit[root - 1] == 1)
        return;
    cur = GG.head[root - 1].next;
    visit[root - 1] = 1;
    while (cur)
    {
        node = cur->NO;
        if (visit[node - 1] == 0)
            dfs(GG, node, visit);
        cur = cur->next;
    }
    return;
}
void insert_node(struct Graph GG, int n1, int n2)
{
    pnode next;
    next = (pnode)malloc(sizeof(struct node));
    next->NO = n2;
    next->next = NULL;
    if (GG.rear[n1 - 1])
    {
        GG.rear[n1 - 1]->next = next;
        GG.rear[n1 - 1] = next;
    }
    else
    {
        GG.rear[n1 - 1] = next;
        GG.head[n1 - 1].next = next;
    }
    return;
}
int main()
{
    int i, node1, node2, indegree[1000] = {0}, visit[1000] = {0};
    int Flag = 1;
    struct Graph GG;
    scanf("%d %d", &GG.nv, &GG.ne);
    //init
    GG.head = (pnode)malloc(GG.nv * sizeof(struct node));
    GG.rear = (pnode *)malloc(GG.nv * sizeof(struct node *));
    for (i = 0; i < GG.nv; i++)
    {
        (GG.head + i)->NO = i + 1;
        (GG.head + i)->next = NULL;
        GG.rear[i] = NULL;
    }
    for (i = 0; i < GG.ne; i++)
    {
        scanf("%d %d", &node1, &node2);
        indegree[node1 - 1]++;
        indegree[node2 - 1]++;
        insert_node(GG, node1, node2);
        insert_node(GG, node2, node1);
    }
    dfs(GG, 1, visit);
    for (i = 0; i < GG.nv; i++)
        if (visit[i] == 0 || indegree[i] % 2)
        {
            Flag = 0;
            break;
        }
    if (Flag)
        printf("1");
    else
        printf("0");
    return (0);
}