/*
有了一张自驾旅游路线图，你会知道城市间的高速公路长度、以及该公路要收取的过路费。
现在需要你写一个程序，帮助前来咨询的游客找一条出发地和目的地之间的最短路径。
如果有若干条路径都是最短的，那么需要输出最便宜的一条路径。
DATE:20200617
*/
#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 500
#define INF 250001
struct GNode
{
    int No; //节点数据
    int distance;
    int charge;
    struct GNode *next;
};
struct Graph
{
    int nv, ne;
    struct GNode head[MaxVertexNum];  //head
    struct GNode *rear[MaxVertexNum]; //tail
};
int Dijkstra(struct Graph *G, int *short_distance, int *collect, int *path, int *charge, int start, int end)
{
    int i, min_distance = INF, min_node;
    struct GNode *cur = NULL, *next;
    short_distance[start] = 0;
    charge[start] = 0;
    collect[start] = 1;
    cur = &(G->head[start]);
    while (cur && cur->No != end)
    {
        //adjacent node loop
        next = G->head[cur->No].next;
        while (next)
        {
            if (short_distance[next->No] == INF || short_distance[cur->No] + next->distance < short_distance[next->No])
            {
                short_distance[next->No] = short_distance[cur->No] + next->distance;
                charge[next->No] = charge[cur->No] + next->charge;
            }
            else if (short_distance[next->No] < INF && short_distance[cur->No] + next->distance == short_distance[next->No] && charge[cur->No] + next->charge < charge[next->No])
            {
                charge[next->No] = charge[cur->No] + next->charge;
            }

            next = next->next;
        }
        //search minDistance and min_node
        min_distance = INF;
        for (i = 0; i < G->nv; i++)
            if (collect[i] == 0 && short_distance[i] < min_distance)
            {
                min_distance = short_distance[i];
                min_node = i;
            }
        if (min_distance < INF)
        {
            path[min_node] = cur->No;
            collect[min_node] = 1;
            cur = &(G->head[min_node]);
        }
        else
            return (0);
    }
    if (cur)
        return (1);
    else
        return (0);
}

int main()
{
    int i, Start, End, node1, node2, distance, charge;
    int *short_distance, *collect, *path, *a_charge;
    struct Graph G;
    //init Graph
    scanf("%d %d %d %d", &G.nv, &G.ne, &Start, &End);
    short_distance = (int *)malloc(sizeof(int) * G.nv);
    collect = (int *)malloc(sizeof(int) * G.nv);
    path = (int *)malloc(sizeof(int) * G.nv);
    a_charge = (int *)malloc(sizeof(int) * G.nv);
    for (i = 0; i < G.nv; i++)
    {
        G.head[i].No = i;
        G.head[i].next = NULL;
        G.rear[i] = NULL;
        //
        short_distance[i] = INF;
        collect[i] = 0;
        path[i] = -1;
        a_charge[i] = INF;
    }
    //insert edge
    for (i = 0; i < G.ne; i++)
    {
        scanf("%d %d %d %d", &node1, &node2, &distance, &charge);
        if (G.rear[node1])
        {
            G.rear[node1]->next = (struct GNode *)malloc(sizeof(struct GNode));
            G.rear[node1] = G.rear[node1]->next;
        }
        else
        {
            G.rear[node1] = (struct GNode *)malloc(sizeof(struct GNode));
            G.head[node1].next = G.rear[node1];
        }
        G.rear[node1]->No = node2;
        G.rear[node1]->charge = charge;
        G.rear[node1]->distance = distance;
        G.rear[node1]->next = NULL;
        if (G.rear[node2])
        {
            G.rear[node2]->next = (struct GNode *)malloc(sizeof(struct GNode));
            G.rear[node2] = G.rear[node2]->next;
        }
        else
        {
            G.rear[node2] = (struct GNode *)malloc(sizeof(struct GNode));
            G.head[node2].next = G.rear[node2];
        }
        G.rear[node2]->No = node1;
        G.rear[node2]->charge = charge;
        G.rear[node2]->distance = distance;
        G.rear[node2]->next = NULL;
    }
    if (Dijkstra(&G, short_distance, collect, path, a_charge, Start, End))
    {
        printf("%d %d", short_distance[End], a_charge[End]);
    }
    else
        printf("%d\n", short_distance[End]);
    return (0);
}