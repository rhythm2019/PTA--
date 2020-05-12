/*
本题要求实现一个函数，找到并返回链式表的第K个元素。
函数接口定义：
ElementType FindKth( List L, int K );
*/
#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
typedef int ElementType;
typedef struct LNode *PtrToLNode;
struct LNode
{
    ElementType Data;
    PtrToLNode Next;
};
typedef PtrToLNode List;
List Read(); /* 细节在此不表 */
ElementType FindKth(List L, int K);
int main()
{
    int N, K;
    ElementType X;
    List L = Read();
    scanf("%d", &N);
    while (N--)
    {
        scanf("%d", &K);
        X = FindKth(L, K);
        if (X != ERROR)
            printf("%d ", X);
        else
            printf("NA ");
    }
    return 0;
}
ElementType FindKth(List L, int K)
{
    int count = 1;
    List cur = L;
    if (L == NULL || K < 1)
        return (ERROR);
    while (count < K && cur->Next != NULL)
    {
        cur = cur->Next;
        count++;
    }
    if (count == K)
        return (cur->Data);
    else
        return (ERROR);
}
