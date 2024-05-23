// 27. Дан одномерный массив из целых чисел. Найти сумму двух старших разрядов чисел

#include "ThreadsafeQueue.h"
#include <iostream>

#include <thread>
#include <algorithm>


const size_t COUNT = 101;
const size_t NTHREADS = 4;
const size_t BLOCK = 10;

ThreadsafeQueue que;

int sum_senior_ranks(int num)
{
	while (num > 100)
		num /= 10;
	return num;
}

void sum(int* arr, std::atomic_int& result)
{
	while (!que.empty())
	{
		std::pair<int, int> pos;
		if (que.try_pop(pos))
		{
			int left = pos.first, right = pos.second;
			int local_res = 0;
			for (size_t i = left; i < right; ++i)
				local_res += sum_senior_ranks(arr[i]);
			result += local_res;
		}
	}
}

int sum_parallel(int* arr)
{
	std::thread t[NTHREADS - 1];

	int j = 0;
	while (j < COUNT)
	{
		que.push(j, j + BLOCK > COUNT ? COUNT : j + BLOCK);
		j += BLOCK;
	}

	std::atomic_int global_sum{};
	for (size_t i = 0; i < NTHREADS - 1; ++i)
	{
		t[i] = std::thread(sum, arr,  std::ref(global_sum));
	}
	
	sum(arr, global_sum);

	for (size_t i = 0; i < NTHREADS - 1; ++i)
		t[i].join();

	return global_sum;
}

void init_array(int* arr)
{
	for (size_t i = 0; i < COUNT; ++i)
		arr[i] = rand() % 1000;
}

int sum_non_parallel(int* arr)
{
	int result{};
	//sum(arr, 0, COUNT, result);
	std::for_each(arr, arr + COUNT, [&result](int x) {result += sum_senior_ranks(x); });
	return result;
}

int main()
{
	srand(GetTickCount());
	int arr[COUNT];
	init_array(arr);

	std::cout << "non parallel = " << sum_non_parallel(arr) << '\n';
	std::cout << "parallel = " << sum_parallel(arr) << '\n';

	return 0;
}