// 27. Дан одномерный массив из целых чисел. Найти сумму двух старших разрядов чисел

#include <iostream>
#include <Windows.h>
#include <omp.h>

const size_t COUNT = 10;
const size_t NTHREADS = 4;


int sum_senior_ranks(int num)
{
	while (num > 100)
		num /= 10;
	return num;
}

int sum(int* arr, size_t size)
{
	int result = 0;
	for (size_t i = 0; i < size; ++i)
		result += sum_senior_ranks(arr[i]);
	return result;

}

int sum_parallel(int* arr)
{
	int global_sum = 0;
	#pragma omp parallel shared(arr) reduction(+:global_sum)
	{
		int local_sum = 0;
	#pragma omp for
		for (int i = 0; i < COUNT; ++i)
			local_sum += sum_senior_ranks(arr[i]);
		global_sum += local_sum;
	}
	return global_sum;
}

void init_array(int* arr)
{
	for (size_t i = 0; i < COUNT; ++i)
		arr[i] = rand() % 1000;
}

int sum_non_parallel(int* arr)
{
	return sum(arr, COUNT);
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