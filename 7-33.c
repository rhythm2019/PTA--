/*
假设有一个地下通道迷宫，它的通道都是直的，而通道所有交叉点（包括通道的端点）上都有一盏灯和一个开关。请问你如何从某个起点开始在迷宫中点亮所有的灯并回到起点？
DATE:20200729
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
};
void dfs(struct Graph GG, int root, int visit[], int path[], int *count)
{
    int node;
    pnode cur;
    if (visit[root - 1] == 1)
        return;
    else
    {
        visit[root - 1] = 1;
        cur = GG.head[root - 1].next;
        path[*count] = root;
        (*count)++;
        while (cur)
        {
            node = cur->NO;
            if (visit[node - 1] == 0)
            {
                dfs(GG, node, visit, path, count);
                path[*count] = root;
                (*count)++;
            }
            cur = cur->next;
        }
    }

    return;
}
void insert_node(struct Graph GG, int n1, int n2)
{
    pnode cur, next;
    next = (pnode)malloc(sizeof(struct node));
    next->NO = n2;
    cur = &(GG.head[n1 - 1]);
    while (cur->next && cur->next->NO < n2)
        cur = cur->next;
    next->next = cur->next;
    cur->next = next;
    return;
}
int main()
{
    int i, root, count = 0, node1, node2, visit[1000] = {0}, path[5000];
    int Flag = 1;
    struct Graph GG;
    scanf("%d %d %d", &GG.nv, &GG.ne, &root);
    //init
    GG.head = (pnode)malloc(GG.nv * sizeof(struct node));
    for (i = 0; i < GG.nv; i++)
    {
        (GG.head + i)->NO = i + 1;
        (GG.head + i)->next = NULL;
    }
    for (i = 0; i < GG.ne; i++)
    {
        scanf("%d %d", &node1, &node2);
        insert_node(GG, node1, node2);
        insert_node(GG, node2, node1);
    }
    dfs(GG, root, visit, path, &count);
    for (i = 0; i < count - 1; i++)
        printf("%d ", path[i]);
    for (i = 0; i < GG.nv; i++)
    {
        Flag *= visit[i];
    }
    if (Flag == 0)
        printf("%d %d", path[count - 1], Flag);
    else
        printf("%d", path[count - 1]);
    return (0);
}