/*
输入的第一行包含两个正整数N(≤10^​5)和C，其中N是纪录的条数，C是指定排序的列号。之后有 N行，每行包含一条学生纪录。
每条学生纪录由学号（6位数字，保证没有重复的学号）、姓名（不超过8位且不包含空格的字符串）、成绩（[0, 100]内的整数）组成，相邻属性用1个空格隔开。
DATE:20200727
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Cutoff 50
struct student
{
    char No[7];
    char Name[9];
    int score;
};
typedef struct student *pstudent;
void swap(struct student A[], int i, int j)
{
    struct student tmp;
    memcpy(&tmp, A + i, sizeof(struct student));
    memcpy(A + i, A + j, sizeof(struct student));
    memcpy(A + j, &tmp, sizeof(struct student));
    return;
}
void insert_sort(struct student A[], int left, int right, int (*cmpfunc)(pstudent, pstudent))
{
    int i, j, k;
    struct student tmp;
    //int key;
    for (i = left + 1; i <= right; i++)
    {
        j = i - 1;
        while (j >= left && cmpfunc(A + j, A + i) > 0)
            j--;
        memcpy(&tmp, A + i, sizeof(struct student));
        for (k = i; k > j + 1; k--)
            memcpy(A + k, A + k - 1, sizeof(struct student));
        memcpy(A + j + 1, &tmp, sizeof(struct student));
    }
    return;
}
void quick_sort(struct student A[], int left, int right, int (*cmpfunc)(pstudent, pstudent))
{
    int i, j, k, center = (left + right) / 2;
    int pivot;
    if (right <= left)
        return;
    if (right - left < Cutoff)
        insert_sort(A, left, right, cmpfunc);
    else
    {
        //search pivot
        if (cmpfunc(A + left, A + center) > 0)
            swap(A, left, center);
        if (cmpfunc(A + left, A + right) > 0)
            swap(A, left, right);
        if (cmpfunc(A + center, A + right) > 0)
            swap(A, center, right);
        swap(A, center, right - 1);
        //quick sort
        i = left + 1;
        j = right - 2;
        while (1)
        {
            while (cmpfunc(A + i, A + right - 1) < 0)
                i++;
            while (cmpfunc(A + j, A + right - 1) > 0)
                j--;
            if (i < j)
            {
                swap(A, i, j);
                i++;
                j--;
            }
            else
                break;
        }
        swap(A, i, right - 1);
        quick_sort(A, left, i - 1, cmpfunc);
        quick_sort(A, i + 1, right, cmpfunc);
    }
    return;
}
int cmp_01(pstudent s1, pstudent s2)
{
    return (strcmp(s1->No, s2->No));
}
int cmp_02(pstudent s1, pstudent s2)
{
    if (strcmp(s1->Name, s2->Name) == 0)
        return (strcmp(s1->No, s2->No));
    else
        return (strcmp(s1->Name, s2->Name));
}
int cmp_03(pstudent s1, pstudent s2)
{
    if (s1->score == s2->score)
        return (strcmp(s1->No, s2->No));
    else
        return (s1->score - s2->score);
}
int main()
{
    int i, N, C;
    struct student stu[100000];
    scanf("%d %d", &N, &C);
    for (i = 0; i < N; i++)
        scanf("%s %s %d", stu[i].No, stu[i].Name, &stu[i].score);
    switch (C)
    {
    case 1:
        quick_sort(stu, 0, N - 1, cmp_01);
        break;
    case 2:
        quick_sort(stu, 0, N - 1, cmp_02);
        break;
    case 3:
        quick_sort(stu, 0, N - 1, cmp_03);
        break;
    }
    for (i = 0; i < N; i++)
        printf("%s %s %d\n", stu[i].No, stu[i].Name, stu[i].score);
    return (0);
}