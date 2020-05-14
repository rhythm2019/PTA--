/*
本题要求实现链式表的操作集。
函数接口定义：
Position Find( List L, ElementType X );
List Insert( List L, ElementType X, Position P );
List Delete( List L, Position P );
*/
/*
Position Find( List L, ElementType X )：返回线性表中首次出现X的位置。若找不到则返回ERROR；
List Insert( List L, ElementType X, Position P )：将X插入在位置P指向的结点之前，返回链表的表头。如果参数P指向非法位置，则打印“Wrong Position for Insertion”，返回ERROR；
List Delete( List L, Position P )：将位置P的元素删除并返回链表的表头。若参数P指向非法位置，则打印“Wrong Position for Deletion”并返回ERROR。
*/
#include <stdio.h>
#include <stdlib.h>
#define ERROR NULL
typedef int ElementType;
typedef struct LNode *PtrToLNode;
typedef struct LNode *List;
typedef struct LNode *Position;
struct LNode
{
    ElementType Data;
    PtrToLNode Next;
};
Position Find(List L, ElementType X);
List Insert(List L, ElementType X, Position P);
List Delete(List L, Position P);

int main()
{
    List L;
    ElementType X;
    Position P, tmp;
    int N;

    L = NULL;
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d", &X);
        L = Insert(L, X, L);
        if (L == ERROR)
            printf("Wrong Answer\n");
    }
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d", &X);
        P = Find(L, X);
        if (P == ERROR)
            printf("Finding Error: %d is not in.\n", X);
        else
        {
            L = Delete(L, P);
            printf("%d is found and deleted.\n", X);
            if (L == ERROR)
                printf("Wrong Answer or Empty List.\n");
        }
    }
    L = Insert(L, X, NULL);
    if (L == ERROR)
        printf("Wrong Answer\n");
    else
        printf("%d is inserted as the last element.\n", X);
    P = (Position)malloc(sizeof(struct LNode));
    tmp = Insert(L, X, P);
    if (tmp != ERROR)
        printf("Wrong Answer\n");
    tmp = Delete(L, P);
    if (tmp != ERROR)
        printf("Wrong Answer\n");
    for (P = L; P; P = P->Next)
        printf("%d ", P->Data);
    return 0;
}

Position Find(List L, ElementType X)
{
    while (L)
    {
        if (L->Data == X)
            return (L);
        else
            L = L->Next;
    }
    return (ERROR);
}

List Insert(List L, ElementType X, Position P)
{
    List cur = L, tmp;
    if (P == NULL) //tail insert
    {
        tmp = (List)malloc(sizeof(struct LNode));
        tmp->Next = NULL;
        tmp->Data = X;
        while (cur && cur->Next != NULL)
            cur = cur->Next;
        if (cur)
        {
            cur->Next = tmp;
            return (L);
        }
        else
            return (tmp);
    }
    else if (L == P || L == NULL)
    {
        tmp = (List)malloc(sizeof(struct LNode));
        tmp->Next = L;
        tmp->Data = X;
        return (tmp);
    }
    else
    {
        while (cur && cur->Next != P)
            cur = cur->Next;
        if (cur)
        {
            tmp = (List)malloc(sizeof(struct LNode));
            tmp->Next = cur->Next;
            tmp->Data = X;
            cur->Next = tmp;
            return (L);
        }
        else
        {
            printf("Wrong Position for Insertion\n");
            return (ERROR);
        }
    }
}

List Delete(List L, Position P)
{

    List cur = L, tmp;
    if (L == NULL)
        return (ERROR);
    else if (L == P)
        return (L->Next);
    else
    {
        while (cur && cur->Next != P)
            cur = cur->Next;
        if (cur)
        {
            tmp = cur->Next->Next;
            cur->Next = tmp;
            return (L);
        }
        else
        {
            printf("Wrong Position for Deletion\n");
            return (ERROR);
        }
    }
}