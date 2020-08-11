/*
假设全校有最多40000名学生和最多2500门课程。现给出每门课的选课学生名单，要求输出每个前来查询的学生的选课清单。
DATE:20200731
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXNUMBER (26 * 26 * 26 * 10)
struct course
{
    int No;
    struct course *next;
};
int main()
{
    int i, j, N, K, course;
    int pos;
    struct course student[MAXNUMBER] = {0, NULL}, *cur, *tmp;
    char name[5];
    scanf("%d %d", &N, &K);
    for (i = 0; i < K; i++)
    {
        scanf("%d %d", &course, &j);
        while (j-- > 0)
        {
            scanf("%s", name);
            tmp = (struct course *)malloc(sizeof(struct course));
            tmp->No = course;
            pos = (name[0] - 'A') * 6760 + (name[1] - 'A') * 260 + (name[2] - 'A') * 10 + name[3] - '0';
            cur = student + pos;
            cur->No++;
            while (cur->next && course > cur->next->No)
                cur = cur->next;
            tmp->next = cur->next;
            cur->next = tmp;
        }
    }
    for (i = 0; i < N; i++)
    {
        scanf("%s", name);
        pos = (name[0] - 'A') * 6760 + (name[1] - 'A') * 260 + (name[2] - 'A') * 10 + name[3] - '0';
        printf("%s %d", name, student[pos].No);
        if (student[pos].No)
        {
            printf(" ");
            cur = (student + pos)->next;
            for (j = 0; j < student[pos].No - 1; j++)
            {
                printf("%d ", cur->No);
                cur = cur->next;
            }
            printf("%d\n", cur->No);
        }
        else
            printf("\n");
    }
    return (0);
}