/*
本题要求实现一个函数，求链式表的表长。
*/
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode
{
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode List;
List Read(); /* 细节在此不表 */
int Length(List L);
int main()
{
    List L = Read();
    printf("%d\n", Length(L));
    return 0;
}
int Length(List L)
{
    int count = 1;
    if (L == NULL)
        return 0;
    while (L->Next)
    {
        count++;
        L = L->Next;
    }
    return count;
}
