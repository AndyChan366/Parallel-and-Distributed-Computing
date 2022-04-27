#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>
#define SIZE 1000000

// 线程数量
int thread_count = 4;
// 第一个向量
double vec1[SIZE];
// 第二个向量
double vec2[SIZE];
// 计算加法的结果
double result[SIZE];
// 每个线程执行的函数
void *sumvec(void *n)
{
    long number = (long)n;
    int i;
    int incre = SIZE / thread_count;
    int first = number * incre;
    int last = (number + 1) * incre;

    for (i = first; i < last; i++)
    {
        result[i] = vec1[i] + vec2[i];
    }
    return NULL;
}

int main()
{
    long thread;
    pthread_t *thread_handles;
    int i;
    srand(time(NULL));
    thread_handles =(pthread_t *)malloc(thread_count * sizeof(pthread_t));
    for(i = 0; i < SIZE; i++)           //随机初始化数据 
    {
        vec1[i] = rand() / 9999;
        vec2[i] = rand() / 9999;
    }

    struct timeval tv1, tv2;
    gettimeofday(&tv1, NULL);
    for (thread = 0; thread < thread_count; thread++){
        pthread_create(&thread_handles[thread], NULL, sumvec, (void *)thread);
    }
    for (thread = 0; thread < thread_count; thread++){
        pthread_join(thread_handles[thread], NULL);
    }
    gettimeofday(&tv2, NULL);
    // 计算高维向量加法运行时间
    printf("%ld\n",(tv2.tv_sec - tv1.tv_sec) * 1000000 + tv2.tv_usec - tv1.tv_usec);
    //printf("The first three elements of result is %lf %lf %lf\n",result[0], result[1], result[2]);
    free(thread_handles);    
    return 0;
}



