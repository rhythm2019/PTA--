/*
随着卫星成像技术的应用，自然资源研究机构可以识别每一棵树的种类。请编写程序帮助研究人员统计每种树的数量，计算每种树占总数的百分比。
DATE:20200716
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAXTABLESIZE 110000 /* 允许开辟的最大散列表长度 */
struct Cell
{
    char name[31]; //key
    int count;     //value
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
        H->Cells[i].name[0] = '\0';
        H->Cells[i].count = 0;
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

int Find(struct HashTable *H, char Key[])
{
    int CurrentPos, NewPos;
    int CNum = 0;
    NewPos = CurrentPos = Hash(Key, H->TableSize); /* 初始散列位置 */
    while (H->Cells[NewPos].count && strcmp(H->Cells[NewPos].name, Key))
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
    strcpy(H->Cells[Pos].name, Key);
    H->Cells[Pos].count++;
    return;
}

int cmpfunc1(const void *a, const void *b)
{
    struct Cell *sch1 = (struct Cell *)a;
    struct Cell *sch2 = (struct Cell *)b;
    return (strcmp(sch1->name, sch2->name));
}

int main()
{
    int i, N;
    struct HashTable *H;
    char tree[31];
    scanf("%d", &N);
    H = CreateTable(N);
    getchar();
    for (i = 0; i < N; i++)
    {
        gets(tree);
        //fgets(tree, 40, stdin);
        Insert(H, tree);
    }
    qsort(H->Cells, H->TableSize, sizeof(struct Cell), cmpfunc1);
    i = 0;
    while (i < H->TableSize)
    {
        if (H->Cells[i].name[0] != '\0')
            printf("%s %.4f%%\n", H->Cells[i].name, H->Cells[i].count * 100. / N);
        i++;
    }
    return (0);
}