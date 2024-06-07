// 27. Дан одномерный массив из целых чисел. Найти сумму двух старших разрядов чисел

#include <iostream>
#include <Windows.h>
#include <future>
#include <algorithm>

const size_t COUNT = 101;
const size_t NTHREADS = 4;


int sum_senior_ranks(int num)
{
	while (num > 100)
		num /= 10;
	return num;
}

int sum(int* arr, size_t left, size_t right)
{
	int result{};
	for (size_t i = left; i < right; ++i)
		result += sum_senior_ranks(arr[i]);
	return result;
}

int sum_parallel(int* arr)
{
	std::future<int> t[NTHREADS - 1];
	size_t block = COUNT / NTHREADS;
	for (size_t i = 0; i < NTHREADS - 1; ++i)
	{
		t[i] = std::async(std::launch::async, sum, arr, block * i, block * (i + 1));
	}
	int global_sum = sum(arr, block * (NTHREADS - 1), COUNT);
	for (size_t i = 0; i < NTHREADS - 1; ++i)
		global_sum += t[i].get();
	return global_sum;
}

void init_array(int* arr)
{
	for (size_t i = 0; i < COUNT; ++i)
		arr[i] = rand() % 1000;
}

int sum_non_parallel(int* arr)
{
	//int result{};
	//std::for_each(arr, arr + COUNT, [&result](int x) {result += sum_senior_ranks(x); });
	return sum(arr, 0 , COUNT);
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