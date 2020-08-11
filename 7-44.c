/*
实现一种简单原始的文件相似度计算，即以两文件的公共词汇占总词汇的比例来定义相似度。
为简化问题，这里不考虑中文（因为分词太难了），只考虑长度不小于3、且不超过10的英文单词，长度超过10的只考虑前10个字母。
DATE:20200806
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>
struct HashTable
{
    int size;
    char (*keychar)[11]; //key
    int *status;         //0-> empty, 1->单个文件 and 2->exist，多个文件
    int (*value)[101];
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
    H1->keychar = (char(*)[11])malloc(P * sizeof(char[11]));
    H1->status = (int *)malloc(P * sizeof(int));
    H1->value = (int(*)[101])malloc(P * sizeof(int[101]));
    for (i = 0; i < P; i++)
    {
        strcpy(H1->keychar[i], "\0");
        H1->status[i] = 0;
        memset(H1->value[i], 0, 101 * sizeof(int));
    }
    return (H1);
}
int get_pos(pHT H1, char key[])
{
    long int i, pos = 0;
    for (i = 0; i < strlen(key); i++)
        pos = (pos << 5) + (key[i]);
    pos = pos % H1->size;
    i = 0;
    while (i <= H1->size && (H1->status[pos] && strcmp(H1->keychar[pos], key)))
    {
        pos = (++pos) % H1->size;
        i++;
    }
    if (i > H1->size)
        return (-1);
    else
        return ((int)pos);
}
int main()
{
    int i, j, k, f1, f2, N, pos;
    int *P, PAB[101][101];
    char c, input[30];
    pHT H1;
    scanf("%d", &N);
    H1 = create_HT(10);
    P = (int *)malloc((N + 1) * sizeof(int));
    memset(PAB, 0, (101 * 101 * sizeof(int)));
    //input
    for (i = 1; i < N + 1; i++)
    {
        j = 0;
        P[i] = 0;
        while (c = getchar())
        {
            if (((c <= 'z' && c >= 'a') || (c <= 'Z' && c >= 'A')) && (j < 10))
                input[j++] = toupper(c);
            else if (j < 3)
                j = 0;
            else
            {
                input[j] = '\0';
                j = 0;
                //hash
                pos = get_pos(H1, input);
                if (H1->status[pos] == 0 || H1->value[pos][i] == 0)
                {
                    H1->value[pos][i] = 1;
                    H1->status[pos]++;
                    strcpy(H1->keychar[pos], input);
                    P[i]++;
                }
            }
            if (c == '#')
                break;
        }
    }
    //solve
    for (f1 = 1; f1 < N + 1; f1++)
        for (f2 = f1; f2 < N + 1; f2++)
            for (i = 0; i < H1->size; i++)
                PAB[f1][f2] += H1->value[i][f1] * H1->value[i][f2];
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d %d", &f1, &f2);
        if (f2 < f1)
            printf("%.1f%%\n", 100.0 * PAB[f2][f1] / (P[f1] + P[f2] - PAB[f2][f1]));
        else
            printf("%.1f%%\n", 100.0 * PAB[f1][f2] / (P[f1] + P[f2] - PAB[f1][f2]));
    }
    return (0);
}