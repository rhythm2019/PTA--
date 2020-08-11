/*
实现QQ新帐户申请和老帐户登陆的简化版功能。最大挑战是：据说现在的QQ号码已经有10位数了。
DATE:20200716
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define MAXTABLESIZE 110000 /* 允许开辟的最大散列表长度 */
struct Cell
{
    char number[11]; //key
    char password[17];
    int status;
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
        H->Cells[i].password[0] = '\0';
        H->Cells[i].status = 0;
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
    while (H->Cells[NewPos].status && strcmp(H->Cells[NewPos].number, Key))
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

void Insert(struct HashTable *H, char *Key, char *value)
{
    int Pos = Find(H, Key);
    strcpy(H->Cells[Pos].number, Key);
    strcpy(H->Cells[Pos].password, value);
    H->Cells[Pos].status = 1;
    return;
}
void check(struct HashTable *H, char ope, char *number, char *pwd)
{
    switch (ope)
    {
    case 'N':
        if (H->Cells[Find(H, number)].status)
            printf("ERROR: Exist\n");
        else
        {
            Insert(H, number, pwd);
            printf("New: OK\n");
        }
        break;
    case 'L':
        if (H->Cells[Find(H, number)].status == 0)
            printf("ERROR: Not Exist\n");
        else if (strcmp(H->Cells[Find(H, number)].password, pwd))
            printf("ERROR: Wrong PW\n");
        else
            printf("Login: OK\n");
        break;
    }
    return;
}

int main()
{
    int i, N;
    struct HashTable *H;
    char ope, number[11], pwd[17];
    scanf("%d", &N);
    H = CreateTable(N);
    for (i = 0; i < N; i++)
    {
        getchar();
        scanf("%c %s %s", &ope, number, pwd);
        check(H, ope, number, pwd);
    }
    return (0);
}
