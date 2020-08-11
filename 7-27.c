/*
人类学研究对于家族很感兴趣，于是研究人员搜集了一些家族的家谱进行研究。实验中，使用计算机处理家谱。
为了实现这个目的，研究人员将家谱转换为文本文件。下面为家谱文本文件的实例：
DATE:20200720
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 100
//
struct node
{
    char name[11];
    int level;
    int parent;
};
int find(struct node *man, int count, char name[11])
{
    int i = 0;
    while (i < count && strcmp(man[i].name, name))
        i++;
    if (i < count)
        return (i);
    else
        return (-1);
}
int main()
{
    int i, j, N, M, n1, n2;
    char s[200], m1[11], m2[11], relation[20];
    struct node man[MAXSIZE];
    scanf("%d %d", &N, &M);
    getchar();
    for (i = 0; i < N; i++)
    {

        gets(s);
        //
        j = 0;
        while (s[j] == ' ')
            j++;
        man[i].level = j / 2;
        strcpy(man[i].name, s + j);
        //
        if (i == 0)
            man[i].parent = -1;
        else if (man[i].level == man[i - 1].level)
            man[i].parent = man[i - 1].parent;
        else if (man[i].level > man[i - 1].level)
        {
            man[i].parent = i - 1;
        }
        else
        {
            j = i - 1;
            while (j >= 0 && man[j].level != man[i].level)
                j--;
            if (j >= 0)
                man[i].parent = man[j].parent;
        }
    }
    for (i = 0; i < M; i++)
    {
        scanf("%s %s %s %s %s %s", m1, s, s, relation, s, m2);
        n1 = find(man, N, m1);
        n2 = find(man, N, m2);
        if (strcmp(relation, "child") == 0)
            if (man[n1].parent == n2)
                printf("True\n");
            else
                printf("False\n");
        else if (strcmp(relation, "parent") == 0)
            if (man[n2].parent == n1)
                printf("True\n");
            else
                printf("False\n");
        else if (strcmp(relation, "sibling") == 0)
            if (man[n2].parent == man[n1].parent)
                printf("True\n");
            else
                printf("False\n");
        else if (strcmp(relation, "ancestor") == 0)
        {
            while (n2 >= 0 && man[n2].parent != n1)
                n2 = man[n2].parent;
            if (n2 >= 0)
                printf("True\n");
            else
                printf("False\n");
        }
        else if (strcmp(relation, "descendant") == 0)
        {
            while (n1 >= 0 && man[n1].parent != n2)
                n1 = man[n1].parent;
            if (n1 >= 0)
                printf("True\n");
            else
                printf("False\n");
        }
    }
    return (0);
}