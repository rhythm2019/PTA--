/*
本题要求给定二叉树的高度。
函数接口定义：
int GetHeight( BinTree BT );
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
int GetHeight(BinTree BT);

int main()
{
    BinTree BT = CreatBinTree();
    printf("%d\n", GetHeight(BT));
    return 0;
}
int GetHeight(BinTree BT)
{
    if (BT == NULL)
        return (0);
    else if (BT->Left == NULL && BT->Right == NULL)
        return (1);
    else
        return (GetHeight(BT->Left) >= GetHeight(BT->Right) ? GetHeight(BT->Left) + 1 : GetHeight(BT->Right) + 1);
}