/*
某地区经过对城镇交通状况的调查，得到现有城镇间快速道路的统计数据，并提出“畅通工程”的目标：使整个地区任何两个城镇间都可以实现快速交通（但不一定有直接的快速道路相连，只要互相间接通过快速路可达即可）。
现得到城镇道路统计表，表中列出了任意两城镇间修建快速路的费用，以及该道路是否已经修通的状态。
现请你编写程序，计算出全地区畅通需要的最低成本。
DATE:2020805
*/
#include <stdio.h>
#include <stdlib.h>
// find and union
int find_parent(int *parent, int node)
{
    while (parent[node] != node)
        node = parent[node];
    return node;
}
int cmpfunc(const void *a, const void *b)
{
    return (((int *)a)[2] - ((int *)b)[2]);
}
int main()
{
    int i, nv, node1, node2, cost, Flag, count_edge = 0;
    int *parent, (*road)[3];
    //init
    scanf("%d", &nv);
    parent = (int *)malloc((nv + 1) * sizeof(int));
    road = (int(*)[3])malloc((nv * (nv - 1) / 2) * sizeof(int[3]));
    for (i = 1; i < nv + 1; i++)
        parent[i] = i;
    for (i = 0; i < (nv * (nv - 1) / 2); i++)
    {
        scanf("%d %d %d %d", &node1, &node2, &cost, &Flag);
        if (Flag)
        {
            if (find_parent(parent, node1) != find_parent(parent, node2))
                parent[find_parent(parent, node1)] = find_parent(parent, node2);
        }
        else
        {
            road[count_edge][0] = node1;
            road[count_edge][1] = node2;
            road[count_edge][2] = cost;
            count_edge++;
        }
    }
    qsort(road, count_edge, sizeof(int[3]), cmpfunc);
    cost = 0;
    i = 0;
    while (i < count_edge)
    {
        node1 = road[i][0];
        node2 = road[i][1];
        if (find_parent(parent, node1) != find_parent(parent, node2))
        {
            parent[find_parent(parent, node1)] = find_parent(parent, node2);
            cost += road[i][2];
        }
        i++;
    }
    printf("%d", cost);
    return (0);
}