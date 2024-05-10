// 27. Дан одномерный массив из целых чисел. Найти сумму двух старших разрядов чисел

#include <iostream>
#include <Windows.h>
#include <thread>
#include <algorithm>

const size_t COUNT = 101;
const size_t NTHREADS = 4;


int sum_senior_ranks(int num)
{
	while (num > 100)
		num /= 10;
	return num;
}

void sum(int* arr, size_t left, size_t right, int& result)
{
	result = 0;
	for (size_t i = left; i < right; ++i)
		result += sum_senior_ranks(arr[i]);
}

int sum_parallel(int* arr)
{
	std::thread t[NTHREADS - 1];
	int result[NTHREADS - 1];
	size_t block = COUNT / NTHREADS;
	for (size_t i = 0; i < NTHREADS - 1; ++i)
	{
		t[i] = std::thread(sum, arr, block * i, block * (i + 1), std::ref(result[i]));
	}
	int global_sum{};
	sum(arr, block * (NTHREADS - 1), COUNT, global_sum);

	for (size_t i = 0; i < NTHREADS - 1; ++i)
		t[i].join();
	
	for (size_t i = 0; i < NTHREADS - 1; ++i)
		global_sum += result[i];
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
	//std::for_each(arr, arr + COUNT, [&result](int x) {result += sum_senior_ranks(x); });
	//return result;
	sum(arr, 0, COUNT, result);
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