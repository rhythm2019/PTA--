/*
给定一系列整型关键字和素数P，用除留余数法定义的散列函数将关键字映射到长度为P的散列表中。用线性探测法解决冲突。
DATE:20200727
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
// 有些问题，没有考虑删除的情况
struct HashTable
{
    int size;
    int *value;
    int *status; //0-> empty, 1->delete and 2->exist
};
typedef struct HashTable *pHT;

pHT create_HT(int P)
{
    int i, Flag;
    pHT H1 = (pHT)malloc(sizeof(struct HashTable));
    // get prime
    while (1)
    {
        Flag = 0;
        for (i = 2; i < (int)(sqrt(P) + 1); i++)
            if (P % i == 0)
            {
                Flag = 1;
                break;
            }
        if (Flag == 0)
            break;
        else
            P++;
    }
    H1->size = P;
    H1->value = (int *)malloc(P * sizeof(int));
    H1->status = (int *)malloc(P * sizeof(int));
    for (i = 0; i < P; i++)
        H1->status[i] = 0;
    return (H1);
}
int get_pos(pHT H1, int key)
{
    int i = 0, pos;
    pos = key % H1->size;
    while (i < H1->size && ((H1->status[pos] == 2 && H1->value[pos] != key) || H1->status[pos] == 1))
    {
        pos = (++pos) % H1->size;
    }
    if (i == H1->size)
        return (-1);
    else
        return (pos);
}

int main()
{
    int i, N, P, pos;
    int *A;
    pHT H;
    scanf("%d %d", &N, &P);
    A = (int *)malloc(N * sizeof(int));
    for (i = 0; i < N; i++)
        scanf("%d", A + i);
    H = create_HT(P);
    for (i = 0; i < N; i++)
    {
        pos = get_pos(H, A[i]);
        if (H->status[pos] == 0)
        {
            H->status[pos] = 2;
            H->value[pos] = A[i];
        }
        printf("%d", pos);
        if (i != N - 1)
            printf(" ");
    }
}