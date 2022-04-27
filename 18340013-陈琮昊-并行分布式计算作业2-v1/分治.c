#include <stdio.h>
#include <stdlib.h> 
#define N 255 
#define SIZE 256 

int A[SIZE][SIZE];
int B[SIZE][SIZE];
int **C;

// 记录矩阵中一个元素的位置
typedef struct
{
    int lin, col;
}posi;

void product_div_con(posi a_beg, posi a_end, posi b_beg, posi b_end);

int main()
{
    posi a_beg, a_end, b_beg, b_end;
    a_beg.lin = a_beg.col = b_beg.lin = b_beg.col = 0;
    a_end.lin = a_end.col = b_end.lin = b_end.col = N;

    int i,j;
    C = (int **)calloc(SIZE, sizeof(int *));
    for(i = 0; i < SIZE; i++)
    C[i] = (int *)calloc(SIZE, sizeof(int));

    for (i = 0; i < SIZE; i++)
    {
        A[i][i] = 1;
        for(j = 0; j < SIZE; j++)
        B[i][j] = 10;
    }

    product_div_con(a_beg, a_end, b_beg, b_end);
    // print_matrix(C, _N + 1);
    return 0;
}

void product_div_con(posi a_beg, posi a_end, posi b_beg, posi b_end)
{
    // cout<<a_beg.lin<<'_'<<a_beg.col<<'_'<<a_end.lin<<'_'<<a_end.col<<'_'<<b_beg.lin<<'_'<<b_beg.col<<'_'<<b_end.lin<<'_'<<b_end.col<<'_'<<endl;
    // 如果递归在最后只有一个元素，那么计算乘积，返回
    if (a_beg.lin == a_end.lin && a_beg.col == a_end.col)
    {
        // cerr<<"ajsdif\n";
        C[a_beg.lin][b_beg.col] += A[a_beg.lin][a_beg.col] * B[b_beg.lin][b_beg.col];
        // cerr<<C[a_beg.lin][b_beg.col]<<endl;
        return;
    }
    
    // 如果还能继续分下去
    // 将矩阵分为4部分
    posi a00_beg, a00_end, a01_beg, a01_end, a10_beg, a10_end, a11_beg, a11_end;
    posi b00_beg, b00_end, b01_beg, b01_end, b10_beg, b10_end, b11_beg, b11_end;

    // A矩阵的左上块
    a00_beg.lin = a_beg.lin;
    a00_beg.col = a_beg.col;
    a00_end.lin = (a_beg.lin + a_end.lin) / 2;
    a00_end.col = (a_beg.col + a_end.col) / 2;
    // A矩阵的右上块
    a01_beg.lin = a_beg.lin;
    a01_beg.col = (a_beg.col + a_end.col) / 2 + 1;
    a01_end.lin = (a_beg.lin + a_end.lin) / 2;
    a01_end.col = a_end.col;
    // A矩阵的左下块
    a10_beg.lin = (a_beg.lin + a_end.lin) / 2 + 1;
    a10_beg.col = a_beg.col;
    a10_end.lin = a_end.lin;
    a10_end.col = (a_beg.col + a_end.col) / 2;
    // A矩阵的右下块
    a11_beg.lin = (a_beg.lin + a_end.lin) / 2 + 1;
    a11_beg.col = (a_beg.col + a_end.col) / 2 + 1;
    a11_end.lin = a_end.lin;
    a11_end.col = a_end.col;

    // B矩阵的第一块
    b00_beg.lin = b_beg.lin;
    b00_beg.col = b_beg.col;
    b00_end.lin = (b_beg.lin + b_end.col) / 2;
    b00_end.col = (b_beg.col + b_end.col) / 2;
    // B矩阵的右上块
    b01_beg.lin = b_beg.lin;
    b01_beg.col = (b_beg.col + b_end.col) / 2 + 1;
    b01_end.lin = (b_beg.lin + b_end.lin) / 2;
    b01_end.col = b_end.col;
    // B矩阵的左下块
    b10_beg.lin = (b_beg.lin + b_end.lin) / 2 + 1;
    b10_beg.col = b_beg.col;
    b10_end.lin = b_end.lin;
    b10_end.col = (b_beg.col + b_end.col) / 2;
    // B矩阵的右下块
    b11_beg.lin = (b_beg.lin + b_end.lin) / 2 + 1;
    b11_beg.col = (b_beg.col + b_end.col) / 2 + 1;
    b11_end.lin = b_end.lin;
    b11_end.col = b_end.col;

    //下面开始八次递归调用
    // A00 * B00
    product_div_con(a00_beg, a00_end, b00_beg, b00_end);
    // A01 * B10
    product_div_con(a01_beg, a01_end, b10_beg, b10_end);
    // A00 * B01
    product_div_con(a00_beg, a00_end, b01_beg, b01_end);
    // A01 * B111
    product_div_con(a01_beg, a01_end, b11_beg, b11_end);
    // A10 * B00
    product_div_con(a10_beg, a10_end, b00_beg, b00_end);
    // A11 * B10
    product_div_con(a11_beg, a11_end, b10_beg, b10_end);
    // A10 * B01
    product_div_con(a10_beg, a10_end, b01_beg, b01_end);
    // A11 * B11
    product_div_con(a11_beg, a11_end, b11_beg, b11_end);
}

