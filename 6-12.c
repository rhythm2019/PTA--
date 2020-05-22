/*
6-12 二叉搜索树的操作集 (30分)
BinTree Insert( BinTree BST, ElementType X );
BinTree Delete( BinTree BST, ElementType X );
Position Find( BinTree BST, ElementType X );
Position FindMin( BinTree BST );
Position FindMax( BinTree BST );
函数Insert将X插入二叉搜索树BST并返回结果树的根结点指针；
函数Delete将X从二叉搜索树BST中删除，并返回结果树的根结点指针；如果X不在树中，则打印一行Not Found并返回原树的根结点指针；
函数Find在二叉搜索树BST中找到X，返回该结点的指针；如果找不到则返回空指针；
函数FindMin返回二叉搜索树BST中最小元结点的指针；
函数FindMax返回二叉搜索树BST中最大元结点的指针。
*/
#include <stdio.h>
#include <stdlib.h>
typedef int ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};
void PreorderTraversal(BinTree BT); /* 先序遍历，由裁判实现，细节不表 */
void InorderTraversal(BinTree BT);  /* 中序遍历，由裁判实现，细节不表 */

BinTree Insert(BinTree BST, ElementType X);
BinTree Delete(BinTree BST, ElementType X);
Position Find(BinTree BST, ElementType X);
Position FindMin(BinTree BST);
Position FindMax(BinTree BST);

void PreorderTraversal(BinTree BT)
{
    if (BT)
    {
        printf("%d ", BT->Data);
        PreorderTraversal(BT->Left);
        PreorderTraversal(BT->Right);
    }
    return;
}
void InorderTraversal(BinTree BT)
{
    if (BT)
    {
        InorderTraversal(BT->Left);
        printf("%d ", BT->Data);
        InorderTraversal(BT->Right);
    }
    return;
}
int main()
{
    BinTree BST, MinP, MaxP, Tmp;
    ElementType X;
    int N, i;

    BST = NULL;
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        BST = Insert(BST, X);
    }
    printf("Preorder:");
    PreorderTraversal(BST);
    printf("\n");
    MinP = FindMin(BST);
    MaxP = FindMax(BST);
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        Tmp = Find(BST, X);
        if (Tmp == NULL)
            printf("%d is not found\n", X);
        else
        {
            printf("%d is found\n", Tmp->Data);
            if (Tmp == MinP)
                printf("%d is the smallest key\n", Tmp->Data);
            if (Tmp == MaxP)
                printf("%d is the largest key\n", Tmp->Data);
        }
    }
    scanf("%d", &N);
    for (i = 0; i < N; i++)
    {
        scanf("%d", &X);
        BST = Delete(BST, X);
    }
    printf("Inorder:");
    InorderTraversal(BST);
    printf("\n");

    return 0;
}
/*
BinTree Insert(BinTree BST, ElementType X)
{
    BinTree tmp, cur = BST;
    tmp = (BinTree)malloc(sizeof(struct TNode));
    tmp->Data = X;
    tmp->Left = NULL;
    tmp->Right = NULL;
    if (BST)
    {
        while (1)
            if (cur->Data > X)
            {
                if (cur->Left)
                    cur = cur->Left;
                else
                {
                    cur->Left = tmp;
                    return (BST);
                }
            }
            else if (cur->Data < X)
            {
                if (cur->Right)
                    cur = cur->Right;
                else
                {
                    cur->Right = tmp;
                    return (BST);
                }
            }
    }
    else
        return (tmp);
}
BinTree Delete(BinTree BST, ElementType X)
{
    BinTree tmp;
    if (BST)
    {
        if (BST->Data < X)
            BST->Right = Delete(BST->Right, X);
        else if (BST->Data > X)
            BST->Left = Delete(BST->Left, X);
        else
        {
            if (BST->Left == NULL && BST->Right == NULL)
            {
                free(BST);
                return (NULL);
            }
            else if (BST->Left && BST->Right == NULL)
            {
                tmp = BST->Left;
                free(BST);
                return (tmp);
            }
            else if (BST->Right && BST->Left == NULL)
            {
                tmp = BST->Right;
                free(BST);
                return (tmp);
            }
            else
            {
                tmp = FindMin(BST->Right);
                BST->Data = tmp->Data;
                BST->Right = Delete(BST->Right, BST->Data);
                return (BST);
            }
        }
    }
    else
    {
        printf("Not Found\n");
        return (NULL);
    }
}
*/

BinTree Insert(BinTree BST, ElementType X)
{
    if (BST)
    {
        if (BST->Data > X)
            BST->Left = Insert(BST->Left, X);
        else if (BST->Data < X)
            BST->Right = Insert(BST->Right, X);
    }
    else
    {
        BST = (BinTree)malloc(sizeof(struct TNode));
        BST->Data = X;
        BST->Left = NULL;
        BST->Right = NULL;
    }
    return (BST);
}

BinTree Delete(BinTree BST, ElementType X)
{
    BinTree tmp;
    if (BST)
    {
        if (BST->Data < X)
            BST->Right = Delete(BST->Right, X);
        else if (BST->Data > X)
            BST->Left = Delete(BST->Left, X);
        else
        {
            if (BST->Left == NULL && BST->Right == NULL)
            {
                free(BST);
                return (NULL);
            }
            else if (BST->Left && BST->Right == NULL)
            {
                tmp = BST->Left;
                free(BST);
                return (tmp);
            }
            else if (BST->Right && BST->Left == NULL)
            {
                tmp = BST->Right;
                free(BST);
                return (tmp);
            }
            else
            {
                tmp = FindMin(BST->Right);
                BST->Data = tmp->Data;
                BST->Right = Delete(BST->Right, BST->Data);
                return (BST);
            }
        }
        return (BST);
    }
    else
    {
        printf("Not Found\n");
        return (NULL);
    }
}
Position Find(BinTree BST, ElementType X)
{
    while (BST && BST->Data != X)
        if (BST->Data < X)
            BST = BST->Right;
        else
            BST = BST->Left;
    return (BST);
}
Position FindMin(BinTree BST)
{
    if (BST)
    {
        while (BST->Left)
            BST = BST->Left;
    }
    return (BST);
}
Position FindMax(BinTree BST)
{
    if (BST)
    {
        while (BST->Right)
            BST = BST->Right;
    }
    return (BST);
}