/*
农夫要修理牧场的一段栅栏，他测量了栅栏，发现需要N块木头，每块木头长度为整数L​i 个长度单位，于是他购买了一条很长的、能锯成N块的木头，即该木头的长度是L
​i​ 的总和。
但是农夫自己没有锯子，请人锯木的酬金跟这段木头的长度成正比。为简单起见，不妨就设酬金等于所锯木头的长度。例如，要将长度为20的木头锯成长度为8、7和5的三段，第一次锯木头花费20，将木头锯成12和8；第二次锯木头花费12，将长度为12的木头锯成7和5，总花费为32。如果第一次将木头锯成15和5，则第二次锯木头花费15，总花费为35（大于32）。
请编写程序帮助农夫计算将木头锯成N块的最少花费。
DATE:20200721
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void Bubble_sort(int *A, int count)
{
    int i, j, tmp;
    for (i = 0; i < count - 1; i++)
        for (j = count - 1; j > i; j--)
            if (A[j] < A[j - 1])
            {
                tmp = A[j - 1];
                A[j - 1] = A[j];
                A[j] = tmp;
            }
    return;
}
int main()
{
    int i, j, tmp, count, cost = 0;
    int A[10000];
    scanf("%d", &count);
    for (i = 0; i < count; i++)
        scanf("%d", A + i);
    Bubble_sort(A, count);
    i = 0;
    while (i + 1 < count)
    {
        A[i + 1] = A[i] + A[i + 1];
        cost += A[i + 1];
        j = i + 1;
        while (j + 1 < count && A[j] > A[j + 1])
        {
            tmp = A[j];
            A[j] = A[j + 1];
            A[j + 1] = tmp;
            j++;
        }
        i++;
    }
    printf("%d", cost);
    return (0);
}