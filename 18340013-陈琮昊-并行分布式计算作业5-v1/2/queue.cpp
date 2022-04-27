#include <chrono>
#include <omp.h> 
#include <iostream>
#include "Queue.hpp"
MultiAccessQueue<int> q;
void producer(int count)
{
	for (int i = 0; i < count; i++)
		q.push(i);
}
void consumer(int count)
{
	for (int i = 0; i < count; i++)
		q.pop();
}
int main()
{
	int number;
	std::cout << "please input the number of producer-consumers: ";
	std::cin >> number;
	auto begin = std::chrono::system_clock::now();
#pragma omp parallel for
	for (int i = 0; i < number; i++)
		producer(1000);
#pragma omp parallel for
	for (int i = 0; i < number; i++)
		consumer(1000);
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - begin;
	std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
}




