#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define SIZE 1000 

int **mat;
int *vec;
int *res;
int thread = 4;

void *multiply(void *r)
{
    long rank = (long)r;
    int len = SIZE / thread;
    int first = rank * len;
    int last = (rank + 1) * len;

    int i, j;
    for(i = first; i < last; i++)
        for(j = 0; j < SIZE; j++)
            res[i] += vec[j] * mat[i][j];
    
    return NULL;
}

int main()
{
    long i, j;
    mat = (int **)calloc(SIZE, sizeof(int *));
    for(i = 0; i < SIZE; i++)
        mat[i] = (int *)calloc(SIZE, sizeof(int));
    vec = (int *)calloc(SIZE, sizeof(int));
    res = (int *)calloc(SIZE, sizeof(int));
    //new一个矩阵和向量 
    for(i = 0; i < SIZE; i++)
    {
        mat[i][i] = 1;
        vec[i] = i + 1;
    } 
    //初始化，不妨取单位阵、元素赋值为序号的向量 
    pthread_t *handles = (pthread_t *)malloc(thread * sizeof(pthread_t));
    for(i = 0; i < thread; i++)
        pthread_create(&handles[i], NULL, multiply,(void *)i);

    for(i = 0; i < thread; i++)
        pthread_join(handles[i], NULL);

    printf("calculate result:\n");
    for(i = 0; i < SIZE; i++)
        printf("%d ", res[i]);
    printf("\n");
    //打印结果 
    free(handles);
    free(vec);
    free(res);
    for(i = 0; i < SIZE; i++)
        free(mat[i]);
    free(mat);
    //delete 
    return 0;
}



