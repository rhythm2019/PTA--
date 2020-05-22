/*
这个题目有点问题......
已知两个非降序链表序列S1与S2，设计函数构造出S1与S2的交集新链表S3。
*/
#include <stdio.h>
#include <stdlib.h>
#define ERROR NULL
typedef struct LNode *PtrToLNode;
typedef int ElementType;
struct LNode
{
    ElementType Data;
    PtrToLNode Next;
};
typedef struct _List
{
    PtrToLNode head, rear;
    int num;
} * List;
List MakeEmpty()
{
    List L = (List)malloc(sizeof(struct _List));
    L->head = NULL;
    L->rear = NULL;
    L->num = 0;
    return (L);
}
void input_List(List L)
{
    int tmp;
    PtrToLNode cur;
    while (1)
    {
        scanf("%d", &tmp);
        if (tmp == -1)
            return;
        cur = (PtrToLNode)malloc(sizeof(struct LNode));
        cur->Data = tmp;
        cur->Next = NULL;
        if (L->rear)
        {
            L->rear->Next = cur;
            L->rear = cur;
            (L->num)++;
        }
        else
        {
            L->rear = cur;
            L->head = cur;
            L->num = 1;
        }
    }
}
void print_list(List L)
{
    PtrToLNode cur;
    if (L == NULL || L->head == NULL)
    {
        printf("NULL");
        return;
    }
    cur = L->head;
    while (cur)
    {
        if (cur != L->rear)
            printf("%d ", cur->Data);
        else
            printf("%d", cur->Data);
        cur = cur->Next;
    }
    return;
}
void insert_list(List L, ElementType X)
{
    PtrToLNode cur = (PtrToLNode)malloc(sizeof(struct LNode));
    cur->Data = X;
    cur->Next = NULL;
    if (L->rear)
    {
        L->rear->Next = cur;
        L->rear = cur;
        (L->num)++;
    }
    else
    {
        L->rear = cur;
        L->head = cur;
        (L->num)++;
    }
    return;
}
int main()
{
    List L1, L2, L3;
    PtrToLNode p1, p2;
    L1 = MakeEmpty();
    L2 = MakeEmpty();
    L3 = MakeEmpty();
    input_List(L1);
    input_List(L2);
    p1 = L1->head;
    p2 = L2->head;
    //intersection
    while (p1 && p2)
    {
        if (p1->Data < p2->Data)
            p1 = p1->Next;
        else if (p1->Data > p2->Data)
            p2 = p2->Next;
        else
        {
            //if (L3->rear == NULL) || p1->Data > L3->rear->Data)
            insert_list(L3, p1->Data);
            p1 = p1->Next;
            p2 = p2->Next;
        }
    }
    print_list(L3);
    return (0);
}