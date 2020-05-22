/*
给定两棵树T1和T2。如果T1可以通过若干次左右孩子互换就变成T2，则我们称两棵树是“同构”的。
例如图1给出的两棵树就是同构的，因为我们把其中一棵树的结点A、B、G的左右孩子互换后，就得到另外一棵树。而图2就不是同构的。
*/
#include <stdio.h>
#include <stdlib.h>
#define ERROR NULL
typedef struct TNODE
{
    char data;
    int left;
    int right;
} TNode;
typedef struct BTREE
{
    int root;
    int num_node;
    TNode *Tree;
} BTree;
void init_Tree(BTree *Tree)
{
    int N, i, *check;
    char left, right;
    scanf("%d\n", &N);
    Tree->num_node = N;
    if (N)
    {
        Tree->Tree = (TNode *)(malloc(N * sizeof(TNode)));
        check = (int *)(malloc(N * sizeof(int)));
        for (i = 0; i < N; i++)
            check[i] = 0;
        for (i = 0; i < N; i++)
        {
            scanf("%c %c %c\n", &(Tree->Tree[i].data), &left, &right);
            if (left == '-')
                Tree->Tree[i].left = -1;
            else
            {
                Tree->Tree[i].left = left - '0';
                check[Tree->Tree[i].left] = 1;
            }
            if (right == '-')
                Tree->Tree[i].right = -1;
            else
            {
                Tree->Tree[i].right = right - '0';
                check[Tree->Tree[i].right] = 1;
            }
        }
        for (i = 0; i < N; i++)
            if (check[i] == 0)
            {
                Tree->root = i;
                free(check);
                return;
            }
    }
    else
    {
        Tree->Tree = NULL;
        Tree->root = -1;
    }
}
int isomorphism(TNode *T1, int root1, TNode *T2, int root2)
{
    if (root1 == -1 && root2 == -1)
        return (1);
    else if ((root1 == -1 && root2 != -1) || (root1 != -1 && root2 == -1))
        return (0);
    else
    {
        if (T1[root1].data != T2[root2].data)
            return (0);
        else
        {
            return (isomorphism(T1, T1[root1].left, T2, T2[root2].left) && isomorphism(T1, T1[root1].right, T2, T2[root2].right)) || (isomorphism(T1, T1[root1].left, T2, T2[root2].right) && isomorphism(T1, T1[root1].right, T2, T2[root2].left));
        }
    }
}
int main()
{
    int N, i;
    BTree T1, T2;
    init_Tree(&T1);
    init_Tree(&T2);
    if (isomorphism(T1.Tree, T1.root, T2.Tree, T2.root))
        printf("Yes");
    else
        printf("No");
    return (0);
}
