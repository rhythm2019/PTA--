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
BinTree Insert(BinTree BST, ElementType x)
{
    if (!BST)
    {
        BinTree p = (BinTree)malloc(sizeof(BinTree));
        p->Data = x;
        p->Left = p->Right = NULL;
        BST = p;
    }
    else if (x < BST->Data)
        BST->Left = Insert(BST->Left, x);
    else if (x > BST->Data)
        BST->Right = Insert(BST->Right, x);
    return BST;
}
BinTree Delete(BinTree BST, ElementType x)
{
    if (!BST)
    {
        printf("Not Found\n");
    }
    else
    {
        if (x < BST->Data)
            BST->Left = Delete(BST->Left, x);
        else if (x > BST->Data)
            BST->Right = Delete(BST->Right, x);
        else if (x == BST->Data)
        {
            if (BST->Left && BST->Right)
            {
                BinTree t = FindMin(BST->Right);
                BST->Data = t->Data;
                BST->Right = Delete(BST->Right, BST->Data);
            }
            else
            {
                if (!BST->Left)
                    BST = BST->Right;
                else if (!BST->Right)
                    BST = BST->Left;
            }
        }
    }
    return BST;
}
Position Find(BinTree BST, ElementType x)
{
    if (!BST)
        return NULL;
    if (BST->Data == x)
        return BST;
    else if (x < BST->Data)
        return Find(BST->Left, x);
    else if (x > BST->Data)
        return Find(BST->Right, x);
    return BST;
}
Position FindMin(BinTree BST)
{
    if (BST)
    {
        if (BST->Left)
            return FindMin(BST->Left);
        else
            return BST;
    }
}
Position FindMax(BinTree BST)
{
    if (BST)
    {
        if (BST->Right)
            return FindMax(BST->Right);
        else
            return BST;
    }
}