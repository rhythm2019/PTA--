/*
算术表达式有前缀表示法、中缀表示法和后缀表示法等形式。
前缀表达式指二元运算符位于两个运算数之前，例如2+3*(7-4)+8/4的前缀表达式是：+ + 2 * 3 - 7 4 / 8 4。
请设计程序计算前缀表达式的结果值。
DATE:20200524
*/
// 困难的地方竟然是浮点数的识别，格式识别
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef double ElementType;
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
}
int Calcu(Stack NUM, char ope, double *result)
{
    ElementType x1, x2;
    if (!IsEmpty(NUM))
        x1 = Pop(NUM);
    if (!IsEmpty(NUM))
        x2 = Pop(NUM);
    else
        return (0);
    switch (ope)
    {
    case '+':
        *result = x1 + x2;
        return (1);
    case '-':
        *result = x1 - x2;
        return (1);
    case '*':
        *result = x1 * x2;
        return (1);
    case '/':
        if (x2 != 0.0)
        {
            *result = x1 / x2;
            return (1);
        }
        else
            return (0);
    }
}
int main()
{
    Stack NUMBER;
    int i, num, N;
    char s[61], cmp[61];
    double result;
    NUMBER = init(31);
    gets(s);
    for (i = strlen(s) - 1; i >= 0; i--)
    {
        if (s[i] == ' ' && strlen(s + i + 1))
        {

            if (strlen(s + i + 1) == 1 && (s[i + 1] == '+' || s[i + 1] == '-' || s[i + 1] == '*' || s[i + 1] == '/'))
                if (Calcu(NUMBER, s[i + 1], &result))
                {
                    Push(NUMBER, result);
                    s[i] = '\0';
                    continue;
                }
                else
                {
                    printf("ERROR");
                    return (0);
                }
            num = atof(s + i);
            if (IsFull(NUMBER))
            {
                printf("ERROR");
                return (0);
            }
            else
                Push(NUMBER, num);
            s[i] = '\0';
            continue;
        }
    }
    if (IsEmpty(NUMBER) && strlen(s))
        printf("%.1lf", atof(s));
    else if (NUMBER->top == 1 && strlen(s))
    {
        if (Calcu(NUMBER, s[i + 1], &result))
            printf("%.1lf", result);
        else
            printf("ERROR");
    }
    else if (NUMBER->top == 0)
        printf("%.1lf", result);
    else
        printf("ERROR");
    return (0);
}