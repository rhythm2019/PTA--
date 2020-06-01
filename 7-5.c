/*
将一系列给定数字插入一个初始为空的小顶堆H[]。随后对任意给定的下标i，打印从H[i]到根结点的路径。
Data[0]为哨兵
每组测试第1行包含2个正整数N和M(≤1000)，分别是插入元素的个数、以及需要打印的路径条数。下一行给出区间[-10000, 10000]内的N个要被插入一个初始为空的小顶堆的整数。最后一行给出M个下标。
关键heap的插入和删除
DATE:20200530
*/
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct HNode *Heap; /* 堆的类型定义 */
struct HNode
{
    ElementType *Data; /* 存储元素的数组 */
    int Size;          /* 堆中当前元素个数 */
    int Capacity;      /* 堆的最大容量 */
};
//typedef Heap MaxHeap; /* 最大堆 */
typedef Heap MinHeap; /* 最小堆 */
MinHeap init_heap(int N)
{
    MinHeap H;
    if (N)
    {
        H = (MinHeap)malloc(sizeof(struct HNode));

        H->Data = (ElementType *)malloc((N + 1) * sizeof(ElementType));
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
    ElementType tmp;
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
int insert_heap(MinHeap H, ElementType ele)
{
    //up
    int i;
    if (H->Size < H->Capacity)
    {
        H->Data[0] = ele;
        i = ++(H->Size);
        while (ele < H->Data[i / 2])
        {
            H->Data[i] = H->Data[i / 2];
            i = i / 2;
        }
        H->Data[i] = ele;
        return (1);
    }
    else
        return (0);
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
    int i, ele, index, *Array, N, M;
    MinHeap H = init_heap(1000);
    scanf("%d %d", &N, &M);
    Array = (int *)malloc(M * sizeof(int));
    for (i = 0; i < N; i++)
    {
        scanf("%d", &ele);
        insert_heap(H, ele);
    }
    for (i = 0; i < M; i++)
        scanf("%d", &Array[i]);
    //build_heap(H);
    for (i = 0; i < M; i++)
    {
        index = Array[i];
        printf("%d", H->Data[index]);
        index /= 2;
        while (index > 0)
        {
            printf(" %d", H->Data[index]);
            index /= 2;
        }
        printf("\n");
    }
    return (0);
}