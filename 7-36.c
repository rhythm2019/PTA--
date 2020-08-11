/*
在社交网络中，个人或单位（结点）之间通过某些关系（边）联系起来。
他们受到这些关系的影响，这种影响可以理解为网络中相互连接的结点之间蔓延的一种相互作用，可以增强也可以减弱。
而结点根据其所处的位置不同，其在网络中体现的重要性也不尽相同。
DATE:20200804
*/
#include <stdio.h>
#include <stdlib.h>
#define maxNode 10001
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
void insert_node(struct Graph *GG, int n1, int n2)
{
    pnode cur, next = (pnode)malloc(sizeof(struct node));
    next->NO = n2;
    cur = &(GG->head[n1]);
    while (cur->next && cur->next->NO < n2)
        cur = cur->next;
    next->next = cur->next;
    cur->next = next;
    return;
}
//Dijkstravoid
float dijkstra(struct Graph *GG, int begin, int selected[], int shortDis[])
{
    int i, q_begin, q_end, curNode, nextNode, queue[maxNode];
    float averDist = 0.;
    pnode cur;
    q_end = 0;
    q_begin = 0;
    queue[q_begin] = begin;
    shortDis[begin] = 0;
    selected[begin] = 1;
    while (q_begin <= q_end)
    {
        curNode = queue[q_begin++];
        cur = GG->head[curNode].next;
        while (cur)
        {
            nextNode = cur->NO;
            if (selected[nextNode] == 0)
            {
                shortDis[nextNode] = shortDis[curNode] + 1;
                selected[nextNode] = 1;
                queue[++q_end] = nextNode;
                averDist += shortDis[nextNode];
            }
            cur = cur->next;
        }
    }
    if (q_end != GG->nv - 2)
        return (0.0);
    else
        return (q_end / averDist);
}
int main()
{
    int i, j, k, node1, node2;
    int begin, end;
    struct Graph GG;
    int selected[maxNode] = {0}, shortDis[maxNode];
    //input and init
    scanf("%d %d", &GG.nv, &GG.ne);
    GG.nv++;
    GG.head = (pnode)malloc(GG.nv * sizeof(struct node));
    for (i = 0; i < GG.nv; i++)
        GG.head[i].next = NULL;
    for (i = 0; i < GG.ne; i++)
    {
        scanf("%d %d", &node1, &node2);
        insert_node(&GG, node1, node2);
        insert_node(&GG, node2, node1);
    }
    //print
    scanf("%d", &k);
    for (i = 0; i < k; i++)
    {
        for (j = 0; j < GG.nv; j++)
            selected[j] = 0;
        scanf("%d", &begin);
        printf("Cc(%d)=%.2f\n", begin, dijkstra(&GG, begin, selected, shortDis));
    }
    return (0);
}