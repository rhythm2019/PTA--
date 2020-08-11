/*
笛卡尔树是一种特殊的二叉树，其结点包含两个关键字K1和K2。首先笛卡尔树是关于K1的二叉搜索树，即结点左子树的所有K1值都比该结点的K1值小，右子树则大。其次所有结点的K2关键字满足优先队列（不妨设为最小堆）的顺序要求，即该结点的K2值比其子树中所有结点的K2值小。
给定一棵二叉树，请判断该树是否笛卡尔树。
DATE:20200723
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node *pnode;
struct node
{
    int K1, K2;
    int left, right;
};

void inorder(pnode A, int B[], int root)
{
    static int index = 0;
    if (root != -1)
    {
        inorder(A, B, A[root].left);
        B[index++] = A[root].K1;
        inorder(A, B, A[root].right);
    }
    return;
}

void preorder(pnode A, int root, int *Flag)
{
    int left, right;
    if (*Flag == 0 || root == -1)
        return;
    left = A[root].left;
    right = A[root].right;
    if (left != -1)
    {
        if (A[root].K1 <= A[left].K1 || A[root].K2 >= A[left].K2)
        {
            *Flag = 0;
            return;
        }
        else
            preorder(A, left, Flag);
    }
    if (right != -1)
    {
        if (A[root].K1 > A[right].K1 || A[root].K2 >= A[right].K2)
        {
            *Flag = 0;
            return;
        }
        else
            preorder(A, right, Flag);
    }
    return;
}

int main()
{
    int i, j = 0, root, count, Flag = 1, tmp[1000] = {0};
    struct node A[1000];
    scanf("%d", &count);
    for (i = 0; i < count; i++)
    {
        scanf("%d %d %d %d", &(A[i].K1), &(A[i].K2), &(A[i].left), &(A[i].right));
        if (A[i].left != -1)
            tmp[A[i].left] = 1;
        if (A[i].right != -1)
            tmp[A[i].right] = 1;
    }
    i = 0;
    while (tmp[i])
        i++;
    preorder(A, i, &Flag);
    if (Flag)
    {
        inorder(A, tmp, i);
        for (i = 0; i < count - 1; i++)
            if (tmp[i] > tmp[i + 1])
            {
                Flag = 0;
                break;
            }
    }
    if (Flag)
        printf("YES\n");
    else
        printf("NO\n");
    return (0);
}