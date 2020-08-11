/*
作为一个城市的应急救援队伍的负责人，你有一张特殊的全国地图。
在地图上显示有多个分散的城市和一些连接城市的快速道路。
每个城市的救援队数量和每一条连接两个城市的快速道路长度都标在地图上。
当其他城市有紧急求助电话给你的时候，你的任务是带领你的救援队尽快赶往事发地，同时，一路上召集尽可能多的救援队。
DATE:20200801
*/
#include <stdio.h>
#include <stdlib.h>
#define maxNode 500
#define maxDis 250001
struct PATH
{
    int NO;       //上一个节点
    int shortNum; //shortest path Num数目
};
//Dijkstra
void dijkstra(int GG[][maxNode], int nv, int begin, int end, int selected[], int shortDis[], int people[], int teampeople[], struct PATH path[])
{
    int i, mindis, curNode = begin, nextNode;
    shortDis[begin] = 0;
    while (1)
    {
        selected[curNode] = 1;
        if (curNode == end || curNode == -1)
            break;
        for (i = 0; i < nv; i++)
        {
            nextNode = i;
            if (selected[nextNode] == 0 && GG[curNode][nextNode])
                if (shortDis[curNode] + GG[curNode][nextNode] < shortDis[nextNode])
                {
                    path[nextNode].shortNum = path[curNode].shortNum;
                    path[nextNode].NO = curNode;
                    shortDis[nextNode] = shortDis[curNode] + GG[curNode][nextNode];
                    teampeople[nextNode] = teampeople[curNode] + people[nextNode];
                }
                else if (shortDis[curNode] + GG[curNode][nextNode] == shortDis[nextNode])
                {
                    path[nextNode].shortNum += path[curNode].shortNum;
                    if (teampeople[nextNode] < teampeople[curNode] + people[nextNode])
                    {
                        teampeople[nextNode] = teampeople[curNode] + people[nextNode];
                        path[nextNode].NO = curNode;
                    }
                }
        }
        //find next node in shprtDis;
        curNode == -1;
        mindis = maxDis;
        for (i = 0; i < nv; i++)
        {
            if (selected[i] == 0 && shortDis[i] < mindis)
            {
                curNode = i;
                mindis = shortDis[i];
            }
        }
    }
    return;
}
int main()
{
    int i, j, node1, node2, dist;
    int nv, ne, begin, end;
    int GG[maxNode][maxNode] = {0};
    int selected[maxNode] = {0}, people[maxNode], teampeople[maxNode], shortDis[maxNode];
    struct PATH path[maxNode];
    //input and init
    scanf("%d %d %d %d", &nv, &ne, &begin, &end);
    for (i = 0; i < nv; i++)
    {
        scanf("%d", &people[i]);
        teampeople[i] = people[i];
        shortDis[i] = maxDis;
        path[i].NO = -1;
        path[i].shortNum = 0;
    }
    for (i = 0; i < ne; i++)
    {
        scanf("%d %d %d", &node1, &node2, &dist);
        GG[node1][node2] = dist;
        GG[node2][node1] = dist;
    }
    path[begin].shortNum = 1;
    dijkstra(GG, nv, begin, end, selected, shortDis, people, teampeople, path);
    //print result
    printf("%d %d\n", path[end].shortNum, teampeople[end]);
    i = 0;
    people[i] = end; //路径queue
    while (path[end].NO != -1)
    {
        end = path[end].NO;
        people[++i] = end;
    }
    for (j = i; j > 0; j--)
        printf("%d ", people[j]);
    printf("%d", people[0]);
    return (0);
}