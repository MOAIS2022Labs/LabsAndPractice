// 27. Дан одномерный массив из целых чисел. Найти сумму двух старших разрядов чисел

#include "ThreadsafeQueue.h"
#include <iostream>
#include <condition_variable>
#include <thread>
#include <algorithm>
#include <fstream>
#include <mutex>
#include <process.h>
#include <Windows.h>

const size_t COUNT = 10;
const size_t NTHREADS = 5;

ThreadsafeQueue que;
std::condition_variable cv;
std::mutex mut;
volatile long volume_work_producer = 6;
volatile long volume_work_consumer = 6;

//void init_array(int* arr)
//{
//	for (size_t i = 0; i < COUNT; ++i)
//		arr[i] = rand() % 1000;
//}

int sum_senior_ranks(int num)
{
	while (num > 100)
		num /= 10;
	return num;
}

int sum_non_parallel(int* arr)
{
	int result{};
	std::for_each(arr, arr + COUNT, [&result](int x) {result += sum_senior_ranks(x); });
	return result;
}

//void sum_producer(int* arr, std::atomic_int& result)
//{
//	while (volume_work_producer)
//	{
//		int elem = rand() % 100;
//		std::this_thread::sleep_for(std::chrono::milliseconds(2)); 
//		//que.push(elem + ID, ID);
//		cv.notify_all();
//	}
//}

void task_producer(int id)
{
	srand(GetTickCount64() + id);
	while (_InterlockedExchangeAdd(&volume_work_producer, -1) > 0)
	{
		int* arr = new int[COUNT];
		for (int i = 0; i < COUNT; ++i)
		{
			//std::this_thread::sleep_for(std::chrono::milliseconds(3));
			arr[i] = rand() % 1000;
			//std::cout << arr[i] << '|';
			std::this_thread::sleep_for(std::chrono::milliseconds(2));
		}
		//std::cout << '\n';
		que.push(arr);
		cv.notify_all();
	}
}

void task_consumer()
{
	while (_InterlockedExchangeAdd(&volume_work_consumer, -1) > 0)
	{
		int* arr = nullptr;
		std::unique_lock<std::mutex> locker(mut);
		cv.wait_for(locker, std::chrono::seconds(5), []() {return !que.empty(); });
		if (que.try_pop(arr))
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(5));
			std::cout << sum_non_parallel(arr) << '\n';
			delete[] arr;
		}
		else
		{
			_InterlockedExchangeAdd(&volume_work_consumer, 1);
		}
	}
}

int main()
{
	
	std::thread workers[NTHREADS];
	for (int i = 0; i < NTHREADS; ++i)
	{
		if (i < 2)
			workers[i] = std::thread(task_producer, 10*i);
		else
			workers[i] = std::thread(task_consumer);
	}

	for (int i = 0; i < NTHREADS; ++i)
		workers[i].join();

	return 0;
}