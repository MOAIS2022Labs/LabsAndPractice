#include <iostream>
#include <process.h>
#include <Windows.h>
#include <future>
#include <thread>
#include <atomic>
#include "threadsafe_stack.h"

const size_t COUNT = 101;
const size_t NTHREADS = 4;

void find_max_thread(int* arr, size_t left, size_t right, std::pair<int, int>& max)
{
	int ma = arr[left], ma_i = left;
	for (size_t i = left; i < right; ++i)
	{
		if (arr[i] > ma)
		{
			ma = arr[i];
			ma_i = i;
		}
		else
			if (arr[i] == ma)
				ma_i = i;
	}
	max.first = ma;
	max.second = ma_i;
}

int max_parallel_thread(int* arr)
{
	std::thread t[NTHREADS - 1];
	size_t block = COUNT / NTHREADS;
	std::pair<int, int> results[NTHREADS - 1];
	for (size_t i = 0; i < NTHREADS - 1; ++i)
	{
		t[i] = std::thread(find_max_thread, arr, i * block, (i + 1) * block, std::ref(results[i]));
	}
	std::pair<int, int> global_pair;
	find_max_thread(arr, block * (NTHREADS - 1), COUNT, global_pair);

	for (size_t i = 0; i < NTHREADS - 1; ++i)
		t[i].join();

	for (size_t i = 0; i < NTHREADS - 1; ++i)
		if (global_pair.first < results[i].first)
			global_pair = results[i];
		else
			if (global_pair.first == results[i].first && global_pair.second < results[i].second)
				global_pair.second = results[i].second;

	return global_pair.second;
}

//для future
std::pair<int, int> find_max_future(int* arr, size_t left, size_t right)
{
	int ma = arr[left], ma_i = left;
	for (size_t i = left; i < right; ++i)
	{
		if (arr[i] > ma)
		{
			ma = arr[i];
			ma_i = i;
		}
		else
			if (arr[i] == ma)
				ma_i = i;
	}
	return { ma, ma_i };
}

int max_parallel_future(int* arr)
{
	std::future<std::pair<int, int>> t[NTHREADS - 1];
	size_t block = COUNT / NTHREADS;

	for (size_t i = 0; i < NTHREADS - 1; ++i)
	{
		t[i] = std::async(std::launch::async, find_max_future, arr, i * block, (i + 1) * block);
	}
	std::pair<int, int> global_pair = find_max_future(arr, block * (NTHREADS - 1), COUNT);


	for (size_t i = 0; i < NTHREADS - 1; ++i)
	{
		auto pr = t[i].get();
		if (global_pair.first < pr.first)
			global_pair = pr;
		else
			if (global_pair.first == pr.first && global_pair.second < pr.second)
				global_pair.second = pr.second;
	}

	return global_pair.second;
}

int max_non_parallel(int* arr)
{
	std::pair<int, int> global_pair;
	find_max_thread(arr, 0, COUNT, global_pair);
	return global_pair.second;
}

void init_array(int* arr)
{
	for (size_t i = 0; i < COUNT; ++i)
		arr[i] = rand() % 100;
}

std::atomic_flag aflag = ATOMIC_FLAG_INIT;

void find_max_critical_section(int* arr, size_t left, size_t right, std::pair<int, int>& global_max)
{
	int ma = arr[left], ma_i = left;
	for (size_t i = left; i < right; ++i)
	{
		if (arr[i] > ma)
		{
			ma = arr[i];
			ma_i = i;
		}
		else
			if (arr[i] == ma)
				ma_i = i;
	}
	// в лабе спросить, если макс больше или равен, тогда ждём
	if (ma > global_max.first) // вроде так
	{
		while (aflag.test_and_set())
			Sleep(0);

		if (ma > global_max.first)
		{
			global_max = { ma, ma_i };
		}
		else if (ma == global_max.first && global_max.second < ma_i)
			global_max.second = ma_i;
		aflag.clear();
	}
}

int max_parallel_critical(int* arr)
{
	std::thread t[NTHREADS - 1];
	size_t block = COUNT / NTHREADS;
	std::pair<int, int> global_pair;
	std::pair<int, int> results[NTHREADS - 1];
	for (size_t i = 0; i < NTHREADS - 1; ++i)
	{
		t[i] = std::thread(find_max_critical_section, arr, i* block, (i + 1)* block, std::ref(global_pair));
	}
	
	find_max_critical_section(arr, block * (NTHREADS - 1), COUNT, global_pair);

	for (size_t i = 0; i < NTHREADS - 1; ++i)
		t[i].join();

	return global_pair.second;
}

threadsave_stack st;

// для stack
void find_max_stack(int* arr, std::pair<int, int>& global_max)
{
	while (!st.empty())
	{
		std::pair<int, int> pos;
		if (st.try_pop(pos))
		{
			int left = pos.first, right = pos.second, ma = global_max.first, ma_i = global_max.second;
			for (size_t i = left; i < right; ++i)
			{
				if (arr[i] > ma)
				{
					ma = arr[i];
					ma_i = i;
				}
				else
					if (arr[i] == ma)
						ma_i = i;
			}
			// в лабе спросить, если макс больше или равен, тогда ждём
			if (ma > global_max.first) // вроде так
			{
				while (aflag.test_and_set())
					Sleep(0);

				if (ma > global_max.first)
				{
					global_max = { ma, ma_i };
				}
				else if (ma == global_max.first && global_max.second < ma_i)
					global_max.second = ma_i;
				aflag.clear();
			}
		}
		
	}
}

int max_parallel_stack(int* arr)
{
	std::thread t[NTHREADS - 1];
	size_t block = 10;
	std::pair<int, int> global_pair;
	int i = 0;
	while (i < COUNT)
	{
		st.push(i, i + block > COUNT ? COUNT : i + block);
		i += block;
	}
	for (size_t i = 0; i < NTHREADS - 1; ++i)
	{
		t[i] = std::thread(find_max_stack, arr, std::ref(global_pair));
	}

	find_max_stack(arr, global_pair);

	for (size_t i = 0; i < NTHREADS - 1; ++i)
		t[i].join();

	return global_pair.second;
}

int main()
{
	srand(GetTickCount());
	int array[COUNT];
	init_array(array);

	// найти номер последнего максимального элемента в массиве
	std::cout << "max non parallel = " << max_non_parallel(array) << '\n'
		<< "max parallel = " << max_parallel_future(array) << '\n'
		<< "max with critical section = " << max_parallel_critical(array) << '\n'
		<< "max with stack = " << max_parallel_stack(array) << '\n';
	return 0;
}