/*
假定一个工程项目由一组子任务构成，子任务之间有的可以并行执行，有的必须在完成了其它一些子任务后才能执行。
“任务调度”包括一组子任务、以及每个子任务可以执行所依赖的子任务集。
比如完成一个专业的所有课程学习和毕业设计可以看成一个本科生要完成的一项工程，各门课程可以看成是子任务。
有些课程可以同时开设，比如英语和C程序设计，它们没有必须先修哪门的约束；有些课程则不可以同时开设，因为它们有先后的依赖关系，比如C程序设计和数据结构两门课，必须先学习前者。
但是需要注意的是，对一组子任务，并不是任意的任务调度都是一个可行的方案。
比如方案中存在“子任务A依赖于子任务B，子任务B依赖于子任务C，子任务C又依赖于子任务A”，那么这三个任务哪个都不能先执行，这就是一个不可行的方案。你现在的工作是写程序判定任何一个给定的任务调度是否可行。
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
};
//Top_sort
int toplogical_sort(int *indegree, int *queue, int end, struct Graph *G)
{
    int node1, node2, begin = 0;
    pnode cur;
    while (begin <= end)
    {
        node1 = queue[begin];
        cur = G->head[node1 - 1].next;
        while (cur)
        {
            node2 = cur->NO;
            indegree[node2 - 1]--;
            if (indegree[node2 - 1] == 0)
                queue[++end] = node2;
            cur = cur->next;
        }
        begin++;
    }
    return (end);
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
    int i, j, node1, queue[100] = {0}, indegree[100] = {0};
    int q_index = -1;
    struct Graph GG;
    scanf("%d", &GG.nv);
    //init
    GG.head = (pnode)malloc(GG.nv * sizeof(struct node));
    for (i = 0; i < GG.nv; i++)
    {
        (GG.head + i)->NO = i + 1;
        (GG.head + i)->next = NULL;
    }
    for (i = 0; i < GG.nv; i++)
    {
        scanf("%d", &indegree[i]);
        if (indegree[i] == 0)
            queue[++q_index] = i + 1;
        for (j = 0; j < indegree[i]; j++)
        {
            scanf("%d", &node1);
            insert_node(GG, node1, i + 1);
        }
    }
    q_index = toplogical_sort(indegree, queue, q_index, &GG);
    if (q_index == GG.nv - 1)
        printf("1");
    else
        printf("0");
    return (0);
}