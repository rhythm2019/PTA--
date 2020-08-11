/*
假设全校有最多40000名学生和最多2500门课程。现给出每个学生的选课清单，要求输出每门课的选课学生名单。
DATE:20200731
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct Stu
{
    char name[5];
    int N[21];
};
struct Node
{
    char name[5];
    struct Node *next;
};
/*
void insert_stu(struct Node *lesson, char *name, int course)
{
    struct Node *cur, *tmp = (struct Node *)malloc(sizeof(struct Node));
    strcpy(tmp->name, name);
    cur = lesson + course - 1;
    while (cur->next && strcmp(name, cur->next->name) > 0)
        cur = cur->next;
    tmp->next = cur->next;
    cur->next = tmp;
    return;
}
*/
int cmpfunc(const void *a, const void *b)
{
    return (strcmp(((struct Stu *)a)->name, ((struct Stu *)b)->name));
}
void insert_stu(struct Node *lesson, char *name, int course)
{
    struct Node *cur = lesson + course - 1, *tmp = (struct Node *)malloc(sizeof(struct Node));
    strcpy(tmp->name, name);    
    tmp->next = cur->next;
    cur->next = tmp;
    return;
}

int main()
{
    struct Node *lesson, *tmp;
    struct Stu *student;
    int i, j, N, K, course, *count;
    char name[5];
    scanf("%d %d", &N, &K);
    lesson = (struct Node *)malloc(K * sizeof(struct Node));
    count = (int *)malloc(K * sizeof(int));
    student = (struct Stu *)malloc(N * sizeof(struct Stu));
    for (i = 0; i < K; i++)
    {
        lesson[i].next = NULL;
        count[i] = 0;
    }
    for (i = 0; i < N; i++)
    {
        scanf("%s %d", &student[i].name, &student[i].N[0]);
        for (j = 1; j <= student[i].N[0]; j++)
            scanf("%d", &student[i].N[j]);
    }
    qsort(student, N, sizeof(struct Stu), cmpfunc);
    for (i = N - 1; i >= 0; i--)
    {
        for (j = 1; j <= student[i].N[0]; j++)
        {
            insert_stu(lesson, student[i].name, student[i].N[j]);
            count[student[i].N[j] - 1]++;
        }
    }
    /*
    for (i = 0; i < N; i++)
    {
        scanf("%s %d", name, &j);
        while (j--)
        {
            scanf("%d", &course);
            insert_stu(lesson, name, course);
            count[course - 1]++;
        }
    }
    */
    for (i = 0; i < K; i++)
    {
        printf("%d %d\n", i + 1, count[i]);
        tmp = (lesson + i)->next;
        for (j = 0; j < count[i]; j++)
        {
            printf("%s\n", tmp->name);
            tmp = tmp->next;
        }
    }
    return (0);
}