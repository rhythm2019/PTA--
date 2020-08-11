/*
哈利·波特要考试了，他需要你的帮助。这门课学的是用魔咒将一种动物变成另一种动物的本事。
例如将猫变成老鼠的魔咒是haha，将老鼠变成鱼的魔咒是hehe等等。
反方向变化的魔咒就是简单地将原来的魔咒倒过来念，例如ahah可以将老鼠变成猫。
另外，如果想把猫变成鱼，可以通过念一个直接魔咒lalala，也可以将猫变老鼠、老鼠变鱼的魔咒连起来念：hahahehe。
现在哈利·波特的手里有一本教材，里面列出了所有的变形魔咒和能变的动物。老师允许他自己带一只动物去考场，要考察他把这只动物变成任意一只指定动物的本事。
于是他来问你：带什么动物去可以让最难变的那种动物（即该动物变为哈利·波特自己带去的动物所需要的魔咒最长）需要的魔咒最短？
例如：如果只有猫、鼠、鱼，则显然哈利·波特应该带鼠去，因为鼠变成另外两种动物都只需要念4个字符；而如果带猫去，则至少需要念6个字符才能把猫变成鱼；同理，带鱼去也不是最好的选择。
DATE:20200612
*/
#include <stdio.h>
#include <stdlib.h>
#define MaxVertexNum 100
#define INFITY 1000001
struct Graph
{
    int nv, ne;
    int Weight[MaxVertexNum][MaxVertexNum];
};

void FLOYED(int Weight[MaxVertexNum][MaxVertexNum], int nv)
{
    int i, j, k;
    for (k = 0; k < nv; k++)
        for (i = 0; i < nv; i++)
            for (j = 0; j < nv; j++)
                if (Weight[i][k] + Weight[k][j] < Weight[i][j])
                    Weight[i][j] = Weight[i][k] + Weight[k][j];
    return;
}

int main()
{
    int i, j, MIN;
    int node1, node2, distance;
    int result_i, result_j, tmp_j, LW; //longWord
    struct Graph G;
    //init Graph
    scanf("%d %d", &G.nv, &G.ne);
    for (i = 0; i < G.nv; i++)
        for (j = 0; j < G.nv; j++)
        {
            if (i == j)
                G.Weight[i][j] = 0;
            else
                G.Weight[i][j] = INFITY;
        }
    //insert edge
    for (i = 0; i < G.ne; i++)
    {
        scanf("%d %d %d", &node1, &node2, &distance);
        G.Weight[node1 - 1][node2 - 1] = distance;
        G.Weight[node2 - 1][node1 - 1] = distance;
    }
    FLOYED(G.Weight, G.nv);
    result_i = -1;
    result_j = -1;
    MIN = INFITY;
    for (i = 0; i < G.nv; i++)
    {
        LW = 0;
        for (j = 0; j < G.nv; j++)
        {
            if (G.Weight[i][j] > LW)
            {
                LW = G.Weight[i][j];
                tmp_j = j;
            }
        }
        if (LW < MIN)
        {
            MIN = LW;
            result_i = i;
            result_j = tmp_j;
        }
    }
    if (result_i != -1)
        printf("%d %d", result_i + 1, G.Weight[result_i][result_j]);
    else
        printf("0");
    return (0);
}
