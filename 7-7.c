/*
“六度空间”理论又称作“六度分隔（Six Degrees of Separation）”理论。
这个理论可以通俗地阐述为：“你和任何一个陌生人之间所间隔的人不会超过六个，也就是说，最多通过五个人你就能够认识任何一个陌生人。”如图1所示。
DATE:20200605
*/
#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 1001
struct GNode
{
    int NO; //节点数据
    struct GNode *next;
};
struct Graph
{
    int nv, ne;
    struct GNode G[MaxVertexNum];     //head
    struct GNode *rear[MaxVertexNum]; //tail
};

void dfs(struct Graph *G, int root, int visit[], int layer, int *countt)
{
    struct GNode *cur;
    cur = G->G[root].next;
    while (cur)
    {
        if (visit[cur->NO - 1] == 0 && layer < 6)
        {
            visit[cur->NO - 1] = 1;
            (*countt)++;
            dfs(G, cur->NO - 1, visit, layer + 1, countt);
        }
        cur = cur->next;
    }
    return;
}
int bfs(struct Graph *G, int root, int visit[])
{
    struct GNode *cur;
    int Queue[MaxVertexNum][2], begin = 0, end = 0;
    Queue[0][0] = root;
    Queue[0][1] = 0;
    while (begin <= end && Queue[begin][1] < 6)
    {

        cur = G->G[Queue[begin][0]].next;
        while (cur)
        {
            if (visit[cur->NO - 1] == 0)
            {
                Queue[++end][0] = cur->NO - 1;
                Queue[end][1] = Queue[begin][1] + 1;
                visit[cur->NO - 1] = 1;
            }
            cur = cur->next;
        }
        begin++;
    }
    return (end + 1);
}
int main()
{
    int i, j;
    int node1, node2, countt, visit[MaxVertexNum];
    struct Graph G;
    struct GNode *tmp;
    //init Graph
    scanf("%d %d", &(G.nv), &(G.ne));
    for (i = 0; i < G.nv; i++)
    {
        G.G[i].NO = i + 1;
        G.G[i].next = NULL;
        G.rear[i] = NULL;
    }
    // insert edge
    for (i = 0; i < G.ne; i++)
    {
        scanf("%d %d", &node1, &node2);
        tmp = (struct GNode *)malloc(sizeof(struct GNode));
        tmp->next = NULL;
        tmp->NO = node2;
        if (G.rear[node1 - 1] == NULL)
        {
            G.G[node1 - 1].next = tmp;
            G.rear[node1 - 1] = tmp;
        }
        else
        {
            G.rear[node1 - 1]->next = tmp;
            G.rear[node1 - 1] = tmp;
        }
        tmp = (struct GNode *)malloc(sizeof(struct GNode));
        tmp->next = NULL;
        tmp->NO = node1;
        if (G.rear[node2 - 1] == NULL)
        {
            G.G[node2 - 1].next = tmp;
            G.rear[node2 - 1] = tmp;
        }
        else
        {
            G.rear[node2 - 1]->next = tmp;
            G.rear[node2 - 1] = tmp;
        }
    }
    /*
    //dfs
    for (i = 0; i < G.nv; i++)
    {
        if (i)
            printf("\n");
        for (j = 0; j < G.nv; j++)
            visit[j] = 0;
        visit[i] = 1;
        countt = 1;
        dfs(&G, i, visit, 0, &countt);
        printf("%d: %.2lf%%", i + 1, 100.0 * countt / G.nv);
    }
    */

    //bfs
    for (i = 0; i < G.nv; i++)
    {
        if (i)
            printf("\n");
        for (j = 0; j < G.nv; j++)
            visit[j] = 0;
        visit[i] = 1;
        countt = bfs(&G, i, visit);
        printf("%d: %.2lf%%", i + 1, 100.0 * countt / G.nv);
    }
    return (0);
}