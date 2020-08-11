/*
现有村落间道路的统计数据表中，列出了有可能建设成标准公路的若干条道路的成本，求使每个村落都有公路连通所需要的最低成本。
输入数据包括城镇数目正整数N（≤1000）和候选道路数目M（≤3N）；
随后的M行对应M条道路，每行给出3个正整数，分别是该条道路直接连通的两个城镇的编号以及该道路改建的预算成本。为简单起见，城镇从1到N编号。
DATE:20200730
*/
#include <stdio.h>
#include <stdlib.h>
// edge and min_heap
struct edge
{
    int node1, node2;
    int cost;
};
typedef struct edge ElementType;
typedef struct HNode *Heap; /* 堆的类型定义 */
typedef Heap MinHeap;       /* 最小堆 */
struct HNode
{
    ElementType *Data; /* 存储元素的数组 */
    int Size;          /* 堆中当前元素个数 */
    int Capacity;      /* 堆的最大容量 */
};
MinHeap init_heap(int N)
{
    MinHeap H;
    if (N)
    {
        H = (MinHeap)malloc(sizeof(struct HNode));
        H->Data = (ElementType *)malloc((N + 1) * sizeof(ElementType));
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
void PercDown(MinHeap H, int index)
{
    ElementType tmp;
    if (2 * index + 1 <= H->Size && H->Data[2 * index + 1].cost < H->Data[2 * index].cost && H->Data[2 * index + 1].cost < H->Data[index].cost)
    {
        tmp = H->Data[2 * index + 1];
        H->Data[2 * index + 1] = H->Data[index];
        H->Data[index] = tmp;
        PercDown(H, 2 * index + 1);
    }
    else if (2 * index <= H->Size && H->Data[2 * index].cost < H->Data[index].cost)
    {
        tmp = H->Data[2 * index];
        H->Data[2 * index] = H->Data[index];
        H->Data[index] = tmp;
        PercDown(H, 2 * index);
    }
    else
        return;
}
int delete_min(MinHeap H)
{
    if (H->Size)
    {
        H->Data[0] = H->Data[H->Size--];
        PercDown(H, 0);
        return (1);
    }
    else
        return (0);
}
int build_heap(MinHeap H)
{
    int i;
    for (i = H->Size / 2; i > 0; i--)
        PercDown(H, i);
    return (1);
}
// find and union
int find_parent(int *parent, int node)
{
    while (parent[node] != node)
        node = parent[node];
    return node;
}
int main()
{
    int i, nv, ne;
    int count_edge = 0, cost = 0;
    int *parent;
    MinHeap H;
    //init
    scanf("%d %d", &nv, &ne);
    parent = (int *)malloc((nv + 1) * sizeof(int));
    H = init_heap(ne);
    for (i = 0; i < nv + 1; i++)
        parent[i] = i;
    for (i = 1; i < ne + 1; i++)
        scanf("%d %d %d", &H->Data[i].node1, &H->Data[i].node2, &H->Data[i].cost);
    H->Size = ne;
    build_heap(H);
    while (!IsEmpty(H) && count_edge < nv - 1)
    //while (!IsEmpty(H))
    {
        if (find_parent(parent, H->Data[1].node1) != find_parent(parent, H->Data[1].node2))
        {
            parent[find_parent(parent, H->Data[1].node1)] = find_parent(parent, H->Data[1].node2);
            count_edge++;
            cost += H->Data[1].cost;
            //printf("%d---%d---%d\n", H->Data[1].node1, H->Data[1].node2, H->Data[1].cost);
        }
        delete_min(H);
    }
    if (count_edge == nv - 1)
        printf("%d", cost);
    else
        printf("-1");
    return (0);
}