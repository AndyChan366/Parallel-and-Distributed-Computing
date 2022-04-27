#include <immintrin.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/time.h>
#define SIZE 1000000

double vec1[SIZE];
double vec2[SIZE];
double result[SIZE];
__m256d arr1[SIZE / 4];
__m256d arr2[SIZE / 4];
__m256d res[SIZE / 4];

//使用AVX计算高维向量加法，并返回计算时间
long useavx(double *vec1, double *vec2, double *result)
{
    for(int i = 0; i < SIZE; i += 4)
    {
        arr1[i / 4] = _mm256_setr_pd(vec1[i], vec1[i + 1], vec1[i + 2], vec1[i + 3]);
        arr2[i / 4] = _mm256_setr_pd(vec2[i], vec2[i + 1], vec2[i + 2], vec2[i + 3]);
    }
    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for(int i = 0; i < SIZE / 4; i++)
    {
        res[i] = _mm256_add_pd(arr1[i], arr2[i]);
    }
    gettimeofday(&tv2, NULL); //测试的时间为AVX向量加法的时间
    //数据转换为结果
    for(int i = 0; i < SIZE / 4; i++)
    {
        result[i * 4] = res[i][0];
        result[i * 4 + 1] = res[i][1];
        result[i * 4 + 2] = res[i][2];
        result[i * 4 + 3] = res[i][3];
    }

    return (tv2.tv_sec - tv1.tv_sec) * 1000000 + tv2.tv_usec - tv1.tv_usec;
}

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

    clock_t time1 = useavx(vec1, vec2, result);
    printf("AVX takes %ld\n",time1);
    clock_t time2 = usefor(vec1, vec2, result);
    printf("For takes %ld\n", time2);

    return 0;
}




