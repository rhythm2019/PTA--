/*
7-19 求链式线性表的倒数第K项 (20分)
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct Node *LNode;
struct Node
{
    int num;
    LNode next;
};
void insert_Node(LNode head, struct Node **rear, int data)
{
    LNode tmp;
    tmp = (LNode)malloc(sizeof(struct Node));
    tmp->next = NULL;
    tmp->num = data;
    if (*rear)
    {
        (*rear)->next = tmp;
        (*rear) = tmp;
        head->num++;
    }
    else
    {
        head->num++;
        head->next = tmp;
        (*rear) = tmp;
    }
    return;
}
void free_Node(LNode head)
{
    LNode tmp = head->next, tmp1;
    while (tmp)
    {
        tmp1 = tmp->next;
        free(tmp);
        tmp = tmp1;
    }
    return;
}
int main()
{
    LNode head, rear;
    int K, tmp;
    head = (LNode)malloc(sizeof(struct Node));
    head->num = 0;
    head->next = NULL;
    rear = NULL;
    scanf("%d", &K);
    scanf("%d", &tmp);
    while (tmp >= 0)
    {
        insert_Node(head, &rear, tmp);
        scanf("%d", &tmp);
    }
    if (K > head->num)
        printf("NULL");
    else
    {
        K = head->num - K + 1;
        tmp = 1;
        rear = head->next;
        while (tmp < K)
        {
            rear = rear->next;
            tmp++;
        }
        printf("%d", rear->num);
    }
    free_Node(head);
    return (0);
}