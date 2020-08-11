/*
给定N个（长整型范围内的）整数，要求输出从小到大排序后的结果。
DATE:20200711
*/
#include <stdio.h>
#include <stdlib.h>
// bubble sort
void bubble_sort(int a[], int count)
{
    int i, j, tmp;
    for (j = count - 1; j > 0; j--)
        for (i = 0; i < j; i++)
            if (a[i] > a[i + 1])
            {
                tmp = a[i];
                a[i] = a[i + 1];
                a[i + 1] = tmp;
            }
    return;
}
//heap sort
typedef struct HNode *Heap; /* 堆的类型定义 */
typedef Heap MinHeap;       /* 最小堆 */
struct HNode
{
    int *Data;    /* 存储元素的数组 */
    int Size;     /* 堆中当前元素个数 */
    int Capacity; /* 堆的最大容量 */
};
MinHeap init_heap(int N)
{
    MinHeap H;
    if (N)
    {
        H = (MinHeap)malloc(sizeof(struct HNode));
        H->Data = (int *)malloc((N + 1) * sizeof(int));
        H->Size = 0;
        H->Capacity = N;
        return (H);
    }
    else
        return (NULL);
}
int IsFull(MinHeap H)
{
    return (H->Size == H->Capacity);
}
int IsEmpty(MinHeap H)
{
    return (H->Size == 0);
}
void PercDown(MinHeap H, int index)
{
    int tmp;
    if (2 * index + 1 <= H->Size && H->Data[2 * index + 1] < H->Data[2 * index] && H->Data[2 * index + 1] < H->Data[index])
    {
        tmp = H->Data[2 * index + 1];
        H->Data[2 * index + 1] = H->Data[index];
        H->Data[index] = tmp;
        PercDown(H, 2 * index + 1);
    }
    else if (2 * index <= H->Size && H->Data[2 * index] < H->Data[index])
    {
        tmp = H->Data[2 * index];
        H->Data[2 * index] = H->Data[index];
        H->Data[index] = tmp;
        PercDown(H, 2 * index);
    }
    else
        return;
}
int delete_min(MinHeap H)
{
    if (H->Size)
    {
        H->Data[0] = H->Data[H->Size--];
        PercDown(H, 0);
        return (1);
    }
    else
        return (0);
}
int build_heap(MinHeap H)
{
    int i;
    for (i = H->Size / 2; i > 0; i--)
        PercDown(H, i);
    return (1);
}

int main()
{
    //int i, count, A[100000] = {0};
    int i;
    Heap h = init_heap(100000);
    scanf("%d", &h->Size);
    for (i = 0; i < h->Size; i++)
        scanf("%d", &h->Data[i+1]);
    //bubble_sort(A, count);
    build_heap(h);
    printf("%d", h->Data[1]);
    while (h->Size > 1)
    {
        delete_min(h);
        printf(" %d", h->Data[1]);
    }
    return (0);
}