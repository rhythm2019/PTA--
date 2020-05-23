/*
设某银行有A、B两个业务窗口，且处理业务的速度不一样，其中A窗口处理速度是B窗口的2倍 —— 
即当A窗口每处理完2个顾客时，B窗口处理完1个顾客。给定到达银行的顾客序列，请按业务完成的顺序输出顾客序列。
假定不考虑顾客先后到达的时间间隔，并且当不同窗口同时处理完2个顾客时，A窗口顾客优先输出。
*/
#include <stdio.h>
#include <stdlib.h>
enum
{
    false,
    true
};
typedef int Position;
typedef int ElementType;
struct QNode
{
    ElementType *Data;    /* 存储元素的数组 */
    Position Front, Rear; /* 队列的头、尾指针 */
    int MaxSize;          /* 队列最大容量 */
};
typedef struct QNode *Queue;
Queue CreateQueue(int MaxSize)
{
    Queue Q = (Queue)malloc(sizeof(struct QNode));
    Q->Data = (ElementType *)malloc(MaxSize * sizeof(ElementType));
    Q->Front = Q->Rear = 0;
    Q->MaxSize = MaxSize;
    return Q;
}
int IsFull(Queue Q)
{
    return ((Q->Rear + 1) % Q->MaxSize == Q->Front);
}

int AddQ(Queue Q, ElementType X)
{
    if (IsFull(Q))
    {
        //printf("队列满");
        return false;
    }
    else
    {
        Q->Rear = (Q->Rear + 1) % Q->MaxSize;
        Q->Data[Q->Rear] = X;
        return true;
    }
}

int IsEmpty(Queue Q)
{
    return (Q->Front == Q->Rear);
}

ElementType DeleteQ(Queue Q)
{
    if (IsEmpty(Q))
    {
        // printf("队列空");
        //return ERROR;
        return (-1);
    }
    else
    {
        Q->Front = (Q->Front + 1) % Q->MaxSize;
        return Q->Data[Q->Front];
        //return (true);
    }
}

int main()
{
    int N, tmp, i = 0;
    int t1 = 0, t2 = 0;
    Queue q1, q2;
    q1 = CreateQueue(1001);
    q2 = CreateQueue(1001);
    scanf("%d", &N);
    while (i++ < N)
    {
        scanf("%d", &tmp);
        if (tmp % 2)
            AddQ(q1, tmp);
        else
            AddQ(q2, tmp);
    }
    t1 += 1;
    t2 += 2;
    if (!IsEmpty(q1))
    {
        printf("%d", DeleteQ(q1));
        t1 += 1;
    }
    else if (!IsEmpty(q2))
    {
        printf("%d", DeleteQ(q2));
        t2 += 2;
    }

    while (!(IsEmpty(q1) || IsEmpty(q2)))
    {
        if (t1 <= t2)
        {
            printf(" %d", DeleteQ(q1));
            t1 += 1;
        }
        else
        {
            printf(" %d", DeleteQ(q2));
            t2 += 2;
        }
    }
    while (!IsEmpty(q1))
        printf(" %d", DeleteQ(q1));
    while (!IsEmpty(q2))
        printf(" %d", DeleteQ(q2));
    return (0);
}