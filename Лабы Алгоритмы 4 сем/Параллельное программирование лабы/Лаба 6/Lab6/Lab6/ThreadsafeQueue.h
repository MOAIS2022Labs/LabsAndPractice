#pragma once
#include <queue>
#include <Windows.h>
//#include <process.h>

class ThreadsafeQueue
{

private:

	std::queue<int*> que;
	HANDLE hSemaphore = CreateSemaphore(
		NULL,
		1,
		1,
		NULL);

public:

	bool empty();

	void push(int* arr);

	bool try_pop(int*& value);

	~ThreadsafeQueue()
	{
		CloseHandle(hSemaphore);
	}
};
