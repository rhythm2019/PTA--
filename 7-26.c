/*
消息队列是Windows系统的基础。对于每个进程，系统维护一个消息队列。
如果在进程中有特定事件发生，如点击鼠标、文字改变等，系统将把这个消息加到队列当中。
同时，如果队列不是空的，这一进程循环地从队列中按照优先级获取消息。
请注意优先级值低意味着优先级高。请编辑程序模拟消息队列，将消息加到队列中以及从队列中获取消息。
DATE:20200718
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 10000
// MESSAGE and min_heap
struct MESSAGE
{
    char msgname[12];
    int priority;
};
typedef struct MESSAGE ElementType;
typedef struct HNode *Heap; /* 堆的类型定义 */
typedef Heap MinHeap;       /* 最小堆 */
struct HNode
{
    ElementType *Data; /* 存储元素的数组 */
    int Size;          /* 堆中当前元素个数 */
    int Capacity;      /* 堆的最大容量 */
};
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
    if (2 * index + 1 <= H->Size && H->Data[2 * index + 1].priority < H->Data[2 * index].priority && H->Data[2 * index + 1].priority < H->Data[index].priority)
    {
        tmp = H->Data[2 * index + 1];
        H->Data[2 * index + 1] = H->Data[index];
        H->Data[index] = tmp;
        PercDown(H, 2 * index + 1);
    }
    else if (2 * index <= H->Size && H->Data[2 * index].priority < H->Data[index].priority)
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
int insert_heap(MinHeap H, ElementType msg)
{
    int i;
    ElementType tmp;
    if (IsFull(H))
        return (0);
    H->Size++;
    i = H->Size;
    H->Data[i] = msg;
    while (i > 1 && H->Data[i].priority < H->Data[i / 2].priority)
    {

        tmp = H->Data[i / 2];
        H->Data[i / 2] = H->Data[i];
        H->Data[i] = tmp;
        i = i / 2;
    }
    return (1);
}
int main()
{
    int i, N;
    char s1[10];
    MinHeap H;
    ElementType tmp;
    scanf("%d", &N);
    H = init_heap(N);
    for (i = 0; i < N; i++)
    {
        scanf("%s", s1);
        if (strcmp(s1, "PUT") == 0)
        {
            scanf("%s %d", &tmp.msgname, &tmp.priority);
            insert_heap(H, tmp);
        }
        else if (strcmp(s1, "GET") == 0)
        {
            if (!IsEmpty(H))
            {
                printf("%s\n", H->Data[1].msgname);
                delete_min(H);
            }
            else
            {
                printf("EMPTY QUEUE!\n");
            }
        }
    }
    return (0);
}