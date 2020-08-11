/*
给定大量手机用户通话记录，找出其中通话次数最多的聊天狂人。
DATE:20200715
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAXTABLESIZE 210000 /* 允许开辟的最大散列表长度 */
struct Cell
{
    char key[12]; /* 存放元素 */
    int value;    /* 单元状态 */
    //int status;
};
struct HashTable
{
    int TableSize;      /* 表的最大长度 */
    struct Cell *Cells; /* 存放散列单元数据的数组 */
};
int NextPrime(int N)
{
    int i, p = (N % 2) ? N + 2 : N + 1;
    while (p <= MAXTABLESIZE)
    {
        for (i = (int)sqrt(p); i > 2; i--)
            if (!(p % i))
                break;
        if (i == 2)
            break;
        else
            p += 2;
    }
    return p;
}

struct HashTable *CreateTable(int TableSize)
{
    int i;
    struct HashTable *H = (struct HashTable *)malloc(sizeof(struct HashTable));
    H->TableSize = NextPrime(TableSize);
    H->Cells = (struct Cell *)malloc(H->TableSize * sizeof(struct Cell));
    for (i = 0; i < H->TableSize; i++)
    {
        H->Cells[i].key[0] = '\0';
        H->Cells[i].value = 0;
    }
    return H;
}

int Hash(const char Key[], int TableSize)
{
    unsigned int h = 0;
    while (*Key != '\0')
        h = (h << 5) + *Key++; //
    return h % TableSize;
}

int Find(struct HashTable *H, char *Key)
{
    int CurrentPos, NewPos;
    int CNum = 0;
    NewPos = CurrentPos = Hash(Key, H->TableSize); /* 初始散列位置 */
    while (H->Cells[NewPos].value && strcmp(H->Cells[NewPos].key, Key))
    {
        /* 统计1次冲突，并判断奇偶次 */
        if (++CNum % 2)
        {                                                      /* 奇数次冲突 */
            NewPos = CurrentPos + (CNum + 1) * (CNum + 1) / 4; /* 增量为+[(CNum+1)/2]^2 */
            if (NewPos >= H->TableSize)
                NewPos = NewPos % H->TableSize; /* 调整为合法地址 */
        }
        else
        {                                          /* 偶数次冲突 */
            NewPos = CurrentPos - CNum * CNum / 4; /* 增量为-(CNum/2)^2 */
            while (NewPos < 0)
                NewPos += H->TableSize; /* 调整为合法地址 */
        }
    }
    return NewPos; /* 此时NewPos或者是Key的位置，或者是一个空单元的位置（表示找不到）*/
}

void Insert(struct HashTable *H, char *Key)
{
    int Pos = Find(H, Key);
    H->Cells[Pos].value++;
    strcpy(H->Cells[Pos].key, Key);
    return;
}
int cmpfunc1(const void *a, const void *b)
{
    struct Cell *sch1 = (struct Cell *)a;
    struct Cell *sch2 = (struct Cell *)b;
    if (sch1->value != sch2->value)
        return (sch2->value - sch1->value);
    else
        return (strcmp(sch1->key, sch2->key));
}

int main()
{
    int i, N;
    struct HashTable *H;
    char phone1[12], phone2[12];
    scanf("%d", &N);
    H = CreateTable(2 * N);
    for (i = 0; i < N; i++)
    {
        scanf("%s %s", phone1, phone2);
        Insert(H, phone1);
        Insert(H, phone2);
    }

    qsort(H->Cells, H->TableSize, sizeof(struct Cell), cmpfunc1);
    i = 1;
    while (H->Cells[i].value == H->Cells[0].value)
        i++;
    if (i == 1)
        printf("%s %d", H->Cells[0].key, H->Cells[0].value);
    else
        printf("%s %d %d", H->Cells[0].key, H->Cells[0].value, i);
    return (0);
}