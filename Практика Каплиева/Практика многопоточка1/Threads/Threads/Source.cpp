#include <iostream>
#include <process.h>
#include <Windows.h>

const size_t COUNT = 101;
const size_t NTHREADS = 4;

struct INFORM
{
	int* a;
	size_t left, right;
	int sum = 0;
};

unsigned __stdcall sum(void* arg)
{
	INFORM* inform = (INFORM*)arg;
	int local_sum = 0;
	for (size_t i = inform->left; i < inform->right; ++i)
		local_sum += inform->a[i];
	inform->sum = local_sum;
	std::cout << "ID from WinAPI: " << ::GetCurrentThreadId() << ' ' << local_sum << '\n';
	if (inform->right != COUNT) // если не main
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
		inform[i].a = arr;
		inform[i].left = block * i;
		if (i != NTHREADS - 1)
			inform[i].right = block * (i + 1);
		else
			inform[i].right = COUNT;
		if (i != NTHREADS - 1)
			t[i] = (HANDLE)_beginthreadex(nullptr, 0, &sum, &inform[i], 0, nullptr); // создали 3 потока, четвЄртый Ч main
	}
	sum(inform + NTHREADS - 1); // main тоже выполн€ет параллельную задачу
	WaitForMultipleObjects(NTHREADS - 1, t, true, INFINITE); // барьерна€ синхронизаци€
															// main ждЄт завершени€ работы 3-х потоков

	for (size_t i = 0; i < NTHREADS - 1; ++i)
		CloseHandle(t[i]);

	int global_sum = 0;
	for (size_t i = 0; i < NTHREADS; ++i)
		global_sum += inform[i].sum;
	
	return global_sum;
}

int sum_non_parallel(int* arr)
{
	int result = 0;
	for (size_t i = 0; i < COUNT; ++i)
		result += arr[i];
	return result;
}

void init_array(int* arr)
{
	for (size_t i = 0; i < COUNT; ++i)
		arr[i] = rand() % 100;
}

int main()
{
	srand(GetTickCount());
	int array[COUNT];
	init_array(array);

	std::cout << "sum non parallel = " << sum_non_parallel(array) << '\n'
		<< "sum parallel = " << sum_parallel(array) << '\n';
	return 0;
}