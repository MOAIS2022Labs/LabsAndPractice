// 27. Дан одномерный массив из целых чисел. Найти сумму двух старших разрядов чисел

#include <iostream>
#include <Windows.h>
#include <thread>
#include <atomic>

const size_t COUNT = 101;
const size_t NTHREADS = 4;


int sum_senior_ranks(int num)
{
	while (num > 100)
		num /= 10;
	return num;
}

void sum(int* arr, size_t left, size_t right, std::atomic_int& result)
{
	int local_res = 0;
	for (size_t i = left; i < right; ++i)
		local_res += sum_senior_ranks(arr[i]);
	result += local_res;

}

int sum_parallel(int* arr)
{
	std::thread t[NTHREADS - 1];
	size_t block = COUNT / NTHREADS;
	std::atomic_int global_sum{};
	for (size_t i = 0; i < NTHREADS - 1; ++i)
		t[i] = std::thread(sum, arr, block * i, block * (i + 1), std::ref(global_sum));
	
	sum(arr, block * (NTHREADS - 1), COUNT, global_sum);

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
	std::atomic_int result{};
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