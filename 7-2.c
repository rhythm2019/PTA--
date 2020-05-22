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
void print_list(List L);
List init_List()
{
    List L = (List)malloc(sizeof(struct SeqList));
    if (L)
        L->last = -1;
    return (L);
}
List copy_List(List L1)
{
    int i;
    List L;
    if (L1)
    {
        L = init_List();
        if (L)
        {
            L->last = L1->last;
            for (i = 0; i <= L->last; i++)
            {
                L->Data[i][0] = L1->Data[i][0];
                L->Data[i][1] = L1->Data[i][1];
            }
            return (L);
        }
    }
    return (NULL);
}

List plus_List(List L1, List L2)
{
    int i, j;
    List L;
    if (L1 && L2)
    {
        L = init_List();
        if (L)
        {
            i = 0;
            j = 0;
            while (i <= L1->last && j <= L2->last)
            {
                if (L1->Data[i][1] == L2->Data[j][1])
                {
                    if (L1->Data[i][0] + L2->Data[j][0])
                    {
                        (L->last)++;
                        L->Data[L->last][0] = L1->Data[i][0] + L2->Data[j][0];
                        L->Data[L->last][1] = L1->Data[i][1];
                    }
                    i++;
                    j++;
                }
                else if (L1->Data[i][1] > L2->Data[j][1])
                {
                    (L->last)++;
                    L->Data[L->last][0] = L1->Data[i][0];
                    L->Data[L->last][1] = L1->Data[i][1];
                    i++;
                }
                else
                {
                    (L->last)++;
                    L->Data[L->last][0] = L2->Data[j][0];
                    L->Data[L->last][1] = L2->Data[j][1];
                    j++;
                }
            }
            while (i <= L1->last)
            {
                (L->last)++;
                L->Data[L->last][0] = L1->Data[i][0];
                L->Data[L->last][1] = L1->Data[i][1];
                i++;
            }
            while (j <= L2->last)
            {
                (L->last)++;
                L->Data[L->last][0] = L2->Data[j][0];
                L->Data[L->last][1] = L2->Data[j][1];
                j++;
            }
            return (L);
        }
    }
    else if (L1)
        return (copy_List(L1));
    else if (L2)
        return (copy_List(L2));
    return (NULL);
}

List multone_List(List L1, int coef, int expo)
{
    int i;
    List L;
    if (coef && L1)
    {
        L = copy_List(L1);
        for (i = 0; i <= L->last; i++)
        {
            L->Data[i][0] = coef * L->Data[i][0];
            L->Data[i][1] = expo + L->Data[i][1];
        }
        return (L);
    }
    return (NULL);
}

List mult_List(List L1, List L2)
{
    int i, j;
    List L = NULL, tmp1, tmp2;
    if (L1 == NULL || L2 == NULL || L1->last == -1 || L2->last == -1)
        return (NULL);
    for (i = 0; i <= L1->last; i++)
    {
        tmp1 = multone_List(L2, L1->Data[i][0], L1->Data[i][1]);
        tmp2 = L;
        L = plus_List(tmp2, tmp1);
        free(tmp1);
        free(tmp2);
    }
    return (L);
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
    List L1, L2, L3;
    int i, N, a, b;
    L1 = init_List();
    L2 = init_List();
    scanf("%d", &N);
    L1->last = N - 1;
    for (i = 0; i < N; i++)
    {
        scanf("%d %d", &a, &b);
        L1->Data[i][0] = a;
        L1->Data[i][1] = b;
    }
    scanf("%d", &N);
    L2->last = N - 1;
    for (i = 0; i < N; i++)
    {
        scanf("%d %d", &a, &b);
        L2->Data[i][0] = a;
        L2->Data[i][1] = b;
    }
    //operation
    L3 = mult_List(L1, L2);
    print_list(L3);
    free(L3);
    printf("\n");
    L3 = plus_List(L1, L2);
    print_list(L3);
    free(L3);
}