/*
计算机程序设计能力考试（Programming Ability Test，简称PAT）旨在通过统一组织的在线考试及自动评测方法客观地评判考生的算法设计与程序设计实现能力，科学的评价计算机程序设计人才，为企业选拔人才提供参考标准（网址http://www.patest.cn）。
每次考试会在若干个不同的考点同时举行，每个考点用局域网，产生本考点的成绩。考试结束后，各个考点的成绩将即刻汇总成一张总的排名表。
现在就请你写一个程序自动归并各个考点的成绩并生成总排名表。
DATE:20200725
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student
{
    char NO[14];
    int score;
    int place;
    int place_rank;
};
int cmpfunc(const void *a, const void *b)
{
    struct student *stu1, *stu2;
    stu1 = (struct student *)a;
    stu2 = (struct student *)b;
    if (stu1->score == stu2->score)
        return (strcmp(stu1->NO, stu2->NO));
    else
        return (stu2->score - stu1->score);
}
int main()
{
    int i, j, N, K, count = 0;
    struct student stu[30001];
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &K);
        for (j = 0; j < K; j++)
        {
            scanf("%s %d", &stu[count].NO, &stu[count].score);
            stu[count].place = i + 1;
            stu[count].place_rank = 1;
            count++;
        }
        qsort(stu + count - K, K, sizeof(struct student), cmpfunc);
        for (j = 1; j < K; j++)
        {
            if (stu[count - K + j].score == stu[count - K + j - 1].score)
                stu[count - K + j].place_rank = stu[count - K + j - 1].place_rank;
            else
                stu[count - K + j].place_rank = j + 1;
        }
    }
    qsort(stu, count, sizeof(struct student), cmpfunc);
    //
    printf("%d\n", count);
    j = 1;
    printf("%s %d %d %d\n", stu[0].NO, j, stu[0].place, stu[0].place_rank);
    for (i = 1; i < count; i++)
    {
        if (stu[i].score != stu[i - 1].score)
            j = i + 1;
        printf("%s %d %d %d\n", stu[i].NO, j, stu[i].place, stu[i].place_rank);
    }
    return (0);
}