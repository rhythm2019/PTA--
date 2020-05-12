/*
本题要求按照先序遍历的顺序输出给定二叉树的叶结点。
函数接口定义：
void PreorderPrintLeaves( BinTree BT );
*/
#include <stdio.h>
#include <stdlib.h>

typedef char ElementType;
typedef struct TNode *Position;
typedef Position BinTree;
struct TNode
{
    ElementType Data;
    BinTree Left;
    BinTree Right;
};

BinTree CreatBinTree(); /* 实现细节忽略 */
void PreorderPrintLeaves(BinTree BT);

int main()
{
    BinTree BT = CreatBinTree();
    printf("Leaf nodes are:");
    PreorderPrintLeaves(BT);
    printf("\n");

    return 0;
}
void PreorderPrintLeaves(BinTree BT)
{
    if (BT == NULL)
        return;
    else if (BT->Left == NULL && BT->Right == NULL)
        printf(" %c", BT->Data);
    else
    {
        PreorderPrintLeaves(BT->Left);
        PreorderPrintLeaves(BT->Right);
    }
    return;
}