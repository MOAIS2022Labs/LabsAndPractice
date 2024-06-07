// 27. Дан одномерный массив из целых чисел. Найти сумму двух старших разрядов чисел

#include <iostream>
#include <Windows.h>
#include <process.h>
#include <algorithm>

const size_t COUNT = 101;
const size_t NTHREADS = 4;

struct INFORM
{
	int* arr;
	size_t left, right;
	int sum{};
};


int sum_senior_ranks(int num)
{
	while (num > 100)
		num /= 10;
	return num;
}

unsigned __stdcall sum(void* arg)
{
	INFORM* inform = (INFORM*)arg;
	int local_sum{};
	for (size_t i = inform->left; i < inform->right; ++i)
		local_sum += sum_senior_ranks(inform->arr[i]);
	inform->sum = local_sum;
	if (inform->right != COUNT)
		_endthreadex(0);
	return 0;
}

int sum_parallel(int* arr)
{
	HANDLE t[NTHREADS - 1];
	size_t block = COUNT / NTHREADS;
	INFORM inform[NTHREADS];
	for (size_t i = 0; i < NTHREADS; ++i)
	{
		inform[i].arr = arr;
		inform[i].left = block * i;
		inform[i].right = (i != NTHREADS - 1) ? block * (i + 1) : COUNT;
		if (i != NTHREADS - 1)
			t[i] = (HANDLE)_beginthreadex(nullptr, 0, &sum, inform + i, 0, nullptr);
	}
	sum(inform + NTHREADS - 1);

	WaitForMultipleObjects(NTHREADS - 1, t, true, INFINITE);

	
	for (size_t i = 0; i < NTHREADS - 1; ++i)
		CloseHandle(t[i]);
	int global_sum{};
	for (size_t i = 0; i < NTHREADS; ++i)
		global_sum += inform[i].sum;
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