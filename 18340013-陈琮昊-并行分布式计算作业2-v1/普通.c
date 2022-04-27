#include <stdio.h>


int A[256][256];
int B[256][256];
int C[256][256];

int main()
{
    // 开始做传统矩阵乘法
    int i, j, k;
    for(i = 0; i < 256; i++)
    for(j = 0; j < 256; j++)
    for(k = 0; k < 256; k++)
    C[i][j] += A[i][k] * B[k][j];

    return 0;
}

