/*
算术表达式有前缀表示法、中缀表示法和后缀表示法等形式。
日常使用的算术表达式是采用中缀表示法，即二元运算符位于两个运算数中间。请设计程序将中缀表达式转换为后缀表达式。
DATE:20200529
*/
/*
写点破程序，真难——正负号的处理
基本思路
参考浙江大学慕课：
把中缀表达式输入到字符串中，从头到尾读取中缀表达式的每个对象，对不同对象不同情况处理：
（1）、运算数：直接输出
（2）、左括号：压入堆栈
（3）、右括号：将栈顶的运算符弹出并输出，直到遇见左括号（左括号出栈，但是不输出）
（4）、运算符：
若优先级大于栈顶运算符，把它压栈；
若优先级小于等于栈顶运算符，将栈顶运算符弹出并输出，再比较新的栈顶运算符，直到该运算符大于栈顶运算符优先级为止，然后将该运算符压栈；
（5）、如果各对象处理完毕，则把堆栈中存留的运算符一并输出
（注意：转换成的后缀表达式，其每个数和运算符之间用空格隔开）

此题中运算数可以是多位数、正负数、小数，这些情况都要考虑到。
版权声明：本文为CSDN博主「_Lichtung_」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/qq_46167487/java/article/details/104005055
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef char ElementType;
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
ElementType Peek(Stack S)
{
    if (!IsEmpty(S))
        return (S->Data[(S->top)]);
}
int Grade(char ope)
{
    switch (ope)
    {
    case '+':
        return (1);
    case '-':
        return (1);
    case '*':
        return (2);
    case '/':
        return (2);
    case '(':
        return (3);
    case ')':
        return (3);
    default:
        return (0);
    }
}
int main()
{
    int i, j, k = 0, stop = -1, signFlag = 1; //下一个sign的标识
    Stack OPE = init(22);
    char s[22], s1[50], ch;
    scanf("%s", s);
    for (i = 0; i < strlen(s) + 1; i++)
    {
        if ((s[i] == '+' && signFlag == 0) || (s[i] == '-' && signFlag == 0) || s[i] == '*' || s[i] == '/' || s[i] == '(' || s[i] == ')' || s[i] == '\0')
        {
            //digit
            if (i > stop + 1)
            {
                s1[k++] = ' ';
                for (j = stop + 1; j < i; j++)
                    s1[k++] = s[j];
            }
            stop = i;
            signFlag = 1; //下一个为正负号

            //ope and end
            if (s[i] == ')')
            {
                signFlag = 0; //import，下一个为plus and minus
                while (!IsEmpty(OPE))
                {
                    ch = Pop(OPE);
                    if (ch != '(')
                    {
                        s1[k++] = ' ';
                        s1[k++] = ch;
                    }
                    else
                        break;
                }
            }
            else if (s[i] == '\0')
                break;
            else
            {
                while (!IsEmpty(OPE) && Grade(Peek(OPE)) >= Grade(s[i]) && Peek(OPE) != '(')
                {
                    s1[k++] = ' ';
                    s1[k++] = Pop(OPE);
                }
                Push(OPE, s[i]);
            }
        }
        else if ((s[i] == '+' && signFlag == 1))
        {
            signFlag = 0;
            stop = i;
        }
        else
            signFlag = 0;
    }
    while (!IsEmpty(OPE))
    {
        s1[k++] = ' ';
        s1[k++] = Pop(OPE);
    }
    s1[k] = '\0';
    k = 0;
    while (s1[k] == ' ' && s1[k] != '\0')
        k++;
    printf("%s\n", s1 + k);
    return (0);
}