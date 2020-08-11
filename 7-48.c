/*
队“夹塞”是引起大家强烈不满的行为，但是这种现象时常存在。在银行的单窗口排队问题中，假设银行只有1个窗口提供服务，所有顾客按到达时间排成一条长龙。当窗口空闲时，下一位顾客即去该窗口处理事务。此时如果已知第i位顾客与排在后面的第j位顾客是好朋友，并且愿意替朋友办理事务的话，那么第i位顾客的事务处理时间就是自己的事务加朋友的事务所耗时间的总和。在这种情况下，顾客的等待时间就可能被影响。
假设所有人到达银行时，若没有空窗口，都会请求排在最前面的朋友帮忙（包括正在窗口接受服务的朋友）；
当有不止一位朋友请求某位顾客帮忙时，该顾客会根据自己朋友请求的顺序来依次处理事务。试编写程序模拟这种现象，并计算顾客的平均等待时间。
DATE:20200802
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define maxNode (26 * 26 * 26)
struct Customer
{
    char Name[4];
    int parent, t0, p, t1, t2;
};
int get_index(char name[])
{
    return ((name[0] - 'A') * 676 + (name[1] - 'A') * 26 + name[2] - 'A');
}
int main()
{
    int i, j, k, c1, c2, nn, nm, waittime = 0;
    struct Customer custom[maxNode];
    char name1[4], name2[4];
    int *queue;
    //input and init
    scanf("%d %d", &nn, &nm);
    queue = (int *)malloc(nn * sizeof(int));
    for (i = 0; i < nn; i++)
        custom[i].parent = i;
    for (i = 0; i < nm; i++)
    {
        scanf("%d %s", &j, name1);
        c1 = get_index(name1);
        strcpy(custom[c1].Name, name1);
        custom[c1].parent = c1;
        while (j > 1)
        {
            scanf("%s", name2);
            c2 = get_index(name2);
            strcpy(custom[c2].Name, name1);
            custom[c2].parent = c1;
            j--;
        }
    }
    for (i = 0; i < nn; i++)
    {
        scanf("%s", name1);
        c1 = get_index(name1);
        strcpy(custom[c1].Name, name1);
        scanf("%d %d", &custom[c1].t0, &custom[c1].p);
        if (custom[c1].p > 60)
            custom[c1].p = 60;
        queue[i] = c1;
    }
    i = 0;
    c1 = queue[0];
    custom[c1].t1 = custom[c1].t0;
    custom[c1].t2 = custom[c1].t1 + custom[c1].p;
    while (i < nn)
    {
        c1 = queue[i];
        if (i)
        {
            if (custom[c1].t0 > custom[queue[i - 1]].t2)
                custom[c1].t1 = custom[c1].t0;
            else
                custom[c1].t1 = custom[queue[i - 1]].t2;
            custom[c1].t2 = custom[c1].t1 + custom[c1].p;
        }
        for (j = i + 1; j < nn; j++)
        {
            c2 = queue[j];
            if (custom[c2].t0 <= custom[c1].t2 && custom[c2].parent == custom[c1].parent)
            {
                custom[c2].t1 = custom[c1].t2;
                custom[c2].t2 = custom[c2].t1 + custom[c2].p;
                for (k = j; k > i + 1; k--)
                    queue[k] = queue[k - 1];
                queue[++i] = c2;
                c1 = c2;
            }
            else if (custom[c2].t0 > custom[c1].t2)
                break;
        }
        i++;
    }
    //print result
    for (i = 0; i < nn; i++)
    {
        waittime += (custom[queue[i]].t1 - custom[queue[i]].t0);
        printf("%s\n", custom[queue[i]].Name);
    }
    printf("%.1f", 1.0 * waittime / nn);
    return (0);
}