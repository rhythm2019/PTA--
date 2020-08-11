/*
在ZIP归档文件中，保留着所有压缩文件和目录的相对路径和名称。当使用WinZIP等GUI软件打开ZIP归档文件时，可以从这些信息中重建目录的树状结构。
请编写程序实现目录的树状结构的重建工作。
DATE:20200722
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node *pnode;
struct node
{
    char name[261];
    int type;    //0->dir,1->file
    pnode child; //子目录、子文件
    pnode next;  //同级别的，相同parent
};

int cmpnode(pnode node1, char name[], int type)
{
    if (node1->type != type)
        return (node1->type - type);
    else
        return (strcmp(node1->name, name));
}
pnode insert(pnode root, char name[], int type) //search and insert
{
    pnode cur = root, tmp;
    if (cur == NULL)
        return (NULL);
    //search
    tmp = (pnode)malloc(sizeof(struct node));
    strcpy(tmp->name, name);
    tmp->type = type;

    if (cur->child == NULL || cmpnode(cur->child, name, type) > 0) //insert child
    {
        tmp->child = NULL;
        tmp->next = cur->child;
        cur->child = tmp;
        return (tmp);
    }
    else if (cmpnode(cur->child, name, type) == 0)
    {
        free(tmp);
        return (cur->child);
    }
    else //search in next
    {
        cur = cur->child;
        while (cur->next && cmpnode(cur->next, name, type) < 0)
            cur = cur->next;
        if (cur->next == NULL || cmpnode(cur->next, name, type) > 0)
        {
            tmp->child = NULL;
            tmp->next = cur->next;
            cur->next = tmp;
            return (tmp);
        }
        else
        {
            free(tmp);
            return (cur->next);
        }
    }
}
char *get_blank(char s[], int n)
{
    int i;
    for (i = 0; i < n; i++)
        s[i] = ' ';
    s[n] = '\0';
    return s;
}
void print_dir(pnode root, int level)
{
    pnode cur = root;
    char s[261];
    if (root)
    {
        printf("%s%s\n", get_blank(s, level), root->name);
        print_dir(cur->child, level + 2);
        print_dir(cur->next, level);
    }
    return;
}
int main()
{
    int i, j, k, N;
    char input[261];
    struct node root = {"root", 0, NULL, NULL};
    pnode cur;
    //
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%s", input);
        cur = &root;
        j = 0;
        k = 0;
        while (1)
        {
            while (input[j] != '\0' && input[j] != '\\')
                j++;
            if (input[j] == '\\' && k != j)
            {
                input[j] = '\0';
                cur = insert(cur, input + k, 0);
                k = j + 1;
                j++;
            }
            else if (input[j] == '\0')
            {
                if (k != j)
                    insert(cur, input + k, 1);
                break;
            }
        }
    }
    print_dir(&root, 0);
    return (0);
}