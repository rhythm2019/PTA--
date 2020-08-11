/*
对于二叉搜索树，我们规定任一结点的左子树仅包含严格小于该结点的键值，而其右子树包含大于或等于该结点的键值。如果我们交换每个节点的左子树和右子树，得到的树叫做镜像二叉搜索树。
现在我们给出一个整数键值序列，请编写程序判断该序列是否为某棵二叉搜索树或某镜像二叉搜索树的前序遍历序列，如果是，则输出对应二叉树的后序遍历序列。
DATE:20200721
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct node
{
    int No; //index
    struct node *left, *right;
};
void Bubble_sort(int *A, int count)
{
    int i, j, tmp;
    for (i = 0; i < count - 1; i++)
        for (j = count - 1; j > i; j--)
            if (A[j] < A[j - 1])
            {
                tmp = A[j - 1];
                A[j - 1] = A[j];
                A[j] = tmp;
            }
    return;
}
void generate_tree(struct node *root, int *preorder, int *inorder, int count, int la, int lb, int *Flag)
{
    int i;
    if (*Flag == 0 || count == 0)
        return;
    //search
    root->No = la;
    for (i = 0; i < count; i++)
    {
        if (inorder[lb + i] == preorder[la])
            break;
    }
    if (i == count)
    {
        *Flag = 0;
        return;
    }
    else
    {
        if (i == 0)
            root->left = NULL;
        else
        {
            root->left = (struct node *)malloc(sizeof(struct node));
            generate_tree(root->left, preorder, inorder, i, la + 1, lb, Flag);
        }
        if (count - i - 1 == 0)
            root->right = NULL;
        else
        {
            root->right = (struct node *)malloc(sizeof(struct node));
            generate_tree(root->right, preorder, inorder, count - i - 1, la + i + 1, lb + i + 1, Flag);
        }
    }
    return;
}
void generate_tree1(struct node *root, int *preorder, int *inorder, int count, int la, int lb, int *Flag)
{
    int i;
    if (*Flag == 0 || count == 0)
        return;
    //search
    root->No = la;
    for (i = count - 1; i >= 0; i--)
    {
        if (inorder[lb + i] == preorder[la])
            break;
    }
    if (i == -1)
    {
        *Flag = 0;
        return;
    }
    else
    {
        if (i == 0)
            root->left = NULL;
        else
        {
            root->left = (struct node *)malloc(sizeof(struct node));
            generate_tree(root->left, preorder, inorder, i, la + 1, lb, Flag);
        }
        if (count - i - 1 == 0)
            root->right = NULL;
        else
        {
            root->right = (struct node *)malloc(sizeof(struct node));
            generate_tree(root->right, preorder, inorder, count - i - 1, la + i + 1, lb + i + 1, Flag);
        }
    }
    return;
}
void postorder(struct node *root, int *preorder)
{
    if (root)
    {
        postorder(root->left, preorder);
        postorder(root->right, preorder);
        printf("%d ", preorder[root->No]);
    }
    return;
}
//search
int main()
{
    int i, tmp, N, number, Flag = 1;
    int *A, *B;
    struct node root = {-1, NULL, NULL};
    scanf("%d", &N);
    A = (int *)malloc(N * sizeof(int));
    B = (int *)malloc(N * sizeof(int));
    for (i = 0; i < N; i++)
    {
        scanf("%d", &number);
        A[i] = number;
        B[i] = number;
    }
    Bubble_sort(B, N);
    generate_tree(&root, A, B, N, 0, 0, &Flag);
    if (Flag == 0)
    {
        for (i = 0; i < N / 2; i++)
        {
            tmp = B[i];
            B[i] = B[N - 1 - i];
            B[N - 1 - i] = tmp;
        }
        Flag = 1;
        generate_tree1(&root, A, B, N, 0, 0, &Flag);
    }
    if (Flag)
    {
        printf("YES\n");
        postorder(root.left, A);
        postorder(root.right, A);
        printf("%d", A[0]);
    }
    else
    {
        printf("NO\n");
    }
    return (0);
}