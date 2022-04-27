#include <stdio.h>
#include <stdlib.h>

#define N 256 

typedef struct
{
    int lin, col;
}posi;

typedef struct
{
    int **mat;
    int size;
} matrix;

matrix C;

void strassen(matrix *mptr, posi c_beg, posi c_end, matrix A, matrix B);
void add_mat(matrix *mptr, matrix A, matrix B);
void sub_mat(matrix *mptr, matrix A, matrix B);
void initial(matrix *mptr, int size);
void print_mat(matrix A);

int main()
{

    matrix A, B;
    initial(&A, N);
    initial(&B, N);
    initial(&C, N);


    posi c_beg, c_end;
    c_beg.lin = c_beg.col = 0;
    c_end.lin = c_end.col = 255;

    int i, j;
    for(i = 0; i < N; i++)
    A.mat[i][i] = 1;

    add_mat(&B, A, B);
    // print_mat(A);
    // print_mat(B);
    strassen(&C, c_beg, c_end, A, B);
    // print_mat(C);

    return 0;
}

void strassen(matrix *mptr, posi c_beg, posi c_end, matrix A, matrix B)
{
    // fprintf(stderr, "%d_%d_%d_%d_\n", c_beg.lin, c_beg.col, c_end.lin, c_end.col);
    if(c_beg.lin == c_end.lin && c_beg.col == c_end.col)
    {
        mptr->mat[0][0] = A.mat[0][0] * B.mat[0][0];
        return;
    }
    matrix A00, A01, A10, A11, B00, B01, B10, B11;
    matrix d1, d2, d3, d4, d5, d6, d7;
    matrix temp1, temp2, temp3, C00, C01, C10, C11;

    int hsize = A.size / 2;

    initial(&A00, hsize);
    initial(&A01, hsize);
    initial(&A10, hsize);
    initial(&A11, hsize);
    initial(&B00, hsize);
    initial(&B01, hsize);
    initial(&B10, hsize);
    initial(&B11, hsize);

    initial(&d1, hsize);
    initial(&d2, hsize);
    initial(&d3, hsize);
    initial(&d4, hsize);
    initial(&d5, hsize);
    initial(&d6, hsize);
    initial(&d7, hsize);
    initial(&temp1, hsize);
    initial(&temp2, hsize);
    initial(&temp3, hsize);
    initial(&C00, hsize);
    initial(&C01, hsize);
    initial(&C10, hsize);
    initial(&C11, hsize);

    int i, j;
    for(i = 0; i < A.size; i++)
        for (j = 0; j < A.size; j++)
        {
            if(i < hsize && j < hsize)
            {
                A00.mat[i][j] = A.mat[i][j];
                B00.mat[i][j] = B.mat[i][j];
            }
            else if(i < hsize && j >= hsize)
            {
                A01.mat[i][j - hsize] = A.mat[i][j];
                B01.mat[i][j - hsize] = B.mat[i][j];
            }
            else if(i >= hsize && j < hsize)
            {
                A10.mat[i - hsize][j] = A.mat[i][j];
                B10.mat[i - hsize][j] = B.mat[i][j];
            }
            else if(i >= hsize && j >= hsize)
            {
                A11.mat[i - hsize][j - hsize] = A.mat[i][j];
                B11.mat[i - hsize][j - hsize] = B.mat[i][j];
            }
        }

    // fprintf(stderr, "asdfjk\n");
    posi d_beg, d_end;
    d_beg.lin = d_beg.col = 0;
    d_end.lin = d_end.col = hsize - 1;

    // 计算d1
    add_mat(&temp1, A00, A11);
    add_mat(&temp2, B00, B11);
    strassen(&d1, d_beg, d_end, temp1, temp2);
    // 计算d2
    add_mat(&temp1, A10, A11);
    strassen(&d2, d_beg, d_end, temp1, B00);
    // 计算d3
    sub_mat(&temp1, B01, B11);
    strassen(&d3, d_beg, d_end, A00, temp1);
    // 计算d4
    sub_mat(&temp1, B10, B00);
    strassen(&d4, d_beg, d_end, A11, temp1);
    // 计算d5
    add_mat(&temp1, A00, A01);
    strassen(&d5, d_beg, d_end, temp1, B11);
    // 计算d6
    sub_mat(&temp1, A10, A00);
    add_mat(&temp2, B00, B01);
    strassen(&d6, d_beg, d_end, temp1, temp2);
    // 计算d7
    sub_mat(&temp1, A01, A11);
    add_mat(&temp2, B10, B11);
    strassen(&d7, d_beg, d_end, temp1, temp2);

    // print_mat(d1);
    // print_mat(d2);
    // print_mat(d3);
    // print_mat(d4);
    // print_mat(d5);
    // print_mat(d6);
    // print_mat(d7);
    // 计算C00
    add_mat(&temp1, d1, d4);
    sub_mat(&temp2, temp1, d5);
    add_mat(&C00, temp2, d7);
    // print_mat(temp1);
    // print_mat(temp2);
    // fprintf(stderr, "c00:");
    // print_mat(C00);
    // 计算C01
    add_mat(&C01, d3, d5);
    // 计算C10
    add_mat(&C10, d2, d4);
    // 计算C11
    add_mat(&temp1, d1, d3);
    sub_mat(&temp2, temp1, d2);
    add_mat(&C11, temp2, d6);

    
    for(i = 0; i < A.size; i++)
        for (j = 0; j < A.size; j++)
        {
            if(i < hsize && j < hsize)
            mptr->mat[i][j] = C00.mat[i][j];
            else if(i < hsize && j >= hsize)
            mptr->mat[i][j] = C01.mat[i][j - hsize];
            else if(i >= hsize && j < hsize)
            mptr->mat[i][j] = A01.mat[i - hsize][j];
            else if(i >= hsize && j >= hsize)
            mptr->mat[i][j] = C11.mat[i - hsize][j - hsize];
        }

}

void add_mat(matrix *mptr, matrix A, matrix B)
{
    int i, j;
    for (i = 0; i < A.size; i++)
    for (j = 0; j < A.size; j++)
    mptr->mat[i][j] = A.mat[i][j] + B.mat[i][j];
}

void sub_mat(matrix *mptr, matrix A, matrix B)
{
    int i, j;
    for (i = 0; i < A.size; i++)
    for (j = 0; j < A.size; j++)
    mptr->mat[i][j] = A.mat[i][j] - B.mat[i][j];
}

void initial(matrix *mptr, int size)
{
    int i, j;
    mptr->size = size;
    mptr->mat = (int **)calloc(size, sizeof(int *));
    for(i = 0; i < size; i++)
    mptr->mat[i] = (int *)calloc(size, sizeof(int));

}

void print_mat(matrix A)
{
    int i, j;
    for(i = 0; i < A.size; i++)
    {
        for (j = 0; j < A.size; j++)
            fprintf(stderr, "%d ", A.mat[i][j]);
        putchar('\n');
    }
}
