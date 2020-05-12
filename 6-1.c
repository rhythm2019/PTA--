/*
本题要求实现一个函数，将给定的单链表逆转。
函数接口定义：
List Reverse( List L );
其中List结构定义如下：
typedef struct Node *PtrToNode;
struct Node {
    ElementType Data; 
    PtrToNode Next;
};
typedef PtrToNode List;
L是给定单链表，函数Reverse要返回被逆转后的链表。
*/
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node
{
    ElementType Data;
    PtrToNode Next;
};
typedef PtrToNode List;

List Read();        /* 细节在此不表 */
void Print(List L); /* 细节在此不表 */
List Reverse(List L);
int main()
{
    List L1, L2;
    L1 = Read();
    L2 = Reverse(L1);
    Print(L1);
    Print(L2);
    return 0;
}
List Reverse(List L)
{
    List cur, next, nnext;
    if (L == NULL)
        return NULL;
    cur = L;
    next = L->Next;
    cur->Next = NULL;
    while (next != NULL)
    {
        nnext = next->Next;
        next->Next = cur;
        cur = next;
        next = nnext;
    }
    return cur;
}