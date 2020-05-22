/*
已知两个非降序链表序列S1与S2，设计函数构造出S1与S2的交集新链表S3。
*/
#include <stdio.h>
#include <stdlib.h>
#define ERROR NULL
struct SeqList
{
    int Data[1000][2];
    int last;
};
typedef struct SeqList *List;
List init_List()
{
    List L = (List)malloc(sizeof(struct SeqList));
    L->last = -1;
    return (L);
}
void derivation(List L1, List L2)
{
    int i;
    int coef, expo;
    if (L1 == NULL || L1->last == -1 || L2 == NULL)
    {
        return;
    }
    for (i = 0; i <= L1->last; i++)
    {
        coef = L1->Data[i][0] * L1->Data[i][1];
        expo = L1->Data[i][1] - 1;
        if (coef)
        {
            ++(L2->last);
            L2->Data[L2->last][0] = coef;
            L2->Data[L2->last][1] = expo;
        }
    }
    return;
}
void print_list(List L)
{
    int i = 0;
    if (L == NULL || L->last == -1)
    {
         printf("0 0");
        return;
    }
    while (i < L->last)
    {
        printf("%d %d ", L->Data[i][0], L->Data[i][1]);
        i++;
    }
    printf("%d %d", L->Data[L->last][0], L->Data[L->last][1]);
    return;
}
int main()
{
    List L1, L2;
    int i, a, b;
    L1 = init_List();
    L2 = init_List();
    //input_List(L1);
    while (scanf("%d %d", &a, &b))
    {
        L1->last++;
        L1->Data[L1->last][0] = a;
        L1->Data[L1->last][1] = b;
        if (getchar() == '\n')
            break;
    }
    //derivation
    derivation(L1, L2);
    print_list(L2);
    return (0);
}