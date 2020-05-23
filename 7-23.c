/*
7-23 还原二叉树 (25分)
给定一棵二叉树的先序遍历序列和中序遍历序列，要求计算该二叉树的高度。
*/
#include <stdio.h>
#include <stdlib.h>
typedef struct BNode
{
    char ch;
    struct BNode *left;
    struct BNode *right;
} * BTree;
int get_height(BTree root)
{
    if (root == NULL)
        return (0);
    else
        return (get_height(root->left) > get_height(root->right) ? get_height(root->left) + 1 : get_height(root->right) + 1);
}
BTree get_BT(char *s1, char *s2, int len)
{
    int index = 0;
    int len1, len2;
    BTree tmp, tmp1;
    if (len == 1)
    {
        tmp = (BTree)malloc(sizeof(struct BNode));
        tmp->ch = s1[0];
        tmp->left = NULL;
        tmp->right = NULL;
        return (tmp);
    }
    if (len == 2)
    {
        tmp = (BTree)malloc(sizeof(struct BNode));
        tmp1 = (BTree)malloc(sizeof(struct BNode));
        tmp->ch = s1[0];
        tmp1->ch = s1[1];
        tmp1->left = NULL;
        tmp1->right = NULL;
        if (s1[0] == s2[0])
        {
            tmp->left = NULL;
            tmp->right = tmp1;
        }
        else
        {
            tmp->left = tmp1;
            tmp->right = NULL;
        }
        return (tmp);
    }
    if (len > 2)
    {
        tmp = (BTree)malloc(sizeof(struct BNode));
        while (s1[0] != s2[index])
            index++;
        len1 = index;
        len2 = len - len1 - 1;
        tmp->ch = s1[0];
        tmp->left = get_BT(s1 + 1, s2, len1);
        tmp->right = get_BT(s1 + index + 1, s2 + index + 1, len2);
        return (tmp);
    }
    return (NULL);
}
int main()
{
    int N;
    char s1[51], s2[51];
    BTree root;
    scanf("%d", &N);
    scanf("%s", s1);
    scanf("%s", s2);
    root = get_BT(s1, s2, N);
    printf("%d", get_height(root));
    return (0);
}