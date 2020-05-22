/*
借助堆栈以非递归（循环）方式求解汉诺塔的问题（n, a, b, c），
即将N个盘子从起始柱（标记为“a”）通过借助柱（标记为“b”）移动到目标柱（标记为“c”），并保证每个移动符合汉诺塔问题的要求。
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100000
struct Status
{
    int n;
    char disk[3];
};
struct STACK
{
    struct Status Array[MAXSIZE];
    int top;
};

void init_stack(struct STACK *S1)
{
    S1->top = -1;
    return;
}
int push_stack(struct STACK *S1, struct Status *newStatus)
{
    int i;
    if (S1->top == MAXSIZE - 1)
        return (0);
    else
    {
        ++(S1->top);
        S1->Array[S1->top] = *newStatus;
        return (1);
    }
}
int pop_stack(struct STACK *S1, struct Status *newStatus)
{
    int i;
    if (S1->top == -1)
        return (0);
    else
    {
        *newStatus = S1->Array[S1->top];
        (S1->top)--;
        return (1);
    }
}

int main()
{
    struct Status cur, tmp;
    struct STACK S1;
    init_stack(&S1);
    scanf("%d", &(cur.n));
    cur.disk[0] = 'a';
    cur.disk[1] = 'b';
    cur.disk[2] = 'c';
    push_stack(&S1, &cur);
    while (S1.top > -1)
    {
        pop_stack(&S1, &cur);
        if (cur.n > 3)
        {
            //
            tmp.n = cur.n - 1;
            tmp.disk[0] = cur.disk[1];
            tmp.disk[1] = cur.disk[0];
            tmp.disk[2] = cur.disk[2];
            push_stack(&S1, &tmp);
            //
            tmp.n = 1;
            tmp.disk[0] = cur.disk[0];
            tmp.disk[1] = cur.disk[1];
            tmp.disk[2] = cur.disk[2];
            push_stack(&S1, &tmp);
            //
            tmp.n = cur.n - 1;
            tmp.disk[0] = cur.disk[0];
            tmp.disk[1] = cur.disk[2];
            tmp.disk[2] = cur.disk[1];
            push_stack(&S1, &tmp);
            continue;
        }
        else if (cur.n == 3)
        {
            printf("%c -> %c\n", cur.disk[0], cur.disk[2]);
            printf("%c -> %c\n", cur.disk[0], cur.disk[1]);
            printf("%c -> %c\n", cur.disk[2], cur.disk[1]);
            printf("%c -> %c\n", cur.disk[0], cur.disk[2]);
            printf("%c -> %c\n", cur.disk[1], cur.disk[0]);
            printf("%c -> %c\n", cur.disk[1], cur.disk[2]);
            printf("%c -> %c\n", cur.disk[0], cur.disk[2]);
            continue;
        }
        else if (cur.n == 2)
        {
            printf("%c -> %c\n", cur.disk[0], cur.disk[1]);
            printf("%c -> %c\n", cur.disk[0], cur.disk[2]);
            printf("%c -> %c\n", cur.disk[1], cur.disk[2]);
            continue;
        }
        else if (cur.n == 1)
        {
            printf("%c -> %c\n", cur.disk[0], cur.disk[2]);
            continue;
        }
        else
        {
            break;
        }
    }
    return (0);
}