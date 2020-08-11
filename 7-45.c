/*
不少航空公司都会提供优惠的会员服务，当某顾客飞行里程累积达到一定数量后，可以使用里程积分直接兑换奖励机票或奖励升舱等服务。
现给定某航空公司全体会员的飞行记录，要求实现根据身份证号码快速查询会员里程积分的功能。
DATE:20200730
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
struct HashTable
{
    int size;
    char (*ID)[19]; //key
    int *status;    //0-> empty, 1->delete and 2->exist
    int *mileage;
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
    H1->ID = (char(*)[19])malloc(P * sizeof(char[19]));
    H1->mileage = (int *)malloc(P * sizeof(int));
    H1->status = (int *)malloc(P * sizeof(int));
    for (i = 0; i < P; i++)
    {
        strcpy(H1->ID[i], "");
        H1->ID[i][0] = '\0';
        H1->status[i] = 0;
        H1->mileage[i] = 0;
    }
    return (H1);
}
int get_pos(pHT H1, char key[])
{
    int i, pos, newpos;
    pos = (key[5] - '0') * 10000 + (key[9] - '0') * 1000 + (key[13] - '0') * 100 + (key[15] - '0') * 10 + (key[16] - '0');
    if (key[17] == 'x')
        pos = (pos * 10 + 10) % H1->size;
    else
        pos = (pos * 10 + key[17] - '0') % H1->size;
    newpos = pos;
    //delete 比较特殊
    i = 0;
    while (i <= H1->size && (H1->status[newpos] == 2 && strcmp(H1->ID[newpos], key)))
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
    int i, N, cutoff, mileage, pos;
    char key[19];
    pHT H = create_HT(110000);
    scanf("%d %d", &N, &cutoff);
    //input
    for (i = 0; i < N; i++)
    {
        scanf("%s %d", key, &mileage);
        if (mileage < cutoff)
            mileage = cutoff;
        pos = get_pos(H, key);
        if (H->status[pos] == 0)
        {
            H->status[pos] = 2;
            strcpy(H->ID[pos], key);
            H->mileage[pos] = mileage;
        }
        else if (H->status[pos] == 2)
        {
            H->mileage[pos] += mileage;
        }
    }
    //print
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%s", key);
        pos = get_pos(H, key);
        if (H->status[pos] == 0)
            printf("No Info\n");
        else if (H->status[pos] == 2)
            printf("%d\n", H->mileage[pos]);
    }
    return (0);
}