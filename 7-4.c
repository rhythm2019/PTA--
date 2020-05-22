/*
给定一个插入序列就可以唯一确定一棵二叉搜索树。然而，一棵给定的二叉搜索树却可以由多种不同的插入序列得到。例如分别按照序列{2, 1, 3}和{2, 3, 1}插入初始为空的二叉搜索树，都得到一样的结果。
于是对于输入的各种插入序列，你需要判断它们是否能生成一样的二叉搜索树。
*/
#include <stdio.h>
#include <stdlib.h>
#define ERROR NULL
typedef struct TNODE *BSTNode;
struct TNODE
{
    int data;
    BSTNode left;
    BSTNode right;
};
BSTNode insert_Tree(BSTNode Root, int num)
{
    BSTNode tmp;
    if (Root)
    {
        if (num < Root->data)
            Root->left = insert_Tree(Root->left, num);
        else if (num > Root->data)
            Root->right = insert_Tree(Root->right, num);
    }
    else
    {
        Root = (BSTNode)malloc(sizeof(struct TNODE));
        Root->data = num;
        Root->left = NULL;
        Root->right = NULL;
    }
    return (Root);
}
int isomorphism(BSTNode R1, BSTNode R2)
{
    if (R1 == NULL && R2 == NULL)
        return (1);
    if ((R1 && R2 == NULL) || (R1 == NULL && R2))
        return (0);
    if (R1->data == R2->data)
    {
        return (isomorphism(R1->left, R2->left) && isomorphism(R1->right, R2->right));
    }
    else
        return (0);
}
int main()
{
    int i, j, num, N, L;
    BSTNode R1, R2;
    scanf("%d", &N);
    while (N)
    {
        scanf("%d", &L);
        R1 = NULL;
        for (j = 0; j < N; j++)
        {
            scanf("%d", &num);
            R1 = insert_Tree(R1, num);
        }
        for (i = 0; i < L; i++)
        {
            R2 = NULL;
            for (j = 0; j < N; j++)
            {
                scanf("%d", &num);
                R2 = insert_Tree(R2, num);
            }
            if (isomorphism(R1, R2))
                printf("Yes\n");
            else
                printf("No\n");
        }
        scanf("%d", &N);
    }
    return (0);
}