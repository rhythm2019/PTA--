/*
每年奥运会各大媒体都会公布一个排行榜，但是细心的读者发现，不同国家的排行榜略有不同。
比如中国金牌总数列第一的时候，中国媒体就公布“金牌榜”；而美国的奖牌总数第一，于是美国媒体就公布“奖牌榜”。
如果人口少的国家公布一个“国民人均奖牌榜”，说不定非洲的国家会成为榜魁…… 现在就请你写一个程序，对每个前来咨询的国家按照对其最有利的方式计算它的排名。
DATE:20200725
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct country
{
    int ID;
    int gold, medal, population;
    float avergold, avermedal;
    int rank[4];
};
int cmpfunc_01(const void *a, const void *b)
{
    return (((struct country *)b)->gold - ((struct country *)a)->gold);
}
int cmpfunc_02(const void *a, const void *b)
{
    return (((struct country *)b)->medal - ((struct country *)a)->medal);
}
int cmpfunc_05(const void *a, const void *b)
{
    return (((struct country *)a)->ID - ((struct country *)b)->ID);
}
int cmpfunc_03(const void *a, const void *b)
{
    struct country *c1, *c2;
    c1 = (struct country *)a;
    c2 = (struct country *)b;
    if (c1->avergold > c2->avergold)
        return (-1);
    else if (c1->avergold < c2->avermedal)
        return (1);
    else
        return (0);
}
int cmpfunc_04(const void *a, const void *b)
{
    struct country *c1, *c2;
    c1 = (struct country *)a;
    c2 = (struct country *)b;
    if (c1->avermedal > c2->avermedal)
        return (-1);
    else if (c1->avermedal < c2->avermedal)
        return (1);
    else
        return (0);
}

int main()
{
    int i, j, k, N, M, minindex, minrank;
    struct country stu[224];
    int (*cmp[5])(const void *, const void *) = {cmpfunc_01, cmpfunc_02, cmpfunc_03, cmpfunc_04, cmpfunc_05};
    scanf("%d %d", &N, &M);
    for (i = 0; i < N; i++)
    {
        scanf("%d %d %d", &(stu[i].gold), &(stu[i].medal), &(stu[i].population));
        stu[i].ID = i;
        stu[i].avergold = 1.0 * stu[i].gold / stu[i].population;
        stu[i].avermedal = 1.0 * stu[i].medal / stu[i].population;
    }
    for (i = 0; i < 4; i++)
    {
        qsort(stu, N, sizeof(struct country), cmp[i]);
        stu[0].rank[i] = 1;
        k = 1;
        for (j = 1; j < N; j++)
        {
            switch (i)
            {
            case 0:
                if (stu[j].gold < stu[j - 1].gold)
                    k = j + 1;
                break;
            case 1:
                if (stu[j].medal < stu[j - 1].medal)
                    k = j + 1;
                break;
            case 2:
                if (stu[j].avergold < stu[j - 1].avergold)
                    k = j + 1;
                break;
            case 3:
                if (stu[j].avermedal < stu[j - 1].avermedal)
                    k = j + 1;
                break;
            }
            stu[j].rank[i] = k;
        }
    }
    qsort(stu, N, sizeof(struct country), cmp[4]);
    //print
    for (i = 0; i < M; i++)
    {
        scanf("%d", &j); //ID
        minrank = N + 1;
        for (k = 0; k < 4; k++)
        {
            if (stu[j].rank[k] < minrank)
            {
                minrank = stu[j].rank[k];
                minindex = k;
            }
        }
        printf("%d:%d", minrank, minindex + 1);
        if (i < M - 1)
            printf(" ");
    }
    return (0);
}