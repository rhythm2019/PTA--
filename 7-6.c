/*
给定一个有N个顶点和E条边的无向图，请用DFS和BFS分别列出其所有的连通集。假设顶点从0到N−1编号。
进行搜索时，假设我们总是从编号最小的顶点出发，按编号递增的顺序访问邻接点。
输入格式:
输入第1行给出2个整数N(0<N≤10)和E，分别是图的顶点数和边数。随后E行，每行给出一条边的两个端点。每行中的数字之间用1空格分隔。
DATE:20200604
*/
#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 100 /* 最大顶点数设为100 */
typedef int Vertex;      /* 用顶点下标表示顶点,为整型 */
typedef int WeightType;  /* 边的权值设为整型 */
typedef char DataType;   /* 顶点存储的数据类型设为字符型 */
struct Graph
{
    int nv, ne;
    WeightType G[MaxVertexNum][MaxVertexNum];
    // DataType Data[MaxVertexNum];
};

void dfs(struct Graph *G, int root, int visit[])
{
    int i;
    for (i = 0; i < G->nv; i++)
    {
        if (G->G[root][i] == 1 && visit[i] == 0)
        {
            visit[i] = 1;
            printf("%d ", i);
            dfs(G, i, visit);
        }
    }
    return;
}
void bfs(struct Graph *G, int root, int visit[])
{
    int Queue[MaxVertexNum], i, begin = 0, end = 0;
    Queue[0] = root;
    while (begin <= end)
    {
        printf("%d ", Queue[begin]);
        for (i = 0; i < G->nv; i++)
        {
            if (visit[i] == 0 && G->G[Queue[begin]][i] == 1)
            {
                Queue[++end] = i;
                visit[i] = 1;
            }
        }
        begin++;
    }
    return;
}

int main()
{
    int nnode, nedge, i, j;
    int node1, node2;
    int visit[MaxVertexNum] = {0};
    struct Graph G;
    scanf("%d %d", &nnode, &nedge);
    //init Graph
    G.nv = nnode;
    G.ne = nedge;
    for (i = 0; i < G.nv; i++)
        for (j = 0; j < G.nv; j++)
            G.G[i][j] = 0;
    // insert edge
    for (i = 0; i < nedge; i++)
    {
        scanf("%d %d", &node1, &node2);
        G.G[node1][node2] = 1;
        G.G[node2][node1] = 1;
    }
    //dfs
    for (i = 0; i < G.nv; i++)
    {
        if (visit[i] == 0)
        {
            printf("{ %d ", i);
            visit[i] = 1;
            dfs(&G, i, visit);
            printf("}\n");
        }
    }
    //bfs
    for (i = 0; i < G.nv; i++)
        visit[i] = 0;
    for (i = 0; i < G.nv; i++)
    {
        if (visit[i] == 0)
        {
            printf("{ ", i);
            visit[i] = 1;
            bfs(&G, i, visit);
            printf("}\n");
        }
    }
    return (0);
}