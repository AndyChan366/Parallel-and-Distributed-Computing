#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#define SIZE 1000000

double vec1[SIZE];
double vec2[SIZE];
double result[SIZE];

//使用for循环计算高维向量加法，并返回计算时间
long usefor(double *vec1, double *vec2, double *result)
{
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for(int i = 0; i < SIZE; i++)
    {
        result[i] = vec1[i] + vec2[i];
    }
    gettimeofday(&tv2, NULL);
    return (tv2.tv_sec - tv1.tv_sec) * 1000000 + tv2.tv_usec - tv1.tv_usec;
}


int main()
{
    srand(time(NULL));
    for(int i = 0; i < SIZE; i++)
    {
        vec1[i] = rand() / 1000;                   //随机生成数据 
        vec2[i] = rand() / 1000;
    }

    clock_t time1 = usefor(vec1, vec2, result);
    printf("%ld\n", time1);

    return 0;
}






