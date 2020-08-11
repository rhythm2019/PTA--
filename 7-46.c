/*
新浪微博可以在发言中嵌入“话题”，即将发言中的话题文字写在一对“#”之间，就可以生成话题链接，点击链接可以看到有多少人在跟自己讨论相同或者相似的话题。
新浪微博还会随时更新热门话题列表，并将最热门的话题放在醒目的位置推荐大家关注。
本题目要求实现一个简化的热门话题推荐功能，从大量英文（因为中文分词处理比较麻烦）微博中解析出话题，找出被最多条微博提到的话题。
DATE:20200810
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#define StringMax 139
#define END 0
#define BEGIN 1
struct HashTable
{
    int size;
    char (*keychar)[StringMax]; //key
    int *count;
    int *lastCase;
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
    H1->keychar = (char(*)[StringMax])malloc(P * sizeof(char[StringMax]));
    H1->count = (int *)malloc(P * sizeof(int));
    H1->lastCase = (int *)malloc(P * sizeof(int));
    for (i = 0; i < P; i++)
        strcpy(H1->keychar[i], "\0");
    memset(H1->count, 0, P * sizeof(int));
    memset(H1->lastCase, 0, P * sizeof(int));
    return (H1);
}
int get_pos(pHT H1, char key[])
{
    long int i, pos = 0;
    for (i = 0; i < strlen(key); i++)
        pos = ((pos << 1) + key[i]) % H1->size;
    i = 0;
    while (i <= H1->size && H1->count[pos] && strcmp(H1->keychar[pos], key))
    {
        pos = (++pos) % H1->size;
        i++;
    }
    if (i > H1->size)
        return (-1);
    else
        return ((int)pos);
}
//输入字符串处理，去头尾空格，去多余空格
void FormatInput(char *s1)
{
    char s2[StringMax];
    int i = 0, j = strlen(s1) - 1, k = 0;
    while (s1[i] == ' ')
        i++;
    while (s1[j] == ' ')
        j--;
    for (; i <= j; i++)
    {
        if (s1[i] != ' ')
            s2[k++] = s1[i];
        else if (s1[i - 1] != ' ')
            s2[k++] = s1[i];
    }
    s2[k] = '\0';
    strcpy(s1, s2);
    s1[0] = toupper(s1[0]);
    return;
}
int main()
{
    int i, j, k, N, pos, Flag, MAXCOUNT = 0, RANK = 0;
    char s1[141], s2[141], MAXSTRING[141];
    pHT H1 = create_HT(100000);
    scanf("%d", &N);
    gets(s1);
    for (k = 1; k < N + 1; k++)
    {
        gets(s1);
        Flag = END;
        for (i = 0; i < strlen(s1); i++)
        {
            if ((isalnum(s1[i]) || s1[i] == ' ') && Flag == BEGIN)
                s2[j++] = tolower(s1[i]);
            else if (s1[i] != '#' && Flag == BEGIN)
                s2[j++] = ' ';
            else if (s1[i] == '#' && Flag == END)
            {
                Flag = BEGIN;
                j = 0;
            }
            else if (s1[i] == '#' && Flag == BEGIN)
            {
                Flag = END;
                s2[j] = '\0';
                FormatInput(s2);
                pos = get_pos(H1, s2);
                if (H1->lastCase[pos] != k)
                {
                    H1->lastCase[pos] = k;
                    H1->count[pos]++;
                    strcpy(H1->keychar[pos], s2);
                    if (H1->count[pos] > MAXCOUNT)
                    {
                        MAXCOUNT = H1->count[pos];
                        strcpy(MAXSTRING, s2);
                        RANK = 1;
                    }
                    else if (H1->count[pos] == MAXCOUNT)
                    {
                        MAXCOUNT = H1->count[pos];
                        RANK++;
                        if (strcmp(s2, MAXSTRING) < 0)
                            strcpy(MAXSTRING, s2);
                    }
                }
            }
        }
    }
    printf("%s\n", MAXSTRING);
    printf("%d\n", MAXCOUNT);
    if (RANK > 1)
        printf("And %d more ...\n", RANK - 1);
    return (0);
}