/*
设已知有两个堆栈S1和S2，请用这两个堆栈模拟出一个队列Q。
所谓用堆栈模拟队列，实际上就是通过调用堆栈的下列操作函数:
    int IsFull(Stack S)：判断堆栈S是否已满，返回1或0；
    int IsEmpty (Stack S )：判断堆栈S是否为空，返回1或0；
    void Push(Stack S, ElementType item )：将元素item压入堆栈S；
    ElementType Pop(Stack S )：删除并返回S的栈顶元素。
实现队列的操作，即入队void AddQ(ElementType item)和出队ElementType DeleteQ()。
DATE:20200524
*/
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct _stack
{
    ElementType *Data;
    int MAXSIZE;
    int top;

} * STACK;
typedef STACK Stack;
Stack init(int N)
{
    Stack S = (Stack)malloc(sizeof(struct _stack));
    if (N && S)
    {
        S->top = -1;
        S->MAXSIZE = N;
        S->Data = (ElementType *)malloc(N * sizeof(ElementType));
        if (S->Data)
            return (S);
    }
    return (NULL);
}
int IsFull(Stack S)
{
    if (S->top == S->MAXSIZE - 1)
        return (1);
    else
        return (0);
}

int IsEmpty(Stack S)
{
    if (S->top == -1)
        return (1);
    else
        return (0);
}
void Push(Stack S, ElementType item)
{
    if (!IsFull(S))
        S->Data[++(S->top)] = item;
}
ElementType Pop(Stack S)
{
    if (!IsEmpty(S))
        return (S->Data[(S->top)--]);
    else
        return (-1);
}
void AddQ(Stack inS, Stack outS, ElementType item)
{
    if (!IsFull(inS))
        Push(inS, item);
    else if (IsEmpty(outS))
    {
        while (!IsEmpty(inS))
            Push(outS, Pop(inS));
        Push(inS, item);
    }
    else
        printf("ERROR:Full\n");
    return;
}
ElementType DeleteQ(Stack inS, Stack outS)
{
    ElementType tmp;
    if (!IsEmpty(outS))
        return (Pop(outS));
    else if (!IsEmpty(inS))
    {
        while (!IsEmpty(inS))
            Push(outS, Pop(inS));
        tmp = Pop(outS);
        while (!IsEmpty(outS))
            Push(inS, Pop(outS));
        return (tmp);
    }
    else
        printf("ERROR:Empty\n");
    return (-1);
}

int main()
{
    Stack inS, outS;
    int N1, N2, num;
    char ch;
    ElementType tmp;
    scanf("%d %d", &N1, &N2);
    inS = init(N1 <= N2 ? N1 : N2);
    outS = init(N1 <= N2 ? N2 : N1);

    while (scanf("%c", &ch))
    {
        if (ch == 'A')
        {
            scanf("%d", &num);
            AddQ(inS, outS, num);
        }
        else if (ch == 'D')
        {
            scanf("%d", &num);
            tmp = DeleteQ(inS, outS);
            if (tmp != -1)
                printf("%d\n", tmp);
        }
        else if (ch == 'T')
            break;
    }
}