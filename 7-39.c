/*
在火星上有个魔法商店，提供魔法优惠券。
每个优惠劵上印有一个整数面值K，表示若你在购买某商品时使用这张优惠劵，可以得到K倍该商品价值的回报！
该商店还免费赠送一些有价值的商品，但是如果你在领取免费赠品的时候使用面值为正的优惠劵，则必须倒贴给商店K倍该商品价值的金额…… 
但是不要紧，还有面值为负的优惠劵可以用！（真是神奇的火星）
DATE:20200801
*/
#include <stdio.h>
#include <stdlib.h>
int cmpfunc(const void *a, const void *b)
{
    return (*(int *)b - *(int *)a);
}
int main()
{
    int i1, i2, j1, j2, N, M;
    long long cost = 0;
    int *A, *B;
    scanf("%d", &N);
    A = (int *)malloc(N * sizeof(int));
    for (i1 = 0; i1 < N; i1++)
        scanf("%d", A + i1);
    scanf("%d", &M);
    B = (int *)malloc(M * sizeof(int));
    for (i1 = 0; i1 < M; i1++)
        scanf("%d", B + i1);
    qsort(A, N, sizeof(int), cmpfunc);
    qsort(B, M, sizeof(int), cmpfunc);
    i1 = 0;
    i2 = 0;
    j1 = N - 1;
    j2 = M - 1;
    while (i1 < N && i2 < M && A[i1] > 0 && B[i2] > 0)
        cost += A[i1++] * B[i2++];
    while (j1 >= 0 && j2 >= 0 && A[j1] < 0 && B[j2] < 0)
        cost += A[j1--] * B[j2--];
    printf("%lld", cost);
    return (0);
}