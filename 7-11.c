/*
假定一个工程项目由一组子任务构成，子任务之间有的可以并行执行，有的必须在完成了其它一些子任务后才能执行。
“任务调度”包括一组子任务、以及每个子任务可以执行所依赖的子任务集。
DATE:20200811
*/
#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 100
struct GEdge
{
    int No; //节点数据
    int time;
    struct GEdge *next;
};
struct Graph
{
    int nv, ne;
    struct GEdge head[MaxVertexNum]; //head
};

//Top_sort
int toplogical_sort(int *indegree, int *earliest, int *q1, int end, struct Graph *G)
{
    int node1, node2, begin = 0;
    struct GEdge *cur;
    while (begin <= end)
    {
        node1 = q1[begin];
        cur = G->head[node1 - 1].next;
        while (cur)
        {
            node2 = cur->No;
            indegree[node2 - 1]--;
            if (indegree[node2 - 1] == 0)
                q1[++end] = node2;
            if (earliest[node2 - 1] < cur->time + earliest[node1 - 1])
                earliest[node2 - 1] = cur->time + earliest[node1 - 1];
            cur = cur->next;
        }
        begin++;
    }
    return (end);
}

void antitoplogical_sort(int *latest, int *q1, int end, struct Graph *G)
{
    int node1, node2;
    struct GEdge *cur;
    while (end >= 0)
    {
        node1 = q1[end];
        cur = G->head[node1 - 1].next;
        while (cur)
        {
            node2 = cur->No;
            if (latest[node1 - 1] > latest[node2 - 1] - cur->time)
                latest[node1 - 1] = latest[node2 - 1] - cur->time;
            cur = cur->next;
        }
        end--;
    }
    return;
}

int get_edge(int node1, int node2, struct Graph *G)
{
    struct GEdge *cur = G->head[node1 - 1].next;
    while (cur && cur->No < node2)
        cur = cur->next;
    if (cur == NULL || cur->No > node2)
        return (0);
    else
        return (cur->time);
}

int main()
{
    int i, j, node1, node2, time;
    int earliest[MaxVertexNum] = {0}, latest[MaxVertexNum] = {0}, indegree[MaxVertexNum] = {0};
    int queue[MaxVertexNum], q_last = -1; //toporder
    int origin_num;
    struct Graph G;
    struct GEdge *cur, *next;
    //init
    scanf("%d %d", &G.nv, &G.ne);
    for (i = 0; i < G.nv; i++)
    {
        G.head[i].No = i + 1;
        G.head[i].next = NULL;
    }
    for (i = 0; i < G.ne; i++)
    {
        scanf("%d %d %d", &node1, &node2, &time);
        indegree[node2 - 1]++;
        cur = &(G.head[node1 - 1]);
        next = cur->next;
        while (next && node2 > next->No)
        {
            cur = next;
            next = cur->next;
        }
        cur->next = (struct GEdge *)malloc(sizeof(struct GEdge));
        cur->next->No = node2;
        cur->next->time = time;
        cur->next->next = next;
    }
    //search indegree=0
    for (i = 0; i < G.nv; i++)
        if (indegree[i] == 0)
            queue[++q_last] = i + 1;
    origin_num = q_last + 1;
    //toplogical sort
    q_last = toplogical_sort(indegree, earliest, queue, q_last, &G);
    if (q_last < G.nv - 1)
    {
        printf("0");
        return (0);
    }
    for (i = 0; i < G.nv; i++)
        latest[i] = earliest[queue[q_last] - 1];
    antitoplogical_sort(latest, queue, q_last, &G);
    //search and print key route
    printf("%d\n", earliest[queue[q_last] - 1]);
    for (i = 0; i < G.nv; i++)
        for (j = G.nv - 1; j >= 0; j--)
        {
            if (get_edge(i + 1, j + 1, &G) && latest[j] - get_edge(i + 1, j + 1, &G) <= earliest[i])
                printf("%d->%d\n", i + 1, j + 1);
        }
    return (0);
}