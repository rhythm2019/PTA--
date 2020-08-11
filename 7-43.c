/*
给定一系列由大写英文字母组成的字符串关键字和素数P，用移位法定义的散列函数H(Key)将关键字Key中的最后3个字符映射为整数，每个字符占5位；再用除留余数法将整数映射到长度为P的散列表中。例如将字符串AZDEG插入长度为1009的散列表中，我们首先将26个大写英文字母顺序映射到整数0~25；
再通过移位将其映射为3×32**​2​ + 4×32 + 6=3206；然后根据表长得到，即是该字符串的散列映射位置。
发生冲突时请用平方探测法解决。
DATE:20200729
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct HashTable
{
    int size;
    char (*value)[9]; //key
    int *status;      //0-> empty, 1->delete and 2->exist
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
        if (Flag)
            P++;
        else
            break;
    }
    H1->size = P;
    H1->value = (char(*)[9])malloc(P * sizeof(char[9]));
    H1->status = (int *)malloc(P * sizeof(int));
    for (i = 0; i < P; i++)
    {
        strcpy(H1->value[i], "");
        H1->status[i] = 0;
    }
    return (H1);
}
int get_pos(pHT H1, char key[])
{
    int i, pos = 0, newpos;
    for (i = strlen(key) - 1; i >= 0 && i >= strlen(key) - 3; i--)
        pos = pos + (key[i] - 'A') * (int)pow(32, (strlen(key) - 1 - i));
    pos = pos % H1->size;
    newpos = pos;
    //delete 比较特殊
    i = 0;
    while (i <= H1->size && ((H1->status[newpos] == 2 && strcmp(H1->value[newpos], key)) || (H1->status[newpos] == 1 && strcmp(H1->value[newpos], key))))
    {
        if (i % 2)
            newpos = (pos + (i + 1) * (i + 1) / 4) % H1->size;
        else
        {
            newpos = (pos - i * i / 4) % H1->size;
            if (newpos < 0)
                newpos += H1->size;
        }
        i++;
    }
    if (i >= H1->size)
        return (-1);
    else
        return (newpos);
    return (0);
}

int main()
{
    int i, N, P, pos, *A;
    char key[9];
    pHT H;
    scanf("%d %d", &N, &P);
    A = (int *)malloc(N * sizeof(int));
    H = create_HT(P);
    for (i = 0; i < N; i++)
    {
        scanf("%s", key);
        pos = get_pos(H, key);
        H->status[pos] = 2;
        strcpy(H->value[pos], key);
        A[i] = pos;
    }
    for (i = 0; i < N; i++)
    {
        printf("%d", A[i]);
        if (i != N - 1)
            printf(" ");
    }
    return (0);
}